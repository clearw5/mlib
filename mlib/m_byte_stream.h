/*
 * m_byte_stream.h
 *
 *  Created on: 2016年10月5日
 *      Author: Stardust
 *
 *
 * 字节流。这里只是一个可以随机访问，自动增加容量的字节容器。
 * 通过修改write_pos和read_pos达到随机读写的效果。
 * 另外提供对泛型元素m_element的序列化。这取决于m_element_get_data_ptr的实现。
 * 对于指针类型的数据，只会把地址写入字节流而不会把指针指向内容写入字节流。
 * 常用类型，例如int, short, char, m_string, cstr, double, float是可以正确的序列化与反序列化的。
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

/* 在wirite_pos位置写入大小为size的数据data，写入时会检查write_pos是否正确，也即write_pos不能超出字节流末尾(>size)
 * 如果write_pos位于字节流末尾且容量不够时会自动扩充容量。*/
void m_byte_stream_write(m_byte_stream s, byte* data, size_t size);

void m_byte_stream_write_char(m_byte_stream s, char c);

/* 将大小信息写入字节流 */
void m_byte_stream_write_size(m_byte_stream s, size_t size);

/* 将类型信息写入字节流 */
void m_byte_stream_write_type(m_byte_stream s, m_type type);

/* 将元素e写入字节流 */
void m_byte_stream_write_element(m_byte_stream s, m_element *e);

/*从read_pos位置读取大小为size的数据。读取时会检查读取位置。*/
void m_byte_stream_read(m_byte_stream s, byte* dst, size_t size);

char m_byte_stream_read_char(m_byte_stream s);

/* 从字节流读取大小信息 */
size_t m_byte_stream_read_size(m_byte_stream s);

const char *m_byte_stream_read_cstr(m_byte_stream s,  m_allocator a);

m_type m_byte_stream_read_type(m_byte_stream s,  m_allocator a);

m_element m_byte_stream_read_element(m_byte_stream s, m_allocator a);


#endif /* MLIB_m_byte_stream_H_ */
