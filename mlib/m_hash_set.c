/*
 * m_hash_set.c
 *
 *  Created on: 2016Äê10ÔÂ3ÈÕ
 *      Author: Stardust
 */

#include "m_hash_set.h"
#include "m_allocator.h"
#include "m_hash_set_iterator.h"
#include "m_type.h"
#include <memory.h>

m_hash_set m_hash_set_new(size_t initial_capacity, float load_factor,
		m_hash_function hash_function, m_allocator allocator) {
	m_hash_set s = (m_hash_set) m_malloc(sizeof(m_hash_set_t), allocator);
	s->size = 0;
	s->allocator = allocator;
	s->load_factor = load_factor;
	s->element_table_nonnull_positions = m_linked_list_new_list(allocator);
	s->hash_function = hash_function;
	s->element_hash_function = M_ELEMENT_HASH_FUNCTION_DEFAULT;
	s->capacity = 1;
	while (s->capacity < initial_capacity) {
		s->capacity = s->capacity << 1;
	}
	s->element_table = (m_set*) m_malloc(sizeof(m_set) * s->capacity,
			allocator);
	memset(s->element_table, 0, sizeof(m_set) * s->capacity);
	return s;
}

m_hash_set m_hash_set_new_custom_element_hash_function(size_t initial_capacity, float load_factor,
		m_element_hash_function element_hash_function, m_allocator allocator) {
	m_hash_set s = m_hash_set_new(initial_capacity, load_factor, NULL, allocator);
	s->element_hash_function = element_hash_function;
	return s;
}

m_hash_set m_hash_set_new_def(m_allocator allocator) {
	return m_hash_set_new(16, 0.75f, m_hash_code_crc32, allocator);
}

static index_t m_hash_set_index_for(m_hash h, size_t length) {
	return h & (length - 1);
}

static void m_hash_set_add_element(m_set *table, m_list position_list, index_t index, m_element e, m_allocator allocator){
	if (table[index] == NULL) {
		table[index] = m_linked_list_new_set(allocator);
		m_list_add(position_list, m_element_init_i(index));
	}
	m_set_add(table[index], e);
}

static void m_hash_set_table_transfer(m_hash_set s, m_set *new_table, size_t new_capacity){
	m_list new_position_list = m_linked_list_new_list(s->allocator);
	m_iterator iter = m_list_iterate(s->element_table_nonnull_positions, ALLOCATOR_NONE);
	while(m_iterator_has_next(iter)){
		int old_pos = m_int(m_iterator_next(iter));
		m_iterator subset_iter = m_set_iterate(s->element_table[old_pos], ALLOCATOR_NONE);
		while(m_iterator_has_next(subset_iter)){
			m_element e = m_iterator_next(subset_iter);
			m_hash h = m_hash_set_element_hash(s, e);
			index_t new_pos = m_hash_set_index_for(h, new_capacity);
			m_hash_set_add_element(new_table, new_position_list, new_pos, e, s->allocator);
		}
		m_iterator_free(subset_iter, ALLOCATOR_NONE);
		m_set_free(s->element_table[old_pos]);
	}
	m_iterator_free(iter, ALLOCATOR_NONE);
	m_list_free(s->element_table_nonnull_positions);
	s->element_table_nonnull_positions = new_position_list;
}

static void m_hash_set_resize(m_hash_set s, size_t capacity) {
	m_set *new_table = (m_set*) m_malloc(sizeof(m_set) * capacity,
			s->allocator);
	memset(new_table, 0, sizeof(m_set) * capacity);
	m_hash_set_table_transfer(s, new_table, capacity);
	s->capacity = capacity;
	m_free(s->element_table, s->allocator);
	s->element_table = new_table;
}

void m_hash_set_add(m_hash_set s, m_element e) {
	m_hash h = m_hash_set_element_hash(s, e);
	index_t index = m_hash_set_index_for(h, s->capacity);
	m_hash_set_add_element(s->element_table, s->element_table_nonnull_positions, index, e, s->allocator);
	if (s->size++ >= (size_t) (s->load_factor * s->capacity)) {
		m_hash_set_resize(s, 2 * s->capacity);
	}
}

