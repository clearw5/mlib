
/**
 * 泛型元素。本库的数据结构都基于这个元素。
 * 每个m_element包括以下成员：类型、值、大小。创建一个m_element必须指定类型，取出数据时会进行类型检查。
 * 至于m_element的值，对于double,long,int以及指针等基本类型，直接保存在m_element内的union中。
 * 对于其他类型，则将数据复制一份并保存指向数据的指针。
 * 另外，m_element提供一个比较函数，可以对基本数据类型和m_string进行比较，从而可以在排序中使用。
 * 但由于每次都要进行类型判断、解包，因而效率较低。
 * 效率低和使用繁琐是m_element的缺点，但其类型检查又确保了安全性。
 * 在追求效率的场景不建议使用m_element和本库的数据结构.
 *
 * TODO 支持更多的类型、嵌套类型和c字符串。
 * 		支持toString函数
 *
 */




#pragma once

#include "m_pointer.h"
#include "m_string.h"
#include "m_type.h"
#include "m_index_t.h"

struct m_allocator_t;
typedef struct m_allocator_t* m_allocator;

typedef union m_element_value {
	char c;
	short s;
	int i;
	long l;
	float f;
	double d;
	m_pointer ptr;
} m_element_value;

typedef struct m_element_t {
	m_element_value value;
	size_t size;
	m_type type;
} m_element_t;

typedef m_element_t m_element;

typedef m_element* m_element_ptr;
typedef const m_element* m_element_const_ptr;

typedef int (*m_element_cmp_function)(const void*, const void*);

/* 初始化一个非基本类型的m_element。注意请不要用这个函数初始化指针类型的数据！！（指针类型用m_element_init_ptr）
 * 该函数会对数据复制一份 */
m_element m_element_init(m_pointer data, size_t size, m_type type, m_allocator allocator);

/* 初始化基本类型 */
m_element m_element_init_c(char value);

m_element m_element_init_s(short value);

m_element m_element_init_i(int value);

m_element m_element_init_l(long value);

m_element m_element_init_f(float value);

m_element m_element_init_d(double value);

m_element m_element_init_cstr(const char *cstr);

m_element m_element_init_cstr_clone(const char *cstr, m_allocator allocator);

/* 初始化m_string的m_element但不复制。请注意内存回收问题！*/
m_element m_element_init_str(m_string str);

/* 复制一个str并出示 */
m_element m_element_init_str_clone(m_string str, m_allocator allocator);

m_element m_element_init_ptr(m_pointer data, m_type type);

m_element m_element_init_ptr_c(char *value);

m_element m_element_init_ptr_s(short *value);

m_element m_element_init_ptr_i(int *value);

m_element m_element_init_ptr_l(long *value);

m_element m_element_init_ptr_f(float *value);

m_element m_element_init_ptr_d(double *value);

m_element m_element_init_ptr_str(m_string *str);

m_element m_element_tmp(m_pointer data, size_t size, m_type type);

/* 初始化一个 null的m_element。null不能转换为其他任何类型。*/
m_element m_element_null();

bool m_element_is_null(m_element e);

/* 以下为取出m_element的基本类型数据 */
char m_char(m_element e);

short m_short(m_element e);

int m_int(m_element e);

long m_long(m_element e);

float m_float(m_element e);

double m_double(m_element e);

m_string m_str(m_element e);

const char *m_cstr(m_element e);

char *m_cstr_clone(m_element e, m_allocator allocator);

m_string m_str_clone(m_element e, m_allocator allocator);

m_pointer m_ptr(m_element e, m_type type);

char *m_char_ptr(m_element e);

short *m_short_ptr(m_element e);

int *m_int_ptr(m_element e);

long *m_long_ptr(m_element e);

float *m_float_ptr(m_element e);

double *m_double_ptr(m_element e);

m_string *m_string_ptr(m_element e);

/* 得到指向m_element的数据的指针。如果是基本类型则返回指向内部union的指针。
 * 如果是指针类型则直接返回指针！*/
m_pointer m_element_get_data_ptr(m_element *e);

/* 判断两个m_element是否相等。对于指针类型，不会比较指针指向的数据相等，而是比较指针是否相等。*/
bool m_element_equals(m_element lhs, m_element rhs);

/* 比较基本类型和m_string类型 */
int m_element_compare_primitive_type_less_than(m_element l, m_element r);

int m_element_compare_primitive_type_greater_than(m_element l, m_element r);


/* m_element 不记录初始化的内存池。对于基本类型调用free是无效的，指针类型也是无效。
 * 只有类型不是指针类型也不是基本类型和m-string时才需要free。因为新建过程需要复制数据。*/
void m_element_free(m_element e, m_allocator allocator);

