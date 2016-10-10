/*
 * m_linear_map.h
 *
 *  Created on: 2016Äê10ÔÂ5ÈÕ
 *      Author: Stardust
 */

#ifndef MLIB_M_LINEAR_MAP_H_
#define MLIB_M_LINEAR_MAP_H_

#include "m_vector.h"
#include "m_map.h"

typedef struct m_linear_map_t {
	size_t size;
	m_allocator allocator;
	m_vector keys;
	m_vector values;
} m_linear_map_t;

typedef struct m_linear_map_t* m_linear_map;

m_linear_map m_linear_map_new(m_allocator allocator);

m_map m_linear_map_new_map(m_allocator allocator);

void m_linear_map_put(m_linear_map m, m_element key, m_element value);

void m_linear_map_put_entry(m_linear_map m, m_map_entry e);

m_element m_linear_map_get(m_linear_map m, m_element key);

m_element m_linear_map_remove(m_linear_map m, m_element key);

size_t m_linear_map_size(m_linear_map m);

bool m_linear_map_empty(m_linear_map m);

m_const_iterator m_linear_map_iterate(m_linear_map m);

void m_linear_map_free(m_linear_map m);

#endif /* MLIB_M_LINEAR_MAP_H_ */
