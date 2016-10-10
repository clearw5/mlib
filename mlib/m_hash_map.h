/*
 * m_hash_map.h
 *
 *  Created on: 2016Äê10ÔÂ3ÈÕ
 *      Author: Stardust
 */

#ifndef MLIB_M_HASH_MAP_H_
#define MLIB_M_HASH_MAP_H_

#include "m_map.h"
#include "m_hash_set.h"

typedef struct m_hash_map_t {
	size_t capacity;
	size_t size;
	float load_factor;
	m_allocator allocator;
	m_hash_function hash_function;
	m_element_hash_function element_hash_function;
	m_map *element_table;
	m_list element_table_nonnull_positions;
} m_hash_map_t;

typedef struct m_hash_map_t* m_hash_map;

m_hash_map m_hash_map_new(size_t initial_capacity, float load_factor,
		m_hash_function hash_function, m_allocator allocator);

m_map m_hash_map_new_map(m_allocator allocator);

void m_hash_map_put(m_hash_map m, m_element key, m_element value);

void m_hash_map_put_entry(m_hash_map m, m_map_entry e);

m_element m_hash_map_get(m_hash_map m, m_element key);

m_element m_hash_map_remove(m_hash_map m, m_element key);

size_t m_hash_map_size(m_hash_map m);

bool m_hash_map_empty(m_hash_map m);

m_const_iterator m_hash_map_iterate(m_hash_map m, m_allocator allocator);

void m_hash_map_free(m_hash_map m);

m_hash m_hash_map_key_hash(m_hash_map m, m_element key);

m_hash m_hash_map_secondary_hash(m_hash h);

#endif /* MLIB_M_HASH_MAP_H_ */
