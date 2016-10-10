#include "m_element.h"
#include "m_allocator.h"
#include <memory.h>
#include "m_except.h"

static void m_element_init_inner(m_element *e, m_type type, size_t size) {
	e->type = type;
	e->size = size;
}

m_element m_element_init(m_pointer data, size_t size, m_type type,
		m_allocator allocator) {
	if (m_type_equals(type, M_TYPE_STRING)) {
		return m_element_init_str(
				m_string_new_a((const char*) data, size, allocator));
	}
	m_element e;
	m_element_init_inner(&e, type, size);
	if (m_type_is_primitive_type(type)) {
		memcpy(&e.value, data, size);
	} else {
		e.value.ptr = (m_pointer) m_malloc(size, allocator);
		memcpy(e.value.ptr, data, size);
	}
	return e;
}

m_element m_element_init_c(char value) {
	m_element e;
	e.value.c = value;
	m_element_init_inner(&e, M_TYPE_CHAR, sizeof(char));
	return e;
}

m_element m_element_init_s(short value) {
	m_element e;
	e.value.s = value;
	m_element_init_inner(&e, M_TYPE_SHORT, sizeof(short));
	return e;
}

m_element m_element_init_i(int value) {
	m_element e;
	e.value.i = value;
	m_element_init_inner(&e, M_TYPE_INT, sizeof(int));
	return e;
}

m_element m_element_init_l(long value) {
	m_element e;
	e.value.l = value;
	m_element_init_inner(&e, M_TYPE_LONG, sizeof(long));
	return e;
}

m_element m_element_init_f(float value) {
	m_element e;
	e.value.f = value;
	m_element_init_inner(&e, M_TYPE_FLOAT, sizeof(float));
	return e;
}

m_element m_element_init_d(double value) {
	m_element e;
	e.value.d = value;
	m_element_init_inner(&e, M_TYPE_DOUBLE, sizeof(double));
	return e;
}

m_element m_element_init_str(m_string str) {
	m_element e;
	m_element_init_inner(&e, M_TYPE_STRING, str->len);
	e.value.ptr = str;
	return e;
}

m_element m_element_init_str_clone(m_string str, m_allocator allocator) {
	m_string clone = m_string_new(str, allocator);
	return m_element_init_str(clone);
}

m_element m_element_init_cstr(const char *cstr){
	m_element e;
	m_element_init_inner(&e, M_TYPE_CSTRING, strlen(cstr));
	e.value.ptr = (m_pointer) cstr;
	return e;
}

m_element m_element_init_cstr_clone(const char *cstr, m_allocator a){
	m_element e;
	m_element_init_inner(&e, M_TYPE_CSTRING, strlen(cstr) + 1);
	char *clone = (char*)m_malloc(e.size, a);
	memcpy(clone, m_cstr(e), e.size + 1);
	e.value.ptr = clone;
	return e;
}

m_element m_element_init_ptr(m_pointer ptr, m_type type) {
	m_element e;
	e.value.ptr = ptr;
	m_element_init_inner(&e, type, sizeof(m_pointer));
	return e;
}

m_element m_element_init_ptr_c(char *ptr) {
	return m_element_init_ptr(ptr, M_TYPE_CHAR_PTR);
}

m_element m_element_init_ptr_s(short *ptr) {
	return m_element_init_ptr(ptr, M_TYPE_SHORT_PTR);
}

m_element m_element_init_ptr_i(int *ptr) {
	return m_element_init_ptr(ptr, M_TYPE_INT_PTR);
}

m_element m_element_init_ptr_l(long *ptr) {
	return m_element_init_ptr(ptr, M_TYPE_LONG_PTR);
}

m_element m_element_init_ptr_f(float *ptr) {
	return m_element_init_ptr(ptr, M_TYPE_FLOAT_PTR);
}

m_element m_element_init_ptr_d(double *ptr) {
	return m_element_init_ptr(ptr, M_TYPE_DOUBLE_PTR);
}

m_element m_element_init_ptr_str(m_string *str) {
	return m_element_init_ptr(str, M_TYPE_STRING_PTR);
}

m_element m_element_tmp(m_pointer data, size_t size, m_type type) {
	return m_element_init(data, size, type, ALLOCATOR_TEMP);
}

m_element m_element_null() {
	m_element e;
	e.size = 0;
	e.type = NULL;
	return e;
}

bool m_element_is_null(m_element e) {
	return e.type == NULL;
}
char m_char(m_element e) {
	m_type_assert_type(e.type, M_TYPE_CHAR);
	return e.value.c;
}

short m_short(m_element e) {
	m_type_assert_type(e.type, M_TYPE_SHORT);
	return e.value.s;
}

int m_int(m_element e) {
	m_type_assert_type(e.type, M_TYPE_INT);
	return e.value.i;
}

long m_long(m_element e) {
	m_type_assert_type(e.type, M_TYPE_LONG);
	return e.value.l;
}

