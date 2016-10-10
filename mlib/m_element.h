
/**
 * ����Ԫ�ء���������ݽṹ���������Ԫ�ء�
 * ÿ��m_element�������³�Ա�����͡�ֵ����С������һ��m_element����ָ�����ͣ�ȡ������ʱ��������ͼ�顣
 * ����m_element��ֵ������double,long,int�Լ�ָ��Ȼ������ͣ�ֱ�ӱ�����m_element�ڵ�union�С�
 * �����������ͣ������ݸ���һ�ݲ�����ָ�����ݵ�ָ�롣
 * ���⣬m_element�ṩһ���ȽϺ��������ԶԻ����������ͺ�m_string���бȽϣ��Ӷ�������������ʹ�á�
 * ������ÿ�ζ�Ҫ���������жϡ���������Ч�ʽϵ͡�
 * Ч�ʵͺ�ʹ�÷�����m_element��ȱ�㣬�������ͼ����ȷ���˰�ȫ�ԡ�
 * ��׷��Ч�ʵĳ���������ʹ��m_element�ͱ�������ݽṹ.
 *
 * TODO ֧�ָ�������͡�Ƕ�����ͺ�c�ַ�����
 * 		֧��toString����
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

/* ��ʼ��һ���ǻ������͵�m_element��ע���벻Ҫ�����������ʼ��ָ�����͵����ݣ�����ָ��������m_element_init_ptr��
 * �ú���������ݸ���һ�� */
m_element m_element_init(m_pointer data, size_t size, m_type type, m_allocator allocator);

/* ��ʼ���������� */
m_element m_element_init_c(char value);

m_element m_element_init_s(short value);

m_element m_element_init_i(int value);

m_element m_element_init_l(long value);

m_element m_element_init_f(float value);

m_element m_element_init_d(double value);

m_element m_element_init_cstr(const char *cstr);

m_element m_element_init_cstr_clone(const char *cstr, m_allocator allocator);

/* ��ʼ��m_string��m_element�������ơ���ע���ڴ�������⣡*/
m_element m_element_init_str(m_string str);

/* ����һ��str����ʾ */
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

/* ��ʼ��һ�� null��m_element��null����ת��Ϊ�����κ����͡�*/
m_element m_element_null();

bool m_element_is_null(m_element e);

/* ����Ϊȡ��m_element�Ļ����������� */
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

/* �õ�ָ��m_element�����ݵ�ָ�롣����ǻ��������򷵻�ָ���ڲ�union��ָ�롣
 * �����ָ��������ֱ�ӷ���ָ�룡*/
m_pointer m_element_get_data_ptr(m_element *e);

/* �ж�����m_element�Ƿ���ȡ�����ָ�����ͣ�����Ƚ�ָ��ָ���������ȣ����ǱȽ�ָ���Ƿ���ȡ�*/
bool m_element_equals(m_element lhs, m_element rhs);

/* �Ƚϻ������ͺ�m_string���� */
int m_element_compare_primitive_type_less_than(m_element l, m_element r);

int m_element_compare_primitive_type_greater_than(m_element l, m_element r);


/* m_element ����¼��ʼ�����ڴ�ء����ڻ������͵���free����Ч�ģ�ָ������Ҳ����Ч��
 * ֻ�����Ͳ���ָ������Ҳ���ǻ������ͺ�m-stringʱ����Ҫfree����Ϊ�½�������Ҫ�������ݡ�*/
void m_element_free(m_element e, m_allocator allocator);

