
#include <memory.h>
#include "m_array.h"

#include "m_except.h"

m_array m_array_new(size_t size, m_allocator allocator) {
	m_array a = (m_array)m_malloc(sizeof(m_array_t), allocator);
	a->data = (m_element*)m_malloc(size * sizeof(m_element), allocator);
	a->len = size;
	a->allocator = allocator;
	m_array_fill_byte_zero(a);
	return a;
}

m_array m_array_new_def(size_t size) {
	return m_array_new(size, ALLOCATOR_DEFAULT);
}

m_array m_array_tmp(size_t size) {
	return m_array_new(size, ALLOCATOR_TEMP);
}

size_t m_array_len(m_array a) {
	return a->len;
}

void m_array_assert_bounds(index_t i, size_t size) {
	if (i >= size) {
		m_fatal_error_f(OUT_OF_BOUNDS, "array access out of bounds: index=%u size=%u", i, size);
	}
}

m_element m_array_at(m_array a, index_t index) {
	m_array_assert_bounds(index, a->len);
	return a->data[index];
}

void m_array_set(m_array a, index_t index, m_element e){
	m_array_assert_bounds(index, a->len);
	a->data[index] = e;
}

void m_array_realloc(m_array a, size_t len) {
	m_realloc(a->data, len, a->allocator);
}

void m_array_fill_byte_zero(m_array a) {
	memset(a->data, 0, a->len * sizeof(m_element));
}

void m_array_fill(m_array a, m_element e) {
	index_t i;
	for (i = 0; i < a->len; i++) {
		a->data[i] = e;
	}
}

m_array m_array_clone(m_array a, m_allocator allocator) {
	return m_array_copy_from(a, 0, allocator);
}

m_array m_array_copy_from(m_array a, index_t from, m_allocator allocator) {
	return m_array_copy(a, from, a->len, allocator);
}

m_array m_array_copy(m_array a, index_t start, index_t end, m_allocator allocator) {
	m_array clone = m_array_new(end - start, allocator);
	m_array_copy_into(a, start, clone, 0, clone->len);
	return clone;
}

void m_array_copy_into(m_array src, index_t srcPos, m_array dest, index_t destPos, size_t length){
	if (src->len <= srcPos || src->len < srcPos + length) {
		m_fatal_error_f(OUT_OF_BOUNDS, "array copy out of src's bounds: srcPos=%ud, length=%ud, array size=%ud", srcPos, length, src->len);
	}
	if (dest->len <= destPos || dest->len < destPos + length) {
		m_fatal_error_f(OUT_OF_BOUNDS, "array copy out of dest's bounds: destPos=%ud, length=%ud, array size=%ud", destPos, length, dest->len);
	}
	memcpy(dest->data + destPos, src->data + srcPos, length * sizeof(m_element));
}

int m_array_compare_primitive_type_less_than(const void *lhs, const void *rhs){
	return m_element_compare_primitive_type_less_than(*(m_element*)lhs, *(m_element*)rhs);
}

int m_array_compare_primitive_type_greater_than(const void *lhs, const void *rhs){
	return m_element_compare_primitive_type_greater_than(*(m_element*)lhs, *(m_element*)rhs);
}

void m_array_sort_primitive_type_ascending(m_array a) {
	qsort(a->data, a->len , sizeof(m_element), m_array_compare_primitive_type_greater_than);
}

void m_array_sort_primitive_type_descending(m_array a) {
	qsort(a->data, a->len , sizeof(m_element), m_array_compare_primitive_type_less_than);
}

void m_array_sort(m_array a, m_element_compare_function cmp) {
	qsort(a->data, a->len, sizeof(m_element), (qsort_compare_function)cmp);
}

void m_array_free(m_array a){
	m_free(a->data, a->allocator);
	a->data = NULL;
	m_free(a, a->allocator);
}

void m_array_free_and_set_null(m_array *a){
	m_array_free(*a);
	*a = NULL;
}

