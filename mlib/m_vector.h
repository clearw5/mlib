#pragma once

#include "m_allocator.h"
#include "m_array.h"
#include "m_list.h"
#include <stdbool.h>

typedef struct m_vector_t {
	m_element *data;
	size_t capacity;
	size_t size;
	m_allocator allocator;
} m_vector_t;

typedef m_vector_t* m_vector;


m_vector m_vector_new(size_t capacity, m_allocator allocator);

/* Ä¬ÈÏÈÝÁ¿Îª10 */
m_vector m_vector_new_def(m_allocator allocator);

size_t m_vector_size(m_vector v);

size_t m_vector_capacity(m_vector v);

m_element m_vector_at(m_vector v, index_t index);

void m_vector_add(m_vector v, m_element e);

void m_vector_insert(m_vector v, index_t index, m_element e);

void m_vector_set(m_vector v, index_t index, m_element e);

void m_vector_remove(m_vector v, index_t index);

bool m_vector_remove_element(m_vector v, m_element e);

index_t m_vector_find(m_vector v, m_element e);

int m_vector_index_of(m_vector v, m_element e);

bool m_vector_contains(m_vector v, m_element e);

void m_vector_clear(m_vector v);

m_vector m_vector_clone(m_vector v, m_allocator allocator);

m_array m_vector_to_array(m_vector v, m_allocator allocator);

void m_vector_copy_into(m_vector v, m_array a);

void m_vector_trim_to_size(m_vector v);

void m_vector_set_capacity(m_vector v, size_t capacity);

m_list m_vector_new_list(m_allocator allocator);

void m_vector_free(m_vector v);

void m_vector_free_and_set_null(m_vector *v);
