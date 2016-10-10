#pragma once

#include "m_string.h"
#include "pthread.h"

/* �쳣�˳���������e�ǵ���exit()ʱ���������һ����˵��ʾ�����루ȡ���ڵ����쳣�˳�������ʱ����Ĳ�������p�Ƿ����쳣���̡߳�*/
typedef void (*error_exit_handler)(int e, pthread_t p);

typedef enum m_expect_type {
	/* �����쳣 */
	OTHERS = 1,
	/* Խ�硣�������顣*/
	OUT_OF_BOUNDS,
	/* �޷�������ڴ档Ҳ��malloc��realloc����NULL��*/
	BAD_ALLOCATION,
	/* ���Ͳ�ƥ�� */
	TYPE_INEQUIVALENCE,
	/* ����δʵ�� */
	UNIMPLEMENTED_ERROR,
	/* ���Ϸ����� */
	ILLEAGL_ARGUMENT,
	/* ���Ϸ�״̬ */
	ILLEAGL_STATE,
	/* SOCKET ���� */
	SOCKET_ERROR,
	/* ��ָ���쳣 */
	NULL_POINTER
} m_expect_type;

const char *m_expect_type_to_cstr(m_expect_type type);

/* �����쳣�˳��Ĵ���*/
void set_error_exit_handler(error_exit_handler h);

/* �쳣�˳�������*/
void m_fatal_error(m_expect_type type, m_string error_msg);

/* �쳣�˳���������������printfһ����ʽ���������Ϣ */
void m_fatal_error_f(m_expect_type type, const char *fmt, ...);

void m_fatal_error_cstr(m_expect_type type, const char *error_msg);


