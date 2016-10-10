
#include "m_vector.h"
#include <memory.h>
#include "m_except.h"
#include "m_vector_iterator.h"

m_vector m_vector_new(size_t capacity, m_allocator allocator) {
	if (capacity == 0) {
		m_fatal_error_f(ILLEAGL_ARGUMENT, "capacity must be > 0 on m_vector_new: capacity=%u", capacity);
	}
	m_vector v = (m_vector)m_malloc(sizeof(m_vector_t), allocator);
	v->allocator = allocator;
	v->data = (m_element*)m_malloc(capacity * sizeof(m_element), allocator);
	v->size = 0;
	v->capacity = capacity;
	return v;
}

m_vector m_vector_new_def(m_allocator allocator) {
	return m_vector_new(10, allocator);
}

m_vector m_vector_tmp(size_t capacity) {
	return m_vector_new(capacity, ALLOCATOR_TEMP);
}

m_vector m_vector_tmp_def() {
	return m_vector_new(10, ALLOCATOR_DEFAULT);
}

size_t m_vector_size(m_vector v) {
	return v->size;
}

size_t m_vector_capacity(m_vector v) {
	return v->capacity;
}

void m_vector_assert_bounds(index_t i, size_t size) {
	if (i >= size) {
		m_fatal_error_f(OUT_OF_BOUNDS, "vector access out of bounds: index=%u size=%u", i, size);
	}
}

m_element m_vector_at(m_vector v, index_t index) {
	m_vector_assert_bounds(index, v->size);
	return v->data[index];
}

void m_vector_ensure_capacity(m_vector v, size_t except_size) {
	// TODO 优化算法。防止死循环和无脑倍乘。
	size_t capacity = v->capacity;
	if(capacity >= except_size){
		return;
	}
	while (except_size > capacity) {
		capacity *= 2;
	}
	m_vector_set_capacity(v, capacity);
}

void m_vector_add(m_vector v, m_element e) {
	m_vector_ensure_capacity(v, v->size + 1);
	v->data[v->size++] = e;
}

void m_vector_insert(m_vector v, index_t index, m_element e) {
	if(index != v->size){
		m_vector_assert_bounds(index, v->size);
	}
	m_vector_ensure_capacity(v, v->size + 1);
	memmove(v->data + index + 1, v->data + index, (v->size - index) * sizeof(m_element));
	v->data[index] = e;
	v->size++;
}

void m_vector_set(m_vector v, index_t index, m_element e){
	m_vector_assert_bounds(index, v->size);
	v->data[index] = e;
}

void m_vector_remove(m_vector v, index_t index) {
	m_vector_assert_bounds(index, v->size);
	v->size--;
	if (index < v->size - 1) {
		memmove(v->data + index, v->data + index + 1, (v->size - index) * sizeof(m_element));
	}
}

bool m_vector_remove_element(m_vector v, m_element e){
	index_t i = m_vector_find(v, e);
	if(i < v->size){
		m_vector_remove(v, i);
		return true;
	}
	return false;
}

index_t m_vector_find(m_vector v, m_element e){
	for(index_t i = 0; i < v->size; i++){
		if(m_element_equals(v->data[i], e)){
			return i;
		}
	}
	return v->size;
}

int m_vector_index_of(m_vector v, m_element e){
	index_t i = m_vector_find(v, e);
	return i == v->size ? -1 : (int) i;
}

bool m_vector_contains(m_vector v, m_element e){
	return m_vector_find(v, e) != v->size;
}

void m_vector_clear(m_vector v) {
	v->size = 0;
}

m_vector m_vector_clone(m_vector v, m_allocator allocator) {
	m_vector dst = m_vector_new(v->size, allocator);
	memcpy(dst->data, v->data, sizeof(m_element) * v->size);
	dst->size = v->size;
	return dst;
}

m_array m_vector_to_array(m_vector v, m_allocator allocator) {
	m_array a = m_array_new(v->size, allocator);
	m_vector_copy_into(v, a);
	return a;
}

void m_vector_copy_into(m_vector v, m_array a) {
	if (m_array_len(a) < v->size) {
		m_fatal_error_f(OUT_OF_BOUNDS, "array size is not enough on m_vector_copy_into() : vector size=%u, array size=%u", v->size, a->len);
	}
	memcpy(a->data, v->data, v->size * sizeof(m_element));
}

void m_vector_trim_to_size(m_vector v) {
	m_vector_set_capacity(v, v->size);
}

void m_vector_set_capacity(m_vector v, size_t capacity) {
	if (capacity == 0 || capacity < v->size) {
		m_fatal_error_f(ILLEAGL_ARGUMENT, "new capacity must be >= size and > 0 on m_vector_set_capacity: capacity=%u, size=%u", capacity, v->size);
	}
	if(capacity == v->capacity){
		return;
	}
	m_element *data = (m_element*)m_malloc(capacity * sizeof(m_element), v->allocator);
	memcpy(data, v->data, sizeof(m_element) * v->size);
	m_free(v->data, v->allocator);
	v->data = data;
	v->capacity = capacity;
}




static size_t list_impl_size(m_list_instance li) {
	return m_vector_size((m_vector)li);
}

static m_element list_impl_get(m_list_instance li, size_t index) {
	return m_vector_at((m_vector)li, index);
}

static void list_impl_add(m_list_instance li, m_element e) {
	m_vector_add((m_vector)li, e);
}

static void list_impl_insert(m_list_instance li, size_t index, m_element e) {
	m_vector_insert((m_vector)li, index, e);
}

static void list_impl_remove(m_list_instance li, size_t index) {
	m_vector_remove((m_vector)li, index);
}

static void list_impl_set(m_list_instance li, size_t index, m_element e) {
	m_vector_set((m_vector)li, index, e);
}

static void list_impl_clear(m_list_instance li) {
	m_vector_clear((m_vector)li);
}

static bool list_impl_remove_element(m_list_instance li, m_element e){
	return m_vector_remove_element((m_vector)li, e);
}

static bool list_impl_contains(m_list_instance li, m_element e){
	return m_vector_contains((m_vector)li, e);
}

static void list_impl_free(m_list_instance li){
	m_vector_free((m_vector)li);
}

static m_iterator list_impl_iterate(m_list_instance li, m_allocator a){
	return m_vector_iterate((m_vector)li, a);
}

static m_list_impl_t list_impl_vector = {
	//.size =
	list_impl_size,
	//.get =
	list_impl_get,
	//.add =
	list_impl_add,
	//.insert =
	list_impl_insert,
	//.remove =
	list_impl_remove,
	//.set =
	list_impl_set,
	//.clear =
	list_impl_clear,
	//.remove_element =
	list_impl_remove_element,
	//.contains =
	list_impl_contains,
	//.free =
	list_impl_free,
	//.iterate =
	list_impl_iterate
};

m_list m_vector_new_list(m_allocator allocator){
	m_list l = (m_list)m_malloc(sizeof(m_list_t), allocator);
	l->impl = &list_impl_vector;
	l->instance = m_vector_new(10, allocator);
	return l;
}

void m_vector_free(m_vector v){
	m_free(v->data, v->allocator);
	v->data = NULL;
	v->capacity = 0;
	v->size = 0;
	m_free(v, v->allocator);
}

void m_vector_free_and_set_null(m_vector *v){
	m_vector_free(*v);
	*v = NULL;
}
