/*
 * m_hash_set.h
 *
 *  Created on: 2016年10月3日
 *      Author: Stardust
 *
 * 哈希表。
 * 1.可以指定哈希函数或者元素哈希函数，默认使用CRC32的查表法。
 * 2.容量必须是2的倍数，如果指定的容量不是2的倍数时会自动扩充为2的倍数
 * 3.当大小大于容量*load_factor(负载因子, 默认0.75)时需要扩充容量，这是一个昂贵的
 *   操作，需要重新为每个元素计算哈希分配位置。因此尽量估计好初始容量。
 * 4.但哈希冲突时使用一个子集合保存冲突元素，目前该集合采用线性表，未来将更换为红黑树。
 * 5.clear操作会清空哈希表并回收所有的子集合
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
