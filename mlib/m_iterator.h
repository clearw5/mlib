/**
 * 迭代器。不同于c++的迭代器，这里的迭代器的函数与java相似：
 * 1. 用has_next函数判断是否有下一个元素
 * 2. 用next函数获取下一个元素并移动迭代器
 * 3. 用remove函数删除元素
 * 4. 一开始迭代器位于第一个元素之前，也就是一个完整的迭代如下：
 *   while(m_iterator_has_next(iter)){
 *   	m_element e = m_iterator_next(iter);
 *   	// 可以在这里调用m_iterator_remove删除e。迭代器不会失效。
 *  }
 *  const_iterator不能remove
 */



#pragma once

#include <stdbool.h>
#include "m_element.h"

typedef void* m_iterator_instance;
typedef struct m_iterator_impl_t* m_iterator_impl;

typedef struct m_iterator_t {
	m_iterator_impl impl;
	m_iterator_instance instance;
} m_iterator_t;

typedef m_iterator_t* m_iterator;

typedef struct m_iterator_impl_t {
	bool (*has_next)(m_iterator_instance);
	m_element (*next)(m_iterator_instance);
	void (*remove)(m_iterator_instance);
	void (*free)(m_iterator_instance);
} m_iterator_impl_t;


bool m_iterator_has_next(m_iterator iter);

m_element m_iterator_next(m_iterator iter);

void m_iterator_remove(m_iterator iter);

void m_iterator_free(m_iterator iter, m_allocator allocator);


typedef void* m_const_iterator_instance;
typedef struct m_const_iterator_impl_t* m_const_iterator_impl;

typedef struct m_const_iterator_t {
	m_const_iterator_impl impl;
	m_const_iterator_instance instance;
} m_const_iterator_t;

typedef m_const_iterator_t* m_const_iterator;

typedef struct m_const_iterator_impl_t {
	bool (*has_next)(m_const_iterator_instance);
	m_element (*next)(m_const_iterator_instance);
} m_const_iterator_impl_t;



bool m_const_iterator_has_next(m_const_iterator iter);

m_element m_const_iterator_next(m_const_iterator iter);

void m_const_iterator_free(m_const_iterator iter, m_allocator allocator);

