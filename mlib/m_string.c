/*
 * m_string.c
 *
 *  Created on: 2016Äê10ÔÂ1ÈÕ
 *      Author: Stardust
 */

#include "m_string.h"
#include "m_allocator.h"
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "m_except.h"
#include "m_list.h"

typedef m_string_t* m_string;

m_string m_string_new_hole(m_allocator allocator, size_t capacity) {
	m_string str = (m_string) m_malloc(sizeof(m_string_t), allocator);
	str->allocator = allocator;
	str->len = 0;
	str->data = (char*) m_malloc(sizeof(char) * (capacity + 1), allocator);
	str->data[0] = '\0';
	str->capacity = capacity;
	return str;
}

m_string m_string_new_empty(m_allocator allocator) {
	return m_string_new_hole(allocator, 0);
}

m_string m_string_new_with_capacity(m_string str, size_t capacity,
		m_allocator allocator) {
	return m_string_new_a_with_capacity(str->data, str->len, capacity,
			allocator);
}
m_string m_string_new(m_string str, m_allocator allocator) {
	return m_string_new_a(str->data, str->len, allocator);
}

m_string m_string_new_cstr(const char *str, m_allocator allocator) {
	return m_string_new_a(str, strlen(str), allocator);
}

m_string m_string_new_c(char c, m_allocator allocator) {
	return m_string_new_a(&c, 1, allocator);
}

m_string m_string_new_a_with_capacity(const char *ch, size_t size,
		size_t capacity, m_allocator allocator) {
	if (capacity < size) {
		m_fatal_error_f(ILLEAGL_ARGUMENT,
				"illegal capacity on m_string_new_a_with_capacity: capacity=%ud, size=%ud",
				capacity, size);
	}
	m_string new_str = m_string_new_hole(allocator, capacity);
	if (size > 0) {
		memcpy(new_str->data, ch, sizeof(char) * size);
	}
	new_str->data[size] = '\0';
	new_str->len = size;
	new_str->capacity = capacity;
	return new_str;
}

m_string m_string_new_a(const char *ch, size_t size, m_allocator allocator) {
	return m_string_new_a_with_capacity(ch, size, size + 1, allocator);
}

m_string m_string_new_s(short s, m_allocator allocator) {
	char str[20];
	sprintf(str, "%hd", s);
	return m_string_new_cstr(str, allocator);
}

m_string m_string_new_i(int i, m_allocator allocator) {
	char str[20];
	sprintf(str, "%d", i);
	return m_string_new_cstr(str, allocator);
}

m_string m_string_new_l(long l, m_allocator allocator) {
	char str[30];
	sprintf(str, "%ld", l);
	return m_string_new_cstr(str, allocator);
}

m_string m_string_new_f(float f, m_allocator allocator) {
	char str[20];
	sprintf(str, "%f", f);
	return m_string_new_cstr(str, allocator);
}

m_string m_string_new_d(double d, m_allocator allocator) {
	char str[30];
	sprintf(str, "%g", d);
	return m_string_new_cstr(str, allocator);
}

m_string m_string_new_def_empty() {
	return m_string_new_empty(ALLOCATOR_DEFAULT);
}

m_string m_string_new_def(m_string str) {
	return m_string_new(str, ALLOCATOR_DEFAULT);
}

m_string m_string_new_def_cstr(const char *str) {
	return m_string_new_cstr(str, ALLOCATOR_DEFAULT);
}

m_string m_string_new_def_c(char c) {
	return m_string_new_c(c, ALLOCATOR_DEFAULT);
}

m_string m_string_new_def_ca(const char *ch, size_t size) {
	return m_string_new_a(ch, size, ALLOCATOR_DEFAULT);
}

m_string m_string_new_def_s(short s) {
	return m_string_new_s(s, ALLOCATOR_DEFAULT);
}

m_string m_string_new_def_i(int i) {
	return m_string_new_i(i, ALLOCATOR_DEFAULT);
}

m_string m_string_new_def_l(long l) {
	return m_string_new_l(l, ALLOCATOR_DEFAULT);
}

m_string m_string_new_def_f(float f) {
	return m_string_new_f(f, ALLOCATOR_DEFAULT);
}

m_string m_string_new_def_d(double d) {
	return m_string_new_d(d, ALLOCATOR_DEFAULT);
}

m_string m_string_tmp_empty() {
	return m_string_new_empty(ALLOCATOR_DEFAULT);
}

m_string m_string_tmp(m_string str) {
	return m_string_new(str, ALLOCATOR_DEFAULT);
}

m_string m_string_tmp_cstr(const char *str) {
	return m_string_new_cstr(str, ALLOCATOR_DEFAULT);
}

m_string m_string_tmp_c(char c) {
	return m_string_new_c(c, ALLOCATOR_DEFAULT);
}

