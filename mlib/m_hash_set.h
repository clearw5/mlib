/*
 * m_hash_set.h
 *
 *  Created on: 2016��10��3��
 *      Author: Stardust
 *
 * ��ϣ��
 * 1.����ָ����ϣ��������Ԫ�ع�ϣ������Ĭ��ʹ��CRC32�Ĳ����
 * 2.����������2�ı��������ָ������������2�ı���ʱ���Զ�����Ϊ2�ı���
 * 3.����С��������*load_factor(��������, Ĭ��0.75)ʱ��Ҫ��������������һ�������
 *   ��������Ҫ����Ϊÿ��Ԫ�ؼ����ϣ����λ�á���˾������ƺó�ʼ������
 * 4.����ϣ��ͻʱʹ��һ���Ӽ��ϱ����ͻԪ�أ�Ŀǰ�ü��ϲ������Ա�δ��������Ϊ�������
 * 5.clear��������չ�ϣ���������е��Ӽ���
 */

#ifndef MLIB_M_HASH_SET_H_
#define MLIB_M_HASH_SET_H_

#include "m_set.h"
#include "m_linked_list.h"
#include "m_allocator.h"
#include "m_hash_code.h"
#include <stdbool.h>

typedef m_hash (*m_element_hash_function)(m_element e);
#define M_ELEMENT_HASH_FUNCTION_DEFAULT NULL

typedef struct m_hash_set_t {
	size_t capacity;
	size_t size;
	float load_factor;
	m_allocator allocator;
	m_hash_function hash_function;
	m_element_hash_function element_hash_function;
	m_set *element_table;
	m_list element_table_nonnull_positions;
} m_hash_set_t;

typedef m_hash_set_t* m_hash_set;

typedef struct m_position_hash_pair_t {
	index_t pos;
	m_hash hash;
} m_position_hash_pair_t;

m_set m_hash_set_new_set(m_allocator allocator);

m_hash_set m_hash_set_new(size_t initial_capacity, float load_factor,
		m_hash_function hash_function, m_allocator allocator);

m_hash_set m_hash_set_new_custom_element_hash_function(size_t initial_capacity, float load_factor,
		m_element_hash_function element_hash_function, m_allocator allocator);

m_hash_set m_hash_set_new_def(m_allocator allocator);

void m_hash_set_add(m_hash_set s, m_element e);

bool m_hash_set_remove(m_hash_set s, m_element e);

size_t m_hash_set_size(m_hash_set s);

bool m_hash_set_empty(m_hash_set s);

bool m_hash_set_contains(m_hash_set s, m_element e);

void m_hash_set_clear(m_hash_set s);

void m_hash_set_free(m_hash_set s);

void m_hash_set_free_and_set_null(m_hash_set *s);



m_hash m_hash_set_element_hash(m_hash_set s, m_element e);

m_hash m_hash_set_secondary_hash(m_hash hash);

#endif /* MLIB_M_HASH_SET_H_ */
