/**
 * 双端链表。
 * 实现了列表和线性查找的集合。
 * 函数命名均与java相同。参见java文档。其实看名字也知道是什么啦。
 */


#pragma once

#include "m_pointer.h"
#include "m_list.h"
#include "m_set.h"
#include "m_element.h"
#include "m_allocator.h"
#include "m_iterator.h"

typedef struct m_linked_list_node {
	struct m_linked_list_node *previous;
	struct m_linked_list_node *next;
	m_element value;
} m_linked_list_node;

typedef struct m_linked_list_t {
	m_linked_list_node *front;
	m_linked_list_node *rear;
	size_t size;
	m_allocator allocator;
} m_linked_list_t;

typedef m_linked_list_t* m_linked_list;

m_linked_list m_linked_list_new(m_allocator allocator);

/* 创建一个用链表实现的列表 */
m_list m_linked_list_new_list(m_allocator allocator);

m_set m_linked_list_new_set(m_allocator allocator);

size_t m_linked_list_size(m_linked_list li);

void m_linked_list_add(m_linked_list li, m_element e);

m_element m_linked_list_get(m_linked_list li, size_t index);

void m_linked_list_insert(m_linked_list li, size_t index, m_element e);

void m_linked_list_remove(m_linked_list li, size_t index);

void m_linked_list_clear(m_linked_list li);

void  m_linked_list_set(m_linked_list li, size_t index, m_element e);

bool  m_linked_list_contains(m_linked_list li, m_element e);

bool m_linked_list_empty(m_linked_list li);

bool m_linked_list_remove_element(m_linked_list li, m_element e);

void m_linked_list_free(m_linked_list li);

m_linked_list m_linked_list_sublist(m_linked_list li, size_t start, size_t end);


/* @hide: should not be used */
void m_linked_list_remove_node(m_linked_list li, m_linked_list_node *node);

