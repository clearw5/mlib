/*
 * m_byte_stream.h
 *
 *  Created on: 2016��10��5��
 *      Author: Stardust
 *
 *
 * �ֽ���������ֻ��һ������������ʣ��Զ������������ֽ�������
 * ͨ���޸�write_pos��read_pos�ﵽ�����д��Ч����
 * �����ṩ�Է���Ԫ��m_element�����л�����ȡ����m_element_get_data_ptr��ʵ�֡�
 * ����ָ�����͵����ݣ�ֻ��ѵ�ַд���ֽ����������ָ��ָ������д���ֽ�����
 * �������ͣ�����int, short, char, m_string, cstr, double, float�ǿ�����ȷ�����л��뷴���л��ġ�
 */

#ifndef MLIB_m_byte_stream_H_
#define MLIB_m_byte_stream_H_

#include "m_byte_stream.h"
#include  "m_except.h"
#include "m_type.h"
#include "m_element.h"
#include <memory.h>
#include <stdbool.h>

typedef char byte;

typedef struct m_byte_stream_t {
	byte *data;
	size_t capacity;
	size_t size;
	index_t read_pos;
	index_t write_pos;
	m_allocator allocator;
} m_byte_stream_t;

typedef m_byte_stream_t* m_byte_stream;

m_byte_stream m_byte_stream_new(size_t initial_capacity, m_allocator a);

/* ��wirite_posλ��д���СΪsize������data��д��ʱ����write_pos�Ƿ���ȷ��Ҳ��write_pos���ܳ����ֽ���ĩβ(>size)
 * ���write_posλ���ֽ���ĩβ����������ʱ���Զ�����������*/
void m_byte_stream_write(m_byte_stream s, byte* data, size_t size);

void m_byte_stream_write_char(m_byte_stream s, char c);

/* ����С��Ϣд���ֽ��� */
void m_byte_stream_write_size(m_byte_stream s, size_t size);

/* ��������Ϣд���ֽ��� */
void m_byte_stream_write_type(m_byte_stream s, m_type type);

/* ��Ԫ��eд���ֽ��� */
void m_byte_stream_write_element(m_byte_stream s, m_element *e);

/*��read_posλ�ö�ȡ��СΪsize�����ݡ���ȡʱ�����ȡλ�á�*/
void m_byte_stream_read(m_byte_stream s, byte* dst, size_t size);

char m_byte_stream_read_char(m_byte_stream s);

/* ���ֽ�����ȡ��С��Ϣ */
size_t m_byte_stream_read_size(m_byte_stream s);

const char *m_byte_stream_read_cstr(m_byte_stream s,  m_allocator a);

m_type m_byte_stream_read_type(m_byte_stream s,  m_allocator a);

m_element m_byte_stream_read_element(m_byte_stream s, m_allocator a);


#endif /* MLIB_m_byte_stream_H_ */
