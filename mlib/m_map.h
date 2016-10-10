/*
 * m_map.h
 *
 *  Created on: 2016Äê10ÔÂ3ÈÕ
 *      Author: Stardust
 */

#ifndef MLIB_M_MAP_H_
#define MLIB_M_MAP_H_

#include <stdbool.h>
#include "m_iterator.h"
#include "m_type.h"

struct m_map_impl_t;
typedef struct m_map_impl_t* m_map_impl;
typedef void* m_map_instance;

typedef struct m_map_t {
	m_map_impl impl;
	m_map_instance instance;
	m_allocator allocator;
} m_map_t;

typedef m_map_t* m_map;

typedef struct m_map_entry {
	m_element key;
	m_element value;
} m_map_entry;

extern m_type M_TYPE_MAP_ENTRY_PTR;

typedef struct m_map_impl_t {
	void (*put)(m_map_instance m, m_element key, m_element value);
	m_element (*get)(m_map_instance m, m_element key);
	m_element (*remove)(m_map_instance m, m_element key);
	size_t (*size)(m_map_instance m);
	m_const_iterator (*iterate)(m_map_instance m, m_allocator allocator);
	bool (*contains)(m_map_instance m, m_element key);
	void (*clear)(m_map_instance m);
	void (*free)(m_map_instance m);
} m_map_impl_t;

void m_map_put(m_map m, m_element key, m_element value);

void m_map_put_entry(m_map m, m_map_entry e);

m_element m_map_get(m_map m, m_element key);

m_element m_map_remove(m_map m, m_element key);

bool m_map_contains(m_map m, m_element key);

void m_map_clear(m_map m);

size_t m_map_size(m_map m);

bool m_map_empty(m_map m);

m_const_iterator m_map_iterate(m_map m, m_allocator allocator);

void m_map_free(m_map m);

m_map_entry *m_entry(m_element e);

m_element m_key_value_to_entry_element(m_element k, m_element v, m_allocator a);

#endif /* MLIB_M_MAP_H_ */