m_string m_string_tmp_ca(const char *ch, size_t size) {
	return m_string_new_a(ch, size, ALLOCATOR_DEFAULT);
}

m_string m_string_tmp_s(short s) {
	return m_string_new_s(s, ALLOCATOR_DEFAULT);
}

m_string m_string_tmp_i(int i) {
	return m_string_new_i(i, ALLOCATOR_DEFAULT);
}

m_string m_string_tmp_l(long l) {
	return m_string_new_l(l, ALLOCATOR_DEFAULT);
}

m_string m_string_tmp_f(float f) {
	return m_string_new_f(f, ALLOCATOR_DEFAULT);
}

m_string m_string_tmp_d(double d) {
	return m_string_new_d(d, ALLOCATOR_DEFAULT);
}

m_string m_string_vformat(m_allocator allocator, size_t max_len,
		const char *format, va_list ap) {
	char *str = (char*) m_malloc(max_len + 1, ALLOCATOR_NONE);
	vsprintf(str, format, ap);
	m_string m_str = m_string_new_cstr(str, allocator);
	m_free(str, ALLOCATOR_NONE);
	return m_str;
}
m_string m_string_format(m_allocator allocator, size_t max_len,
		const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	return m_string_vformat(allocator, max_len, format, ap);
}

m_string m_string_def_format(size_t max_len, const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	return m_string_vformat(ALLOCATOR_DEFAULT, max_len, format, ap);
}

m_string m_string_tmp_format(size_t max_len, const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	return m_string_vformat(ALLOCATOR_TEMP, max_len, format, ap);
}

size_t m_string_len(m_string str) {
	return str->len;
}

bool m_string_is_empty(m_string str) {
	return str->len == 0;
}

const char * m_string_cstr(m_string str) {
	return str->data;
}

void m_string_make_upper(m_string str) {
	m_strupr_s(str->data, str->len);
}

void m_string_make_lower(m_string str) {
	m_strlwr_s(str->data, str->len);
}

m_string m_string_upper(m_string str, m_allocator allocator) {
	m_string new_str = m_string_new(str, allocator);
	m_string_make_upper(new_str);
	return new_str;
}

m_string m_string_lower(m_string str, m_allocator allocator) {
	m_string new_str = m_string_new(str, allocator);
	m_string_make_lower(new_str);
	return str;
}

m_string m_string_substr(m_string str, size_t start, size_t end,
		m_allocator allocator) {
	return m_string_new_a(str->data + start, end - start, allocator);
}

m_string m_string_subs_to_end(m_string str, size_t start, m_allocator allocator) {
	return m_string_substr(str, start, str->len, allocator);
}

bool m_string_equals(m_string lhs, m_string rhs) {
	return m_string_compare(lhs, rhs) == 0;
}

int m_string_compare(m_string lhs, m_string rhs) {
	return strcmp(lhs->data, rhs->data);
}

bool m_string_starts_with(m_string str, m_string prefix) {
	if (str->len < prefix->len) {
		return false;
	}
	return strncmp(str->data, prefix->data, prefix->len) == 0;
}

bool m_string_ends_with(m_string str, m_string suffix) {
	if (str->len < suffix->len) {
		return false;
	}
	return strncmp(str->data + str->len - suffix->len - 1, suffix->data,
			suffix->len) == 0;
}

m_string m_string_concat(m_string lhs, m_string rhs, m_allocator allocator) {
	m_string new_str = m_string_new_with_capacity(lhs, lhs->len + rhs->len + 1,
			allocator);
	m_string_append(new_str, rhs);
	return new_str;
}

m_string m_string_concat_cstr(m_string str, const char *cstr,
		m_allocator allocator) {
	m_string new_str = m_string_new_with_capacity(str, strlen(cstr) + str->len,
			allocator);
	m_string_append_cstr(new_str, cstr);
	return new_str;
}

m_string m_string_concat_c(m_string str, char c, m_allocator allocator) {
	m_string new_str = m_string_new_with_capacity(str, str->len + 1, allocator);
	m_string_append_c(new_str, c);
	return new_str;
}

m_string m_string_concat_s(m_string str, short s, m_allocator allocator) {
	m_string new_str = m_string_new_with_capacity(str, str->len + 10,
			allocator);
	m_string_append_s(new_str, s);
	return new_str;
}

m_string m_string_concat_i(m_string str, int n, m_allocator allocator) {
	m_string new_str = m_string_new_with_capacity(str, str->len + 20,
			allocator);
	m_string_append_i(new_str, n);
	return new_str;
}

m_string m_string_concat_l(m_string str, long l, m_allocator allocator) {
	m_string new_str = m_string_new_with_capacity(str, str->len + 30,
			allocator);
	m_string_append_l(new_str, l);
	return new_str;
}

