/**
 *
 * ���͡����Ǳ��������ͼ��Ļ�����
 * �ڽ��˻������ͺ�m_string�����Ӧ��ָ�����͡�
 * �����������������ƣ�����������ͬ�����ͻᱻ��Ϊ��ͬһ�����͡�
 *
 *
 * TODO ����Ч�����ͼ�顢�ж�
 * 		���������Ǻܿɿ��������׳��ֳ�ͻ��
 */


#pragma once

#include <stdbool.h>
#include "m_allocator.h"
#include "m_string.h"

typedef struct m_type_t {
	/* �������� */
	const char *name;
	/* ����Ƿ���ָ������ */
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

/* ���ͱȽϡ��Ƚ��������ƺ��Ƿ�Ϊָ�롣*/
bool m_type_equals(m_type lhs, m_type rhs);

/* ���Ͳ���ͬʱ�쳣�˳� */
void m_type_assert_type(m_type type, m_type except_type);

/* ���Ͳ���ָ��ʱ�쳣�˳� */
void m_type_assert_type_ptr(m_type type, bool is_ptr);

/* �ж��Ƿ���6�л������ͣ�Ŀǰ������unsigned���ͣ�*/
bool m_type_is_primitive_type(m_type type);

/* ȫ������ʵ������ָ�����ͺ�������Ǻ� */
m_string m_type_get_full_type_name(m_type type, m_allocator allocator);

