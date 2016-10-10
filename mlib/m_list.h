#pragma once

#include "m_element.h"
#include "m_iterator.h"
#include "m_allocator.h"

struct m_list_impl_t;
typedef struct m_list_impl_t* m_list_impl;
typedef void* m_list_instance;

typedef struct m_list_t {
	m_list_impl impl;
	m_list_instance instance;
	m_allocator allocator;
} m_list_t;

typedef m_list_t* m_list;

typedef struct m_list_impl_t {
	size_t (*size)(m_list_instance li);
	m_element (*get)(m_list_instance li, size_t index);
	void (*add)(m_list_instance li, m_element e);
	void (*insert)(m_list_instance li, size_t index, m_element e);
	void (*remove)(m_list_instance li, size_t index);
	void (*set)(m_list_instance li, size_t index, m_element e);
	void (*clear)(m_list_instance li);
	bool (*remove_element)(m_list_instance li, m_element e);
	bool (*contains)(m_list_instance li, m_element e);
	void (*free)(m_list_instance li);
	m_iterator (*iterate)(m_list_instance li, m_allocator allocator);
} m_list_impl_t;

size_t m_list_size(m_list li);

m_element m_list_get(m_list li, size_t index);

/* 在列表末尾增加元素 */
void m_list_add(m_list li, m_element e);

/* 在第index + 1的元素的前面插入一个元素e */
void m_list_insert(m_list li, size_t index, m_element e);

void m_list_remove(m_list li, size_t index);

void m_list_set(m_list li, size_t index, m_element e);

void m_list_clear(m_list li);

m_list m_list_sublist(m_list li, size_t start, size_t end);

/* 移除一个元素e。至多只有一个。比较时调用m_element_equals,因此依赖于其实现。*/
bool m_list_remove_element(m_list li, m_element e);

/* 判断列表是否包括该元素 */
bool m_list_contains(m_list li, m_element e);

void m_list_free(m_list li);

m_iterator m_list_iterate(m_list li, m_allocator allocator);




