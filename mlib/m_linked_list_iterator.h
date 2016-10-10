/*
 * m_linked_list_iterator.h
 *
 *  Created on: 2016Äê10ÔÂ2ÈÕ
 *      Author: Stardust
 */

#ifndef MLIB_M_LINKED_LIST_ITERATOR_H_
#define MLIB_M_LINKED_LIST_ITERATOR_H_

#include "m_linked_list.h"

typedef struct m_linked_list_iterator_t {
	m_linked_list_node *current_node;
	m_linked_list_node *next_node;
	m_linked_list li;
} m_linked_list_iterator_t;

typedef m_linked_list_iterator_t* m_linked_list_iterator;


void m_linked_list_init_iterator(m_linked_list li, m_iterator iter, m_linked_list_iterator linked_list_iterator);

m_iterator m_linked_list_iterate(m_linked_list li, m_allocator allocator);

void m_linked_list_init_const_iterator(m_linked_list li, m_const_iterator iter, m_linked_list_iterator linked_list_iterator);

m_const_iterator m_linked_list_const_iterate(m_linked_list li, m_allocator allocator);



#endif /* MLIB_M_LINKED_LIST_ITERATOR_H_ */
