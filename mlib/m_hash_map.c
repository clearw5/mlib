/*
 * m_hash_map.c
 *
 *  Created on: 2016Äê10ÔÂ3ÈÕ
 *      Author: Stardust
 */

#include "m_hash_map.h"
#include "m_allocator.h"
#include "m_type.h"
#include "m_linear_map.h"
#include <memory.h>

m_hash_map m_hash_map_new(size_t initial_capacity, float load_factor,
		m_hash_function hash_function, m_allocator allocator) {
	m_hash_map m = (m_hash_map) m_malloc(sizeof(m_hash_map_t), allocator);
	m->size = 0;
	m->allocator = allocator;
	m->load_factor = load_factor;
	m->element_table_nonnull_positions = m_linked_list_new_list(allocator);
	m->hash_function = hash_function;
	m->element_hash_function = M_ELEMENT_HASH_FUNCTION_DEFAULT;
	m->capacity = 1;
	while (m->capacity < initial_capacity) {
		m->capacity = m->capacity << 1;
	}
	m->element_table = (m_map*) m_malloc(sizeof(m_map) * m->capacity,
			allocator);
	memset(m->element_table, 0, sizeof(m_map) * m->capacity);
	return m;
}

m_hash_map m_hash_map_new_custom_element_hash_function(size_t initial_capacity,
		float load_factor, m_element_hash_function element_hash_function,
		m_allocator allocator) {
	m_hash_map m = m_hash_map_new(initial_capacity, load_factor, NULL,
			allocator);
	m->element_hash_function = element_hash_function;
	return m;
}

m_hash_map m_hash_map_new_def(m_allocator allocator) {
	return m_hash_map_new(16, 0.75f, m_hash_code_crc32, allocator);
}

static index_t m_hash_map_index_for(m_hash h, size_t length) {
	return h & (length - 1);
}

static void m_hash_map_put_in_table(m_map *table, m_list position_list,
		index_t index, m_element key, m_element value, m_allocator allocator) {
	if (table[index] == NULL) {
		table[index] = m_linear_map_new_map(allocator);
		m_list_add(position_list, m_element_init_i(index));
	}
	m_map_put(table[index], key, value);
}

static void m_hash_map_table_transfer(m_hash_map s, m_map *new_table,
		size_t new_capacity) {
	m_list new_position_list = m_linked_list_new_list(s->allocator);
	m_iterator iter = m_list_iterate(s->element_table_nonnull_positions,
			ALLOCATOR_NONE);
	while (m_iterator_has_next(iter)) {
		int old_pos = m_int(m_iterator_next(iter));
		m_const_iterator submap_iter = m_map_iterate(s->element_table[old_pos],
				ALLOCATOR_NONE);
		while (m_const_iterator_has_next(submap_iter)) {
			m_map_entry *e = m_entry(m_const_iterator_next(submap_iter));
			m_hash h = m_hash_map_key_hash(s, e->key);
			index_t new_pos = m_hash_map_index_for(h, new_capacity);
			m_hash_map_put_in_table(new_table, new_position_list, new_pos, e->key, e->value,
					s->allocator);
		}
		m_const_iterator_free(submap_iter, ALLOCATOR_NONE);
		m_map_free(s->element_table[old_pos]);
	}
	m_iterator_free(iter, ALLOCATOR_NONE);
	m_list_free(s->element_table_nonnull_positions);
	s->element_table_nonnull_positions = new_position_list;
}

static void m_hash_map_resize(m_hash_map s, size_t capacity) {
	m_map *new_table = (m_map*) m_malloc(sizeof(m_map) * capacity,
			s->allocator);
	memset(new_table, 0, sizeof(m_map) * capacity);
	m_hash_map_table_transfer(s, new_table, capacity);
	s->capacity = capacity;
	m_free(s->element_table, s->allocator);
	s->element_table = new_table;
}

void m_hash_map_put(m_hash_map m, m_element key, m_element value) {
	m_hash h = m_hash_map_key_hash(m, key);
	index_t index = m_hash_map_index_for(h, m->capacity);
	m_hash_map_put_in_table(m->element_table, m->element_table_nonnull_positions,
			index, key, value, m->allocator);
	if (m->size++ >= (size_t) (m->load_factor * m->capacity)) {
		m_hash_map_resize(m, 2 * m->capacity);
	}
}

void m_hash_map_put_entry(m_hash_map m, m_map_entry e) {
	m_hash_map_put(m, e.key, e.value);
}

m_element m_hash_map_get(m_hash_map m, m_element key) {
	m_hash h = m_hash_map_key_hash(m, key);
	index_t index = m_hash_map_index_for(h, m->capacity);
	if (m->element_table[index] != NULL) {
		return m_map_get(m->element_table[index], key);
	}
	return m_element_null();
}

