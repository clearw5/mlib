#pragma once

#include "m_string.h"
#include "pthread.h"

/* 异常退出处理函数。e是调用exit()时传入参数，一般来说表示错误码（取决于调用异常退出函数的时候传入的参数）。p是发送异常的线程。*/
typedef void (*error_exit_handler)(int e, pthread_t p);

typedef enum m_expect_type {
	/* 其他异常 */
	OTHERS = 1,
	/* 越界。例如数组。*/
	OUT_OF_BOUNDS,
	/* 无法分配堆内存。也即malloc或realloc返回NULL。*/
	BAD_ALLOCATION,
	/* 类型不匹配 */
	TYPE_INEQUIVALENCE,
	/* 函数未实现 */
	UNIMPLEMENTED_ERROR,
	/* 不合法参数 */
	ILLEAGL_ARGUMENT,
	/* 不合法状态 */
	ILLEAGL_STATE,
	/* SOCKET 错误 */
	SOCKET_ERROR,
	/* 空指针异常 */
	NULL_POINTER
} m_expect_type;

const char *m_expect_type_to_cstr(m_expect_type type);

/* 设置异常退出的处理*/
void set_error_exit_handler(error_exit_handler h);

/* 异常退出函数。*/
void m_fatal_error(m_expect_type type, m_string error_msg);

/* 异常退出函数。可以类似printf一样格式输出错误信息 */
void m_fatal_error_f(m_expect_type type, const char *fmt, ...);

void m_fatal_error_cstr(m_expect_type type, const char *error_msg);