float m_float(m_element e) {
	m_type_assert_type(e.type, M_TYPE_FLOAT);
	return e.value.f;
}

double m_double(m_element e) {
	m_type_assert_type(e.type, M_TYPE_DOUBLE);
	return e.value.d;
}

m_string m_str_clone(m_element e, m_allocator allocator) {
	return m_string_new(m_str(e), allocator);
}

m_string m_str(m_element e) {
	m_type_assert_type(e.type, M_TYPE_STRING);
	return (m_string) e.value.ptr;
}

const char *m_cstr(m_element e){
	return (char*) e.value.ptr;
}

char *m_cstr_clone(m_element e, m_allocator a){
	char *clone = m_malloc(e.size, a);
	memcpy(clone, m_cstr(e), e.size + 1);
	return clone;
}

m_pointer m_ptr(m_element e, m_type type) {
	m_type_assert_type_ptr(e.type, true);
	m_type_assert_type(e.type, type);
	return e.value.ptr;
}

char *m_char_ptr(m_element e) {
	m_type_assert_type(e.type, M_TYPE_CHAR_PTR);
	return (char*) e.value.ptr;
}

short *m_short_ptr(m_element e) {
	m_type_assert_type(e.type, M_TYPE_SHORT_PTR);
	return (short*) e.value.ptr;
}

int *m_int_ptr(m_element e) {
	m_type_assert_type(e.type, M_TYPE_INT_PTR);
	return (int*) e.value.ptr;
}

long *m_long_ptr(m_element e) {
	m_type_assert_type(e.type, M_TYPE_LONG_PTR);
	return (long*) e.value.ptr;
}

float *m_float_ptr(m_element e) {
	m_type_assert_type(e.type, M_TYPE_FLOAT_PTR);
	return (float*) e.value.ptr;
}

double *m_double_ptr(m_element e) {
	m_type_assert_type(e.type, M_TYPE_DOUBLE_PTR);
	return (double*) e.value.ptr;
}

m_string *m_string_ptr(m_element e) {
	m_type_assert_type(e.type, M_TYPE_STRING_PTR);
	return (m_string*) e.value.ptr;
}

m_pointer m_element_get_data_ptr(m_element *e) {
	if (e->type->is_pointer || m_type_is_primitive_type(e->type)) {
		return (m_pointer) &e->value;
	}
	if(m_type_equals(e->type, M_TYPE_STRING)){
		return m_str(*e)->data;
	}
	return (m_pointer) e->value.ptr;
}

bool m_element_equals(m_element lhs, m_element rhs) {
	if (lhs.size != rhs.size || !m_type_equals(lhs.type, rhs.type)) {
		return false;
	}
	if (m_type_equals(lhs.type, M_TYPE_STRING)) {
		return m_string_equals(m_str(lhs), m_str(rhs));
	}
	return memcmp(m_element_get_data_ptr(&lhs), m_element_get_data_ptr(&rhs),
			lhs.size) == 0;
}

int m_element_compare_primitive_type_less_than(m_element l, m_element r) {
	m_type_assert_type(l.type, r.type);
	m_type type = l.type;
	if (m_type_equals(type, M_TYPE_CHAR)) {
		return m_char(l) < m_char(r) ? 1 : m_char(l) == m_char(r) ? 0 : -1;
	}
	if (m_type_equals(type, M_TYPE_SHORT)) {
		return m_short(l) < m_short(r) ? 1 : m_short(l) == m_short(r) ? 0 : -1;
	}
	if (m_type_equals(type, M_TYPE_INT)) {
		return m_int(l) < m_int(r) ? 1 : m_int(l) == m_int(r) ? 0 : -1;
	}
	if (m_type_equals(type, M_TYPE_LONG)) {
		return m_long(l) < m_long(r) ? 1 : m_long(l) == m_long(r) ? 0 : -1;
	}
	if (m_type_equals(type, M_TYPE_FLOAT)) {
		return m_float(l) < m_float(r) ? 1 : m_float(l) == m_float(r) ? 0 : -1;
	}
	if (m_type_equals(type, M_TYPE_DOUBLE)) {
		return m_double(l) < m_double(r) ? 1 :
				m_double(l) == m_double(r) ? 0 : -1;
	}
	if (m_type_equals(type, M_TYPE_STRING)) {
		return m_string_compare(m_str(l), m_str(r));
	}
	m_fatal_error_f(ILLEAGL_ARGUMENT,
			"m_element_compare_primitive_type_less_than only compares for primitive type: type=%s",
			l.type->name);
	return 0;
}

int m_element_compare_primitive_type_greater_than(m_element l, m_element r) {
	return -m_element_compare_primitive_type_less_than(l, r);
}

void m_element_free(m_element e, m_allocator allocator) {
	if (m_type_equals(e.type, M_TYPE_STRING)) {
		m_string_free(m_str(e));
	}
	if (e.type->is_pointer || m_type_is_primitive_type(e.type)) {
		return;
	}
	m_free(e.value.ptr, allocator);
}
