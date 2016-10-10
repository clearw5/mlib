/*
 * m_log.c
 *
 *  Created on: 2016年10月2日
 *      Author: Stardust
 */

#include "m_log.h"
#include <stdio.h>



const char *M_LOG_TYPE_NAME[] = {
		"ERROR",
		"INFO",
		"WARNING"
};

void m_log_f(m_log_type type, const char *format, ...){
	va_list ap;
	va_start(ap, format);
	m_log_vf(type, format, ap);
}

void m_log_err_f(const char *format, ...){
	va_list ap;
	va_start(ap, format);
	m_log_vf(M_LOG_TYPE_ERROR, format, ap);
}

void m_log_info_f(const char *format, ...){
	va_list ap;
	va_start(ap, format);
	m_log_vf(M_LOG_TYPE_INFO, format, ap);
}

void m_log_warn_f(const char *format, ...){
	va_list ap;
	va_start(ap, format);
	m_log_vf(M_LOG_TYPE_WARNING, format, ap);
}

void m_log_vf(m_log_type type, const char *format, va_list ap){
	if(LOG_ONLY_ERROR && type != M_LOG_TYPE_ERROR){
		return;
	}
	// TODO 输出到日志文件；添加时间信息。
	printf("[%s]", M_LOG_TYPE_NAME[type]);
	vprintf(format, ap);
	printf("\n");
}

void m_log_cstr(m_log_type type, const char *msg){
	m_log_f(type, "%s", msg);
}

void m_log_err_cstr(const char* msg){
	m_log_cstr(M_LOG_TYPE_ERROR, msg);
}

void m_log_info_cstr(const char* msg){
	m_log_cstr(M_LOG_TYPE_INFO, msg);
}

void m_log_warn_cstr(const char *msg){
	m_log_cstr(M_LOG_TYPE_WARNING, msg);
}

void m_log_str(m_log_type type, m_string msg){
	m_log_cstr(type, m_string_cstr(msg));
}

void m_log_err_str(m_string msg){
	m_log_cstr(M_LOG_TYPE_ERROR, m_string_cstr(msg));
}

void m_log_info_str(m_string msg){
	m_log_cstr(M_LOG_TYPE_INFO, m_string_cstr(msg));
}

void m_log_warn_str(m_string msg){
	m_log_cstr(M_LOG_TYPE_WARNING, m_string_cstr(msg));
}

void m_log_hex(m_log_type type, char *data, size_t size){
	printf("[%s]", M_LOG_TYPE_NAME[type]);
	for(index_t i = 0; i < size; i++){
		printf("%02x", (unsigned char)*data);
		data++;
	}
	printf("\n");

}