m_string m_string_concat_f(m_string str, float f, m_allocator allocator) {
	m_string new_str = m_string_new_with_capacity(str, str->len + 20,
			allocator);
	m_string_append_f(new_str, f);
	return new_str;
}

m_string m_string_concat_d(m_string str, double d, m_allocator allocator) {
	m_string new_str = m_string_new_with_capacity(str, str->len + 30,
			allocator);
	m_string_append_d(new_str, d);
	return new_str;
}

void m_string_append(m_string str, m_string append) {
	m_string_append_a(str, append->data, append->len);
}

void m_string_append_cstr(m_string str, const char *append) {
	m_string_append_a(str, append, strlen(append));
}

void m_string_append_a(m_string str, const char *array, size_t size) {
	if (str->len + size > str->capacity) {
		if(size < 16){
			str->capacity = str->len + 16;
		}else{
			str->capacity = str->len + size;
		}
		char *new_data = (char*) m_malloc(str->capacity + 1, str->allocator);
		memcpy(new_data, str->data, str->len);
		m_free(str->data, str->allocator);
		str->data = new_data;
	}
	memcpy(str->data + str->len, array, size);
	str->len += size;
	str->data[str->len] = '\0';
}

void m_string_append_c(m_string str, char c) {
	m_string_append_a(str, &c, 1);
}

void m_string_append_s(m_string str, short s) {
	char cstr[20];
	sprintf(cstr, "%hd", s);
	m_string_append_cstr(str, cstr);
}

void m_string_append_i(m_string str, int n) {
	char cstr[20];
	sprintf(cstr, "%d", n);
	m_string_append_cstr(str, cstr);
}

void m_string_append_l(m_string str, long l) {
	char cstr[30];
	sprintf(cstr, "%ld", l);
	m_string_append_cstr(str, cstr);
}

void m_string_append_f(m_string str, float f) {
	char cstr[20];
	sprintf(cstr, "%f", f);
	m_string_append_cstr(str, cstr);
}

void m_string_append_d(m_string str, double d) {
	char cstr[30];
	sprintf(cstr, "%g", d);
	m_string_append_cstr(str, cstr);
}

bool m_string_contains(m_string str, m_string substr) {
	return strstr(str->data, substr->data) != 0;
}

index_t m_string_find(m_string str, m_string substr) {
	char *p = strstr(str->data, substr->data);
	return p == NULL ? str->len : (index_t) (p - str->data);
}

int m_string_index_of(m_string str, m_string substr) {
	index_t i = m_string_find(str, substr);
	return i == str->len ? -1 : (int) i;
}

void m_string_replace_char(m_string str, char old_char, char new_char) {
	char *ptr = str->data;
	for (index_t i = 0; i < str->len; i++) {
		if (*ptr == old_char) {
			*ptr = new_char;
		}
		ptr++;
	}
}

void m_string_replace(m_string str, m_string old_str, m_string new_str) {
	// TODO
	m_fatal_error_cstr(UNIMPLEMENTED_ERROR, "function: m_string_replace");
}

void m_string_split(m_string str, m_string delimit, m_list l){
	m_string_split_cstr(str, m_string_cstr(delimit), l);
}

void m_string_split_cstr(m_string str, const char *delimit, m_list l){
	char *clone = (char*)m_malloc(str->len + 1, ALLOCATOR_NONE);
	strcpy(clone, m_string_cstr(str));
	char* substr = strtok(clone, delimit);
	while(substr != NULL){
		 m_list_add(l, m_element_init_str(m_string_new_cstr(substr, l->allocator)));
		 substr = strtok(NULL, delimit);
	}
}

int m_string_to_int(m_string str){
	int i = 0;
	sscanf(str->data, "%d", &i);
	return i;
}

long m_string_to_long(m_string str){
	long l = 0;
	sscanf(str->data, "%ld", &l);
	return l;
}

float m_string_to_float(m_string str){
	float f = 0;
	sscanf(str->data, "%f", &f);
	return f;
}

double m_string_to_double(m_string str){
	double d = 0;
	sscanf(str->data, "%lf", &d);
	return d;
}

void m_string_free(m_string str) {
	m_free(str->data, str->allocator);
	str->data = NULL;
	str->capacity = 0;
	str->len = 0;
	m_free(str, str->allocator);
}

void m_string_free_and_set_null(m_string *str) {
	m_string_free(*str);
	*str = NULL;
}

void m_strupr_s(char *str, size_t len) {
	for (index_t i = 0; i < len; i++) {
		if (*str >= 'a' && *str <= 'z') {
			*str += 'a' - 'A';
		}
		str++;
	}
}

void m_strlwr_s(char *str, size_t len) {
	for (index_t i = 0; i < len; i++) {
		if (*str >= 'A' && *str <= 'Z') {
			*str += 'A' - 'a';
		}
		str++;
	}
}

