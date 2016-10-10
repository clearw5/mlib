/*
 * vector_iterator.h
 *
 *  Created on: 2016Äê10ÔÂ3ÈÕ
 *      Author: Stardust
 */

#ifndef MLIB_M_VECTOR_ITERATOR_H_
#define MLIB_M_VECTOR_ITERATOR_H_

#include "m_iterator.h"
#include "m_vector.h"
#include <stdlib.h>

typedef struct m_vector_iterator_t {
	m_vector vec;
	index_t next_pos;
	bool removed;
} m_vector_iterator_t;

typedef m_vector_iterator_t* m_vector_iterator;

m_iterator m_vector_iterate(m_vector v, m_allocator a);

m_const_iterator m_vector_const_iterate(m_vector v, m_allocator a);

#endif /* MLIB_M_VECTOR_ITERATOR_H_ */
