/**
 * ����������ͬ��c++�ĵ�����������ĵ������ĺ�����java���ƣ�
 * 1. ��has_next�����ж��Ƿ�����һ��Ԫ��
 * 2. ��next������ȡ��һ��Ԫ�ز��ƶ�������
 * 3. ��remove����ɾ��Ԫ��
 * 4. һ��ʼ������λ�ڵ�һ��Ԫ��֮ǰ��Ҳ����һ�������ĵ������£�
 *   while(m_iterator_has_next(iter)){
 *   	m_element e = m_iterator_next(iter);
 *   	// �������������m_iterator_removeɾ��e������������ʧЧ��
 *  }
 *  const_iterator����remove
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

