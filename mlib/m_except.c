#include "m_except.h"

#include "stdio.h"
#include "stdlib.h"
#include "m_string.h"
#include "pthread.h"
#include <stdarg.h>

static error_exit_handler handler = NULL;

void m_exit(int i){
	if(handler == NULL){
		printf("Fatal error. Input E to exit.\n");
		while(getchar() != 'E');
		exit(i);
	}else{
		handler(i, pthread_self());
	}
}

const char *m_error_type_msg[] = {
			"OTHERS",
			"OUT_OF_BOUND",
			"BAD_ALLOCATION",
			"TYPE_INEQUIVALENCE",
			"UNIMPLEMENTED_ERROR",
			"ILLEAGL_ARGUMENT",
			"ILLEAGL_STATE",
			"SOCKET_ERROR",
			"NULL_POINTER"
};

const char *m_expect_type_to_cstr(m_expect_type type) {
	return m_error_type_msg[type];
}

void set_error_exit_handler(error_exit_handler h){
	handler = h;
}

void m_fatal_error(m_expect_type type, m_string error_msg) {
	m_fatal_error_cstr(type, m_string_cstr(error_msg));
}

void m_fatal_error_f(m_expect_type type, const char *fmt, ...) {
	printf("!!! Fatal error [%s] ", m_expect_type_to_cstr(type - 1));
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	printf("\n");
	m_exit(type);
}

void m_fatal_error_cstr(m_expect_type type, const char *error_msg) {
	printf("!!! Fatal error [%s] : %s \n", m_expect_type_to_cstr(type - 1), error_msg);
	m_exit(type);
}
