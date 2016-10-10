#pragma once

#include "m_allocator.h"
#include "m_index_t.h"
#include <stdbool.h>

typedef struct m_string_t {
	char* data;
	size_t len;
	size_t capacity;
	m_allocator allocator;
} m_string_t;

typedef m_string_t* m_string;


typedef struct m_list_t *m_list;


/* 新建一个长度为0但容量不为0的字符串 */
m_string m_string_new_hole(m_allocator allocator, size_t capacity);

m_string m_string_new_empty(m_allocator allocator);

/* 复制字符串作为一个新字符串 */
m_string m_string_new(m_string str, m_allocator allocator);

/*复制字符串 指定容量，容量不得小于该字符串长度 */
m_string m_string_new_with_capacity(m_string str, size_t capacity, m_allocator allocator);

/* 复制C字符串 */
m_string m_string_new_cstr(const char *str, m_allocator allocator);

m_string m_string_new_c(char c, m_allocator allocator);

/*用一个char数组新建一个字符串（会复制这个数组）*/
m_string m_string_new_a(const char *array, size_t size, m_allocator allocator);

m_string m_string_new_a_with_capacity(const char *ch, size_t size, size_t capacity, m_allocator allocator);

m_string m_string_new_s(short s, m_allocator allocator);

m_string m_string_new_i(int i, m_allocator allocator);

m_string m_string_new_l(long l, m_allocator allocator);

m_string m_string_new_f(float f, m_allocator allocator);

m_string m_string_new_d(double d, m_allocator allocator);

m_string m_string_new_def_empty();

m_string m_string_new_def(m_string str);

m_string m_string_new_def_cstr(const char *str);

m_string m_string_new_def_c(char c);

m_string m_string_new_def_ca(const char *ch, size_t size);

m_string m_string_new_def_s(short s);

m_string m_string_new_def_i(int i);

m_string m_string_new_def_l(long l);

m_string m_string_new_def_f(float f);

m_string m_string_new_def_d(double d);

m_string m_string_tmp_empty();

m_string m_string_tmp(m_string str);

m_string m_string_tmp_cstr(const char *str);

m_string m_string_tmp_c(char c);

m_string m_string_tmp_ca(const char *ch, size_t size);

m_string m_string_tmp_s(short s);

m_string m_string_tmp_i(int i);

m_string m_string_tmp_l(long l);

m_string m_string_tmp_f(float f);

m_string m_string_tmp_d(double d);

/* 格式化的新建一个字符串。格式和sscanf相同。这里必须指定最大长度。并且目前是这个函数是不安全的！*/
m_string m_string_format(m_allocator allocator, size_t max_len, const char *format, ...);

m_string m_string_def_format(size_t max_len, const char *format, ...);

m_string m_string_tmp_format(size_t max_len, const char *format, ...);

size_t m_string_len(m_string str);

bool m_string_is_empty(m_string str);

const char * m_string_cstr(m_string str);

/* 让字符串变成大写 */
void m_string_make_upper(m_string str);

/* 让字符串变成小写 */
void m_string_make_lower(m_string str);

/* 新字符串，将原字符串变成大写 */
m_string m_string_upper(m_string str, m_allocator allocator);

/* 新字符串，将原字符串变成小写 */
m_string m_string_lower(m_string str, m_allocator allocator);

/* 从start到end（不包括）的子串。有边界检查。会复制一份。 */
m_string m_string_substr(m_string str, size_t start, size_t end, m_allocator allocator);

/* 从start到字符串结束的子串 */
m_string m_string_subs_to_end(m_string str, size_t start, m_allocator allocator);

bool m_string_equals(m_string lhs, m_string rhs);

int m_string_compare(m_string lhs, m_string rhs);

int m_string_compare_ignore_case(m_string lhs, m_string rhs);

bool m_string_starts_with(m_string str, m_string prefix);

bool m_string_starts_with_ignore_case(m_string str, m_string prefix);

bool m_string_ends_with(m_string str, m_string suffix);

bool m_string_ends_with_ignore_case(m_string str, m_string suffix);

/* concat与append的区别是concat会连接产生新字符串,append则追加在原字符串末尾 */

m_string m_string_concat(m_string lhs, m_string rhs, m_allocator allocator);

m_string m_string_concat_cstr(m_string lhs, const char *cstr, m_allocator allocator);

m_string m_string_concat_c(m_string str, char c, m_allocator allocator);

m_string m_string_concat_s(m_string str, short s, m_allocator allocator);

m_string m_string_concat_i(m_string str, int n, m_allocator allocator);

m_string m_string_concat_l(m_string str, long l, m_allocator allocator);

m_string m_string_concat_f(m_string str, float f, m_allocator allocator);

m_string m_string_concat_d(m_string str, double d, m_allocator allocator);

void m_string_append(m_string str, m_string append);

void m_string_append_cstr(m_string str, const char *append);

void m_string_append_a(m_string str, const char *array, size_t size);

void m_string_append_c(m_string str, char c);

void m_string_append_s(m_string str, short s);

void m_string_append_i(m_string str, int n);

void m_string_append_l(m_string str, long l);

void m_string_append_f(m_string str, float f);

void m_string_append_d(m_string str, double d);

bool m_string_contains(m_string str, m_string substr);

void m_string_replace_char(m_string str, char old_char, char new_char);

void m_string_replace(m_string str, m_string old_str, m_string new_str);

/* 查找字串，找不到则返回字符串长度 */
index_t m_string_find(m_string str, m_string substr);

/* 查找字串，找不到则返回-1 */
int m_string_index_of(m_string str, m_string substr);

/* 用delimit作为分割符分割成若干子字符串，存在li中 */
void m_string_split(m_string str, m_string delimit, m_list li);

void m_string_split_cstr(m_string str, const char *delimit, m_list li);

int m_string_to_int(m_string str);

long m_string_to_long(m_string str);

float m_string_to_float(m_string str);

double m_string_to_double(m_string str);

void m_string_free(m_string str);

void m_string_free_and_set_null(m_string *str);

/* @hide */
void m_strupr_s(char *str, size_t len);

void m_strlwr_s(char *str, size_t len);




