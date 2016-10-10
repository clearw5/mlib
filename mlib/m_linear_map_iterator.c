/*
 * m_linear_map_iterator.c
 *
 *  Created on: 2016Äê10ÔÂ5ÈÕ
 *      Author: Stardust
 */

#include "m_linear_map_iterator.h"
#include "m_vector.h"
#include "m_vector_iterator.h"

typedef struct m_linear_map_iterator_t {
	m_iterator key_iterator;
	m_iterator value_iterator;
	m_allocator allocator;
} m_linear_map_iterator_t;

typedef m_linear_map_iterator_t* m_linear_map_iterator;

static bool m_iterator_impl_has_next(m_iterator_instance instance) {
	m_linear_map_iterator iter = (m_linear_map_iterator) instance;
	return m_iterator_has_next(iter->key_iterator)
			&& m_iterator_has_next(iter->value_iterator);
}

static m_element m_iterator_impl_next(m_iterator_instance instance) {
	m_linear_map_iterator iter = (m_linear_map_iterator) instance;
	return m_key_value_to_entry_element(m_iterator_next(iter->key_iterator),
			m_iterator_next(iter->value_iterator), iter->allocator);
}

static m_const_iterator_impl_t m_iterator_impl_linear_map_iterator = {
		m_iterator_impl_has_next, m_iterator_impl_next };

m_const_iterator m_linear_map_const_iterate(m_linear_map m, m_allocator a) {
	m_const_iterator iter = (m_const_iterator) m_malloc(sizeof(m_const_iterator_t), a);
	m_linear_map_iterator linear_map_iterator = (m_linear_map_iterator)m_malloc(sizeof(m_linear_map_iterator_t), a);
	linear_map_iterator->allocator = a;
	linear_map_iterator->key_iterator = m_vector_iterate(m->keys, a);
	linear_map_iterator->value_iterator = m_vector_iterate(m->values, a);
	iter->impl = &m_iterator_impl_linear_map_iterator;
	iter->instance = linear_map_iterator;
	return iter;
}
