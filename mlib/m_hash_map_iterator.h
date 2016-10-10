/*
 * m_hash_map_iterator.h
 *
 *  Created on: 2016Äê10ÔÂ5ÈÕ
 *      Author: Stardust
 */

#ifndef MLIB_M_HASH_MAP_ITERATOR_H_
#define MLIB_M_HASH_MAP_ITERATOR_H_

#include "m_iterator.h"
#include "m_hash_map.h"

typedef struct m_hash_map_iterator_t {
	m_hash_map hash_map;
	m_iterator nonnull_position_iterator;
	m_iterator submap_iter;
	m_iterator next_submap_iter;
	bool has_next;
	m_allocator allocator;
} m_hash_map_iterator_t;

typedef m_hash_map_iterator_t* m_hash_map_iterator;

m_const_iterator m_hash_map_const_iterate(m_hash_map m, m_allocator allocator);

#endif /* MLIB_M_HASH_MAP_ITERATOR_H_ */
