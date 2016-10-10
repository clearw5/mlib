/*
 * m_linear_map.c
 *
 *  Created on: 2016Äê10ÔÂ5ÈÕ
 *      Author: Stardust
 */

#include "m_linear_map.h"
#include "m_linear_map_iterator.h"

m_linear_map m_linear_map_new(m_allocator allocator) {
	m_linear_map m = (m_linear_map) m_malloc(sizeof(m_linear_map_t), allocator);
	m->keys = m_vector_new(10, allocator);
	m->values = m_vector_new(10, allocator);
	m->size = 0;
	m->allocator = allocator;
	return m;
}

void m_linear_map_put(m_linear_map m, m_element key, m_element value) {
	index_t i = m_vector_find(m->keys, key);
	if (i < m->keys->size) {
		m_vector_set(m->values, i, value);
	} else {
		m_vector_add(m->keys, key);
		m_vector_add(m->values, value);
		m->size++;
	}
}

void m_linear_map_put_entry(m_linear_map m, m_map_entry e) {
	m_linear_map_put(m, e.key, e.value);
}

m_element m_linear_map_get(m_linear_map m, m_element key) {
	index_t i = m_vector_find(m->keys, key);
	if (i < m->keys->size) {
		return m_vector_at(m->values, i);
	} else {
		return m_element_null();
	}
}

m_element m_linear_map_remove(m_linear_map m, m_element key) {
	index_t i = m_vector_find(m->keys, key);
	if (i < m->keys->size) {
		m_element e = m_vector_at(m->values, i);
		m_vector_remove(m->keys, i);
		m_vector_remove(m->values, i);
		return e;
	}
	return m_element_null();
}

size_t m_linear_map_size(m_linear_map m) {
	return m->size;
}

void m_linear_map_clear(m_linear_map m) {
	m_vector_clear(m->keys);
	m_vector_clear(m->values);
	m->size = 0;
}

bool m_linear_map_contains(m_linear_map m, m_element key) {
	return m_vector_contains(m->keys, key);
}

bool m_linear_map_empty(m_linear_map m) {
	return m->size == 0;
}

void m_linear_map_free(m_linear_map m) {
	m_vector_free_and_set_null(&m->keys);
	m_vector_free_and_set_null(&m->values);
	m->size = 0;
	m_free(m, m->allocator);
}

static size_t map_impl_size(m_map_instance s) {
	return m_linear_map_size((m_linear_map) s);
}

static void map_impl_put(m_map_instance s, m_element k, m_element v) {
	m_linear_map_put((m_linear_map) s, k, v);
}

static m_element map_impl_remove(m_map_instance s, m_element k) {
	return m_linear_map_remove((m_linear_map) s, k);
}

static m_element map_impl_get(m_map_instance s, m_element k) {
	return m_linear_map_get((m_linear_map) s, k);
}

static void map_impl_clear(m_map_instance s) {
	m_linear_map_clear((m_linear_map) s);
}

static bool map_impl_contains(m_map_instance s, m_element k) {
	return m_linear_map_contains((m_linear_map) s, k);
}

static m_const_iterator map_impl_iterate(m_map_instance s,
		m_allocator allocator) {
	return m_linear_map_const_iterate((m_linear_map) s, allocator);
}

static void map_impl_free(m_map_instance s) {
	m_linear_map_free((m_linear_map) s);
}

static m_map_impl_t map_impl_linear_map = {
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
		map_impl_free };

m_map m_linear_map_new_map(m_allocator allocator) {
	m_map s = (m_map) m_malloc(sizeof(m_map_t), allocator);
	s->allocator = allocator;
	m_linear_map hs = m_linear_map_new(allocator);
	s->impl = &map_impl_linear_map;
	s->instance = hs;
	return s;
}
