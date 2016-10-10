/*
 * m_hash_set_iterator.h
 *
 *  Created on: 2016Äê10ÔÂ3ÈÕ
 *      Author: Stardust
 */

#ifndef MLIB_M_HASH_SET_ITERATOR_H_
#define MLIB_M_HASH_SET_ITERATOR_H_

#include "m_iterator.h"
#include "m_hash_set.h"

typedef struct m_hash_set_iterator_t {
	m_hash_set hash_set;
	m_iterator nonnull_position_iterator;
	m_iterator subset_iter;
	m_iterator next_subset_iter;
	bool has_next;
	m_allocator allocator;
} m_hash_set_iterator_t;

typedef m_hash_set_iterator_t* m_hash_set_iterator;

m_iterator m_hash_set_iterate(m_hash_set s, m_allocator allocator);

void m_hash_set_init_const_iterator(m_hash_set s, m_const_iterator iter, m_hash_set_iterator hash_set_iterator);

m_const_iterator m_hash_set_const_iterate(m_hash_set s, m_allocator allocator);


#endif /* MLIB_M_HASH_SET_ITERATOR_H_ */