m_element m_hash_map_remove(m_hash_map m, m_element key){
	m_hash h = m_hash_map_key_hash(m, key);
	index_t index = m_hash_map_index_for(h, m->capacity);
	if (m->element_table[index] != NULL) {
		return m_map_remove(m->element_table[index], key);
	}
	return m_element_null();
}

bool m_hash_map_contains(m_hash_map m, m_element k) {
	m_hash h = m_hash_map_key_hash(m, k);
	index_t index = m_hash_map_index_for(h, m->capacity);
	if (m->element_table[index] != NULL) {
		return m_map_contains(m->element_table[index], k);
	}
	return false;
}

size_t m_hash_map_size(m_hash_map m){
	return m->size;
}

bool m_hash_map_empty(m_hash_map m){
	return m->size == 0;
}

m_const_iterator m_hash_map_iterate(m_hash_map m, m_allocator allocator){
	// TODO
	return NULL;// m_hash_map_const_iterate(m, allocator);
}

void m_hash_map_clear(m_hash_map s) {
	m_iterator iter = m_list_iterate(s->element_table_nonnull_positions,
			ALLOCATOR_NONE);
	while (m_iterator_has_next(iter)) {
		index_t i = m_int(m_iterator_next(iter));
		m_map_free(s->element_table[i]);
		m_iterator_remove(iter);
	}
	m_iterator_free(iter, ALLOCATOR_NONE);
}


m_hash m_hash_map_data_hash(m_pointer data, size_t size,
		m_hash_function hash_function) {
	if (size <= sizeof(m_hash)) {
		return *(m_hash*) data;
	}
	return hash_function(data, size);
}

m_hash m_hash_map_key_hash(m_hash_map m, m_element key) {
	m_hash h;
	if (m->element_hash_function == M_ELEMENT_HASH_FUNCTION_DEFAULT) {
		h = m_hash_map_data_hash(m_element_get_data_ptr(&key), key.size,
				m->hash_function);
	} else {
		h = m->element_hash_function(key);
	}
	return m_hash_map_secondary_hash(h);
}

m_hash m_hash_map_secondary_hash(m_hash h) {
	h ^= (h >> 20) ^ (h >> 12);
	return h ^ (h >> 7) ^ (h >> 4);
}

void m_hash_map_free(m_hash_map s) {
	m_hash_map_clear(s);
	m_free(s->element_table, s->allocator);
	s->element_table = NULL;
	m_list_free(s->element_table_nonnull_positions);
	s->element_table_nonnull_positions = NULL;
	s->capacity = 0;
	s->size = 0;
	m_free(s, s->allocator);
}

void m_hash_map_free_and_set_null(m_hash_map *s) {
	m_hash_map_free(*s);
	*s = NULL;
}

static size_t map_impl_size(m_map_instance s) {
	return m_hash_map_size((m_hash_map) s);
}

static void map_impl_put(m_map_instance s, m_element k, m_element v) {
	m_hash_map_put((m_hash_map) s, k, v);
}

static m_element map_impl_remove(m_map_instance s, m_element k) {
	return m_hash_map_remove((m_hash_map) s, k);
}

static m_element map_impl_get(m_map_instance s, m_element k) {
	return m_hash_map_get((m_hash_map) s, k);
}

static void map_impl_clear(m_map_instance s) {
	m_hash_map_clear((m_hash_map) s);
}

static bool map_impl_contains(m_map_instance s, m_element k) {
	return m_hash_map_contains((m_hash_map) s, k);
}

static m_const_iterator map_impl_iterate(m_map_instance s, m_allocator allocator) {
	return  m_hash_map_iterate((m_hash_map) s, allocator);
}

static void map_impl_free(m_map_instance s) {
	m_hash_map_free((m_hash_map) s);
}

static m_map_impl_t map_impl_hash_map = {
		//.put =
		map_impl_put,
		//.get =
		map_impl_get,
		//.remove =
		map_impl_remove,
		//.size =
		map_impl_size,
		//.iterate =
		map_impl_iterate,
		//.contains =
		map_impl_contains,
		//.clear =
		map_impl_clear,
		//.free
		map_impl_free
};

m_map m_hash_map_new_map(m_allocator allocator) {
	m_map s = (m_map) m_malloc(sizeof(m_map_t), allocator);
	s->allocator = allocator;
	m_hash_map hs = m_hash_map_new_def(allocator);
	s->impl = &map_impl_hash_map;
	s->instance = hs;
	return s;
}
