/**
 * �������顣
 * ��ͬ��C��ָ���STL��array���������ʱ������鳤�ȡ�
 * �����ṩһЩ���ú������������鸴�ƣ���䣬����ȡ�
 * ������½���Ҫһ���ڴ�أ��������ʱ�������Ԫ�ػ��ա��������Ҫ��Ԫ�ص�����������������ͬ��������������
 * m_array a = m_array_new(10, m_allocator_new());
 * m_array_set(a, i, m_element_init_...(..., a->allocator));
 * ���������ͨ��m_allocator_destory(&a->allocator)һ������������Ԫ�ء�
 *
 * TODO ���Ӹ���Ĺ��ߣ���������Ƚϣ����ӣ�foreach�Ⱥ���
 */


#pragma once

#include <stdbool.h>
#include "m_allocator.h"
#include "m_element.h"


typedef struct m_array_t {
	/* �������� */
	m_element *data;
	/* ���鳤�� */
	size_t len;
	/* �ڴ�� */
	m_allocator allocator;
} m_array_t;

typedef m_array_t* m_array;

/* ����Ԫ�رȽϺ���������sort����*/
typedef int (*m_element_compare_function)(const m_element*, const m_element*);
/* ����qsort�ıȽϺ��� */
typedef int (*qsort_compare_function)(const void*, const void*);

/* �½���СΪsize�����顣Ԫ�ػᱻȫ����ʼ��Ϊnull�� */
m_array m_array_new(size_t size, m_allocator allocator);

/* Deprecated */
m_array m_array_new_def(size_t size);

/* Deprecated */
m_array m_array_tmp(size_t size);

/* ��ȡ���鳤�� */
size_t m_array_len(m_array a);

/* ��ȡ������λ��index����Ԫ�� */
m_element m_array_at(m_array a, index_t index);

/* ����������index����Ԫ�� */
void m_array_set(m_array a, index_t index, m_element e);

/* ���������·����С */
void m_array_realloc(m_array a, size_t len);

/* ������Ԫ�����ֽ�0��� */
void m_array_fill_byte_zero(m_array a);

/* ��e������� */
void m_array_fill(m_array a, m_element e);

/* ���鸴�� */
m_array m_array_clone(m_array a, m_allocator allocator);

/* ��λ��from��ʼ�������� */
m_array m_array_copy_from(m_array a, index_t from, m_allocator allocator);

/* ��λ��from��end(������)�������� */
m_array m_array_copy(m_array a, index_t start, index_t end, m_allocator allocator);

/* ������src��srcPos��λ�ÿ�ʼ���Ƴ���Ϊlength�����ݵ�����dest��destPosλ��*/
void m_array_copy_into(m_array src, index_t srcPos, m_array dest, index_t destPos, size_t length);

/* ��������������ֻ�ܶ�ԭʼ��������ʹ�ã�����short, int, long, float, double, m_string)
 * �������ͼ�飬Ч�ʴ��Ϊqsort��1/6*/
void m_array_sort_primitive_type_ascending(m_array a);

/* �����齵������ֻ�ܶ�ԭʼ��������ʹ�ã�����short, int, long, float, double, m_string)
 * �������ͼ����жϣ�Ч�ʴ��Ϊqsort��1/6 */
void m_array_sort_primitive_type_descending(m_array a);

/* �����齵������ʹ��qsortʵ�֡��������ͼ�飬Ч�ʴ��Ϊqsort��1/4*/
void m_array_sort(m_array a, m_element_compare_function cmp);

/* �ͷ����顣�������ͷ�ÿ��Ԫ�ء���short,int,long,double,float�����ǲ���Ҫ�ͷŵģ�*/
void m_array_free(m_array a);

/* �ͷ����鲢����Ϊnull */
void m_array_free_and_set_null(m_array *a);
