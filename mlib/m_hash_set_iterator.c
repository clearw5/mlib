/*
 * m_hash_set_iterator.c
 *
 *  Created on: 2016年10月3日
 *      Author: Stardust
 */

#include "m_hash_set_iterator.h"

/*
 * m_hash_set_iterator.c
 *
 *  Created on: 2016年10月2日
 *      Author: Stardust
 */

#include "m_hash_set_iterator.h"
#include "m_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include "m_except.h"

#define M_LIST_NONE NULL

static void m_hash_set_iterator_check_next_list_existanse(
		m_hash_set_iterator iter) {
	while (m_iterator_has_next(iter->nonnull_position_iterator)) {
		int i = m_int(m_iterator_next(iter->nonnull_position_iterator));
		iter->next_subset_iter = m_set_iterate(iter->hash_set->element_table[i],
				iter->allocator);
		if (m_iterator_has_next(iter->next_subset_iter)) {
			iter->has_next = true;
			return;
		} else {
			m_iterator_free(iter->next_subset_iter, iter->allocator);
			iter->next_subset_iter = NULL;
		}
	}
	iter->has_next = false;
}

bool m_hash_set_iterator_has_next(m_hash_set_iterator iter) {
	return iter->has_next;
}

m_element m_hash_set_iterator_next(m_hash_set_iterator iter) {
	if (!iter->has_next) {
		m_fatal_error_cstr(ILLEAGL_STATE,
				" m_hash_set_iterator next element does not exist");
	}
	if (iter->next_subset_iter != NULL) {
		if (iter->subset_iter != NULL)
			m_iterator_free(iter->subset_iter, iter->allocator);
		iter->subset_iter = iter->next_subset_iter;
		iter->next_subset_iter = NULL;
	}
	m_element e = m_iterator_next(iter->subset_iter);
	if (!m_iterator_has_next(iter->subset_iter)) {
		m_hash_set_iterator_check_next_list_existanse(iter);
	}
	return e;
}

void m_hash_set_iterator_remove(m_hash_set_iterator iter) {
	m_iterator_remove(iter->subset_iter);
}

void m_hash_set_iterator_free(m_hash_set_iterator iter) {
	if (iter->subset_iter != NULL) {
		m_iterator_free(iter->subset_iter, iter->allocator);
	}
	m_iterator_free(iter->nonnull_position_iterator, iter->allocator);
	m_free(iter, iter->allocator);
}

static bool m_iterator_impl_has_next(m_iterator_instance iter) {
	return m_hash_set_iterator_has_next((m_hash_set_iterator) iter);
}

static m_element m_iterator_impl_next(m_iterator_instance iter) {
	return m_hash_set_iterator_next((m_hash_set_iterator) iter);
}

static void m_iterator_impl_remove(m_iterator_instance iter) {
	return m_hash_set_iterator_remove((m_hash_set_iterator) iter);
}

static void m_iterator_impl_free(m_iterator_instance iter) {
	m_hash_set_iterator_free((m_hash_set_iterator) iter);
}

static m_iterator_impl_t iterator_impl_hash_set_iterator = {
//.has_next =
		m_iterator_impl_has_next,
		//.next =
		m_iterator_impl_next,
		//.remove=
		m_iterator_impl_remove, m_iterator_impl_free };

static void m_hash_set_iterator_init(m_hash_set s,
		m_hash_set_iterator hash_set_iterator, m_allocator allocator) {
	hash_set_iterator->allocator = allocator;
	hash_set_iterator->hash_set = s;
	hash_set_iterator->nonnull_position_iterator = m_list_iterate(
			s->element_table_nonnull_positions, allocator);
	hash_set_iterator->next_subset_iter = NULL;
	hash_set_iterator->subset_iter = NULL;
	m_hash_set_iterator_check_next_list_existanse(hash_set_iterator);
}

m_iterator m_hash_set_iterate(m_hash_set s, m_allocator allocator) {
	m_iterator iter = (m_iterator) m_malloc(sizeof(m_iterator_t), allocator);
	m_hash_set_iterator hash_set_iterator = (m_hash_set_iterator) m_malloc(
			sizeof(m_hash_set_iterator_t), allocator);
	m_hash_set_iterator_init(s, hash_set_iterator, allocator);
	iter->impl = &iterator_impl_hash_set_iterator;
	iter->instance = hash_set_iterator;
	return iter;
}

static m_const_iterator_impl_t iterator_const_impl_hash_set_iterator = {
//.has_next =
		m_iterator_impl_has_next,
		//.next =
		m_iterator_impl_next };

m_const_iterator m_hash_set_const_iterate(m_hash_set s, m_allocator allocator) {
	m_const_iterator iter = (m_const_iterator) m_malloc(
			sizeof(m_const_iterator_t), allocator);
	m_hash_set_iterator hash_set_iterator = (m_hash_set_iterator) m_malloc(
			sizeof(m_hash_set_iterator_t), allocator);
	m_hash_set_iterator_init(s, hash_set_iterator, allocator);
	iter->impl = &iterator_const_impl_hash_set_iterator;
	iter->instance = hash_set_iterator;
	return iter;
}
