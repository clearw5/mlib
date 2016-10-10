/*
 * m_m_byte_stream.c
 *
 *  Created on: 2016Äê10ÔÂ5ÈÕ
 *      Author: Stardust
 */

#include "m_byte_stream.h"
#include  "m_except.h"
#include "m_allocator.h"
#include "m_type.h"
#include "m_element.h"
#include "m_string.h"
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>

static void m_byte_stream_print(byte *data, size_t size){
	for(index_t i = 0; i < size; i++){
		//printf("%0x", (char) *data);
		data++;
	}
}

m_byte_stream m_byte_stream_new(size_t initial_capacity, m_allocator a){
	if(initial_capacity == 0){
		initial_capacity = 1;
	}
	m_byte_stream s = (m_byte_stream)m_malloc(sizeof(m_byte_stream_t), a);
	s->data = (byte*) m_malloc(initial_capacity, a);
	s->capacity = initial_capacity;
	s->size = s->read_pos = s->write_pos = 0;
	s->allocator = a;
	return s;
}

static void m_byte_stream_ensure_capacity(m_byte_stream s, size_t size){
	bool resize = false;
	while(s->capacity < size){
		s->capacity *= 2;
		resize = true;
	}
	if(resize){
		s->data = (byte*) m_realloc(s->data, s->capacity, s->allocator);
	}
}

static void m_byte_stream_assert_bounds(index_t start, index_t end, size_t size){
	if(start >= size || end > size){
		m_fatal_error_f(OUT_OF_BOUNDS, "byte stream access out of bounds: start=%u end=%u size=%u", start, end, size);
	}
}

void m_byte_stream_write(m_byte_stream s, byte* data, size_t size){
	if(s->write_pos > s->size){
		m_fatal_error_f(OUT_OF_BOUNDS, "byte stream write out of bounds: write pos=%u size=%u", s->write_pos, size);
	}
	if(s->size < s->write_pos + size){
		s->size = s->write_pos + size;
	}
	m_byte_stream_ensure_capacity(s, s->size);
	memcpy(s->data + s->write_pos, data, size);
	s->write_pos += size;
	m_byte_stream_print(data, size);
}

void m_byte_stream_write_char(m_byte_stream s, char c){
	m_byte_stream_write(s, &c, 1);
}

void m_byte_stream_write_size(m_byte_stream a, size_t size){
	m_byte_stream_write(a, (byte*)&size, sizeof(size));
}

void m_byte_stream_write_cstr(m_byte_stream a, const char *str){
	int len = strlen(str);
	m_byte_stream_write_size(a, len);
	m_byte_stream_write(a, (byte*)str, len);
}

void m_byte_stream_write_type(m_byte_stream a, m_type type){
	m_byte_stream_write_cstr(a, type->name);
	m_byte_stream_write(a, (byte*)&type->is_pointer , sizeof(type->is_pointer ));
}


void m_byte_stream_write_element(m_byte_stream a, m_element *e){
	m_byte_stream_write_size(a, e->size);
	m_byte_stream_write_type(a, e->type);
	m_byte_stream_write(a, (byte*)m_element_get_data_ptr(e), e->size);
}

void m_byte_stream_read(m_byte_stream s, byte* dst, size_t size){
	if(size == 0)
		return;
	m_byte_stream_assert_bounds(s->read_pos, s->read_pos + size, s->size);
	memcpy(dst, s->data + s->read_pos, size);
	s->read_pos += size;
	m_byte_stream_print(dst, size);

}

char m_byte_stream_read_char(m_byte_stream s){
	char c;
	m_byte_stream_read(s, &c, 1);
	return c;
}

size_t m_byte_stream_read_size(m_byte_stream a){
	size_t size;
	m_byte_stream_read(a, (byte*)&size, sizeof(size));
	return size;
}

const char *m_byte_stream_read_cstr(m_byte_stream s,  m_allocator a){
	size_t size = m_byte_stream_read_size(s);
	char *str = (char*) m_malloc(size + 1, a);
	m_byte_stream_read(s, str, size);
	str[size] = 0;
	return str;
}

m_type m_byte_stream_read_type(m_byte_stream s,  m_allocator a){
	m_type t = (m_type) m_malloc(sizeof(m_type_t), a);
	t->name = m_byte_stream_read_cstr(s, a);
	m_byte_stream_read(s, (byte*)&t->is_pointer, sizeof(t->is_pointer));
	return t;
}

m_element m_byte_stream_read_element(m_byte_stream s, m_allocator a){
	size_t size = m_byte_stream_read_size(s);
	m_type type = m_byte_stream_read_type(s, a);
	m_pointer data = m_malloc(size, ALLOCATOR_NONE);
	m_byte_stream_read(s, (byte*)data, size);
	m_element e =  m_element_init(data, size, type, a);
	m_free(data, ALLOCATOR_NONE);
	return e;
}
