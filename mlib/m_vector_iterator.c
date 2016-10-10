/*
 * m_vector_iterator.c
 *
 *  Created on: 2016Äê10ÔÂ3ÈÕ
 *      Author: Stardust
 */

#include "m_vector_iterator.h"
#include "m_except.h"

bool m_vector_iterator_has_next(m_vector_iterator iter) {
	return iter->next_pos < iter->vec->size;
}

m_element m_vector_iterator_next(m_vector_iterator iter) {
	if (!m_vector_iterator_has_next(iter)) {
		m_fatal_error_cstr(ILLEAGL_STATE,
						"m_vector_iterator next element does not exist");
	}
	m_element e = m_vector_at(iter->vec, iter->next_pos);
	iter->removed = false;
	iter->next_pos++;
	return e;
}

void m_vector_iterator_remove(m_vector_iterator iter) {
	if (iter->removed) {
		m_fatal_error_f(ILLEAGL_STATE,
				"m_vector_iterator_remove should be called only once after next");
	}
	m_vector_remove(iter->vec, iter->next_pos - 1);
	iter->removed = true;
}

static bool m_iterator_impl_has_next(m_iterator_instance iter) {
	return m_vector_iterator_has_next((m_vector_iterator) iter);
}

static m_element m_iterator_impl_next(m_iterator_instance iter) {
	return m_vector_iterator_next((m_vector_iterator) iter);
}

static void m_iterator_impl_remove(m_iterator_instance iter) {
	return m_vector_iterator_remove((m_vector_iterator) iter);
}

static m_iterator_impl_t iterator_impl_vector_iterator = {
		//.has_next =
		m_iterator_impl_has_next,
		//.next =
		m_iterator_impl_next,
		//.remove=
		m_iterator_impl_remove
};

void m_vector_init_iterator(m_vector v, m_iterator iter,
		m_vector_iterator vector_iterator) {
	vector_iterator->vec = v;
	vector_iterator->next_pos = 0;
	vector_iterator->removed = true;
	iter->impl = &iterator_impl_vector_iterator;
	iter->instance = vector_iterator;
}

m_iterator m_vector_iterate(m_vector li, m_allocator allocator) {
	m_iterator iter = (m_iterator) m_malloc(sizeof(m_iterator_t), allocator);
	m_vector_iterator vector_iterator = (m_vector_iterator) m_malloc(
			sizeof(m_vector_iterator_t), allocator);
	m_vector_init_iterator(li, iter, vector_iterator);
	return iter;
}

static m_const_iterator_impl_t iterator_const_impl_vector_iterator = {
		//.has_next =
		m_iterator_impl_has_next,
		//.next =
		m_iterator_impl_next
};

void m_vector_init_const_iterator(m_vector v, m_const_iterator iter,
		m_vector_iterator vector_iterator) {
	vector_iterator->vec = v;
	vector_iterator->next_pos = 0;
	vector_iterator->removed = true;
	iter->impl = &iterator_const_impl_vector_iterator;
	iter->instance = vector_iterator;
}

m_const_iterator m_vector_const_iterate(m_vector li, m_allocator allocator) {
	m_const_iterator iter = (m_const_iterator) m_malloc(
			sizeof(m_const_iterator_t), allocator);
	m_vector_iterator vector_iterator = (m_vector_iterator) m_malloc(
			sizeof(m_vector_iterator_t), allocator);
	m_vector_init_const_iterator(li, iter, vector_iterator);
	return iter;
}
