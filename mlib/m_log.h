/*
 * m_log.h
 *
 *  Created on: 2016年10月2日
 *      Author: Stardust
 */

#ifndef MLIB_M_LOG_H_
#define MLIB_M_LOG_H_

#include <stdarg.h>
#include "m_string.h"

#define LOG_ONLY_ERROR 1

typedef enum m_log_type {
	M_LOG_TYPE_ERROR = 0,
	M_LOG_TYPE_INFO,
	M_LOG_TYPE_WARNING
} m_log_type;

void m_log_f(m_log_type type, const char *format, ...);

void m_log_err_f(const char *format, ...);

void m_log_info_f(const char *format, ...);

void m_log_warn_f(const char *format, ...);

void m_log_vf(m_log_type type, const char *format, va_list ap);

void m_log_cstr(m_log_type type, const char *msg);

void m_log_err_cstr(const char* msg);

void m_log_info_cstr(const char* msg);

void m_log_warn_cstr(const char *msg);

void m_log_str(m_log_type type, m_string msg);

void m_log_err_str(m_string msg);

void m_log_info_str(m_string msg);

void m_log_warn_str(m_string msg);

/* 将一段数据以16进制的形式记录起来 */
void m_log_hex(m_log_type type, char *data, size_t size);


#endif /* MLIB_M_LOG_H_ */
