/*
 * m_linked_list_iterator.c
 *
 *  Created on: 2016Äê10ÔÂ2ÈÕ
 *      Author: Stardust
 */

#include "m_linked_list_iterator.h"
#include <stdlib.h>
#include <stdbool.h>
#include "m_except.h"

bool m_linked_list_iterator_has_next(m_linked_list_iterator iter) {
	return iter->next_node != NULL;
}

m_element m_linked_list_iterator_next(m_linked_list_iterator iter) {
	if (!m_linked_list_iterator_has_next(iter)) {
		m_fatal_error_cstr(ILLEAGL_STATE,
						"m_linked_list_iterator next element does not exist");
	}
	m_element e = iter->next_node->value;
	iter->current_node = iter->next_node;
	iter->next_node = iter->next_node->next;
	return e;
}

void m_linked_list_iterator_remove(m_linked_list_iterator iter) {
	if (iter->current_node == NULL) {
		m_fatal_error_f(ILLEAGL_STATE,
				"m_linked_list_iterator_remove should be called only once after next");
	}
	m_linked_list_remove_node(iter->li, iter->current_node);
	iter->current_node = NULL;
}

static bool m_iterator_impl_has_next(m_iterator_instance iter) {
	return m_linked_list_iterator_has_next((m_linked_list_iterator) iter);
}

static m_element m_iterator_impl_next(m_iterator_instance iter) {
	return m_linked_list_iterator_next((m_linked_list_iterator) iter);
}

static void m_iterator_impl_remove(m_iterator_instance iter) {
	return m_linked_list_iterator_remove((m_linked_list_iterator) iter);
}

static m_iterator_impl_t iterator_impl_linked_list_iterator = {
	//.has_next =
	m_iterator_impl_has_next,
	//.next =
	m_iterator_impl_next,
	//.remove=
	m_iterator_impl_remove,
	//.free =
	NULL
};

void m_linked_list_init_iterator(m_linked_list li, m_iterator iter, m_linked_list_iterator linked_list_iterator) {
	linked_list_iterator->current_node = NULL;
	linked_list_iterator->li = li;
	linked_list_iterator->next_node = li->front;
	iter->impl = &iterator_impl_linked_list_iterator;
	iter->instance = linked_list_iterator;
}

m_iterator m_linked_list_iterate(m_linked_list li, m_allocator allocator) {
	 m_iterator iter = (m_iterator)m_malloc(sizeof(m_iterator_t), allocator);
	 m_linked_list_iterator linked_list_iterator = (m_linked_list_iterator)m_malloc(sizeof(m_linked_list_iterator_t), allocator);
	 m_linked_list_init_iterator(li, iter, linked_list_iterator);
	 return iter;
}

static m_const_iterator_impl_t iterator_const_impl_linked_list_iterator = {
	//.has_next =
	m_iterator_impl_has_next,
	//.next =
	m_iterator_impl_next
};

void m_linked_list_init_const_iterator(m_linked_list li, m_const_iterator iter, m_linked_list_iterator linked_list_iterator) {
	linked_list_iterator->current_node = NULL;
	linked_list_iterator->li = li;
	linked_list_iterator->next_node = li->front;
	iter->impl = &iterator_const_impl_linked_list_iterator;
	iter->instance = linked_list_iterator;
}

m_const_iterator m_linked_list_const_iterate(m_linked_list li, m_allocator allocator) {
	m_const_iterator iter = (m_const_iterator)m_malloc(sizeof(m_const_iterator_t), allocator);
	 m_linked_list_iterator linked_list_iterator = (m_linked_list_iterator)m_malloc(sizeof(m_linked_list_iterator_t), allocator);
	 m_linked_list_init_const_iterator(li, iter, linked_list_iterator);
	 return iter;
}