bool m_hash_set_remove(m_hash_set s, m_element e) {
	m_hash h = m_hash_set_element_hash(s, e);
	index_t index = m_hash_set_index_for(h, s->capacity);
	if (s->element_table[index] != NULL) {
		return m_set_remove(s->element_table[index], e);
	}
	return false;
}

size_t m_hash_set_size(m_hash_set s) {
	return s->size;
}

bool m_hash_set_empty(m_hash_set s) {
	return s->size == 0;
}

bool m_hash_set_contains(m_hash_set s, m_element e) {
	m_hash h = m_hash_set_element_hash(s, e);
	index_t index = m_hash_set_index_for(h, s->capacity);
	if (s->element_table[index] != NULL) {
		return m_set_contains(s->element_table[index], e);
	}
	return false;
}

void m_hash_set_clear(m_hash_set s) {
	m_iterator iter = m_list_iterate(s->element_table_nonnull_positions, ALLOCATOR_NONE);
	while (m_iterator_has_next(iter)) {
		index_t i = m_int(m_iterator_next(iter));
		m_set_free(s->element_table[i]);
		m_iterator_remove(iter);
	}
	m_iterator_free(iter, ALLOCATOR_NONE);
}

m_hash m_hash_set_data_hash(m_pointer data, size_t size,
		m_hash_function hash_function) {
	if (size <= sizeof(m_hash)) {
		return *(m_hash*) data;
	}
	return hash_function(data, size);
}

m_hash m_hash_set_element_hash(m_hash_set s, m_element e) {
	m_hash h;
	if(s->element_hash_function == M_ELEMENT_HASH_FUNCTION_DEFAULT){
		h = m_hash_set_data_hash(&e.value, sizeof(m_pointer), s->hash_function);
	}else{
		h = s->element_hash_function(e);
	}
	return m_hash_set_secondary_hash(h);
}

m_hash m_hash_set_secondary_hash(m_hash h) {
	h ^= (h >> 20) ^ (h >> 12);
	return h ^ (h >> 7) ^ (h >> 4);
}

void m_hash_set_free(m_hash_set s){
	m_hash_set_clear(s);
	m_free(s->element_table, s->allocator);
	s->element_table = NULL;
	m_list_free(s->element_table_nonnull_positions);
	s->element_table_nonnull_positions = NULL;
	s->capacity = 0;
	s->size = 0;
	m_free(s, s->allocator);
}

void m_hash_set_free_and_set_null(m_hash_set *s){
	m_hash_set_free(*s);
	*s = NULL;
}



static size_t set_impl_size(m_set_instance s) {
	return m_hash_set_size((m_hash_set) s);
}

static void set_impl_add(m_set_instance s, m_element e) {
	m_hash_set_add((m_hash_set) s, e);
}

static bool set_impl_remove(m_set_instance s, m_element e) {
	return m_hash_set_remove((m_hash_set) s, e);
}

static void set_impl_clear(m_set_instance s) {
	m_hash_set_clear((m_hash_set) s);
}

static bool set_impl_contains(m_set_instance s, m_element e) {
	return m_hash_set_contains((m_hash_set) s, e);
}

static bool set_impl_empty(m_set_instance s) {
	return m_hash_set_empty((m_hash_set) s);
}

static m_iterator set_impl_iterate(m_set_instance s, m_allocator allocator) {
	return (m_iterator) m_hash_set_iterate((m_hash_set) s, allocator);
}

static void set_impl_free(m_set_instance s){
	m_hash_set_free((m_hash_set) s);
}

static m_set_impl_t set_impl_hash_set = {
		//.size =
		set_impl_size,
		//.add =
		set_impl_add,
		//.remove =
		set_impl_remove,
		//.contains =
		set_impl_contains,
		//.clear =
		set_impl_clear,
		//.empty =
		set_impl_empty,
		//.iterate =
		set_impl_iterate,
		//.free
		set_impl_free
};

m_set m_hash_set_new_set(m_allocator allocator) {
	m_set s = (m_set) m_malloc(sizeof(m_set_t), allocator);
	s->allocator = allocator;
	m_hash_set hs = m_hash_set_new_def(allocator);
	s->impl = &set_impl_hash_set;
	s->instance = hs;
	return s;
}
