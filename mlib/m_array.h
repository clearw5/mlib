/**
 * 泛型数组。
 * 不同与C的指针和STL的array，你可以随时获得数组长度。
 * 另外提供一些常用函数，例如数组复制，填充，排序等。
 * 数组的新建需要一个内存池，数组回收时不会把其元素回收。如果你想要让元素的生命周期与数组相同，可以这样做：
 * m_array a = m_array_new(10, m_allocator_new());
 * m_array_set(a, i, m_element_init_...(..., a->allocator));
 * 数组用完后通过m_allocator_destory(&a->allocator)一并回收数组与元素。
 *
 * TODO 增加更多的工具，例如数组比较，连接，foreach等函数
 */


#pragma once

#include <stdbool.h>
#include "m_allocator.h"
#include "m_element.h"


typedef struct m_array_t {
	/* 数组数据 */
	m_element *data;
	/* 数组长度 */
	size_t len;
	/* 内存池 */
	m_allocator allocator;
} m_array_t;

typedef m_array_t* m_array;

/* 数组元素比较函数，用于sort函数*/
typedef int (*m_element_compare_function)(const m_element*, const m_element*);
/* 用于qsort的比较函数 */
typedef int (*qsort_compare_function)(const void*, const void*);

/* 新建大小为size的数组。元素会被全部初始化为null。 */
m_array m_array_new(size_t size, m_allocator allocator);

/* Deprecated */
m_array m_array_new_def(size_t size);

/* Deprecated */
m_array m_array_tmp(size_t size);

/* 获取数组长度 */
size_t m_array_len(m_array a);

/* 获取数组在位置index处的元素 */
m_element m_array_at(m_array a, index_t index);

/* 设置数组在index处的元素 */
void m_array_set(m_array a, index_t index, m_element e);

/* 对数组重新分配大小 */
void m_array_realloc(m_array a, size_t len);

/* 把数组元素用字节0填充 */
void m_array_fill_byte_zero(m_array a);

/* 用e填充数组 */
void m_array_fill(m_array a, m_element e);

/* 数组复制 */
m_array m_array_clone(m_array a, m_allocator allocator);

/* 从位置from开始复制数组 */
m_array m_array_copy_from(m_array a, index_t from, m_allocator allocator);

/* 从位置from到end(不包括)复制数组 */
m_array m_array_copy(m_array a, index_t start, index_t end, m_allocator allocator);

/* 将数组src从srcPos的位置开始复制长度为length的内容到数组dest的destPos位置*/
void m_array_copy_into(m_array src, index_t srcPos, m_array dest, index_t destPos, size_t length);

/* 对数组升序排序，只能对原始数据类型使用（包括short, int, long, float, double, m_string)
 * 由于类型检查，效率大概为qsort的1/6*/
void m_array_sort_primitive_type_ascending(m_array a);

/* 对数组降序排序，只能对原始数据类型使用（包括short, int, long, float, double, m_string)
 * 由于类型检查和判断，效率大概为qsort的1/6 */
void m_array_sort_primitive_type_descending(m_array a);

/* 对数组降序排序，使用qsort实现。由于类型检查，效率大概为qsort的1/4*/
void m_array_sort(m_array a, m_element_compare_function cmp);

/* 释放数组。但并不释放每个元素。（short,int,long,double,float类型是不需要释放的）*/
void m_array_free(m_array a);

/* 释放数组并设置为null */
void m_array_free_and_set_null(m_array *a);
