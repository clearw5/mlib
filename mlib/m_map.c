/*
 * m_map.c
 *
 *  Created on: 2016Äê10ÔÂ4ÈÕ
 *      Author: Stardust
 */

#include "m_map.h"

m_type_t M_TYPE_T_MAP_ENTRY_PTR = { "m_map_entry", true };
m_type M_TYPE_MAP_ENTRY_PTR = &M_TYPE_T_MAP_ENTRY_PTR;

void m_map_put(m_map m, m_element key, m_element value) {
	m->impl->put(m->instance, key, value);
}

void m_map_put_entry(m_map m, m_map_entry e) {
	m_map_put(m, e.key, e.value);
}

m_element m_map_get(m_map m, m_element key) {
	return m->impl->get(m->instance, key);
}

m_element m_map_remove(m_map m, m_element key) {
	return m->impl->remove(m->instance, key);
}

bool m_map_contains(m_map m, m_element key) {
	return m->impl->contains(m->instance, key);
}

void m_map_clear(m_map m) {
	return m->impl->clear(m->instance);
}

size_t m_map_size(m_map m) {
	return m->impl->size(m->instance);
}

bool m_map_empty(m_map m) {
	return m_map_size(m) == 0;
}

m_const_iterator m_map_iterate(m_map m, m_allocator allocator) {
	return m->impl->iterate(m->instance, allocator);
}

void m_map_free(m_map m) {
	m->impl->free(m->instance);
	m->instance = NULL;
	m_free(m, m->allocator);
}

m_map_entry *m_entry(m_element e) {
	m_map_entry *entry = (m_map_entry*) m_ptr(e, M_TYPE_MAP_ENTRY_PTR);
	return entry;
}

m_element m_key_value_to_entry_element(m_element k, m_element v, m_allocator a) {
	m_map_entry *entry = (m_map_entry*) m_malloc(sizeof(m_map_entry), a);
	entry->key = k;
	entry->value = v;
	return m_element_init_ptr(entry, M_TYPE_MAP_ENTRY_PTR);
}
