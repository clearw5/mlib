/**
 *
 * 类型。这是本库中类型检查的基础。
 * 内建了基本类型和m_string及其对应的指针类型。
 * 类型依赖于类型名称，类型名称相同的类型会被认为是同一种类型。
 *
 *
 * TODO 更高效的类型检查、判断
 * 		类型名不是很可靠，很容易出现冲突。
 */


#pragma once

#include <stdbool.h>
#include "m_allocator.h"
#include "m_string.h"

typedef struct m_type_t {
	/* 类型名称 */
	const char *name;
	/* 标记是否是指针类型 */
	bool is_pointer;
} m_type_t;

typedef m_type_t* m_type;

extern m_type M_TYPE_CHAR, M_TYPE_SHORT, M_TYPE_INT, M_TYPE_LONG, M_TYPE_FLOAT,
		M_TYPE_DOUBLE, M_TYPE_STRING, M_TYPE_CSTRING, M_TYPE_CHAR_PTR, M_TYPE_SHORT_PTR,
		M_TYPE_INT_PTR, M_TYPE_LONG_PTR, M_TYPE_FLOAT_PTR, M_TYPE_DOUBLE_PTR,
		M_TYPE_STRING_PTR, M_TYPE_PTR, M_TYPE_CSTRING_PTR;

m_type m_type_new(const char *type_name, bool is_ptr);

m_type m_type_new_type(const char *type_name);

m_type m_type_new_ptr_type(const char *type_name);

/* 类型比较。比较类型名称和是否为指针。*/
bool m_type_equals(m_type lhs, m_type rhs);

/* 类型不相同时异常退出 */
void m_type_assert_type(m_type type, m_type except_type);

/* 类型不是指针时异常退出 */
void m_type_assert_type_ptr(m_type type, bool is_ptr);

/* 判断是否是6中基本类型（目前不包括unsigned类型）*/
bool m_type_is_primitive_type(m_type type);

/* 全名。其实就是在指针类型后面加上星号 */
m_string m_type_get_full_type_name(m_type type, m_allocator allocator);

