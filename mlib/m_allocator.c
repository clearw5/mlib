#include "m_allocator.h"

#include "m_except.h"
#include "m_set.h"
#include "m_log.h"
#include "m_hash_set.h"

static m_allocator allocator_default = ALLOCATOR_NONE;
static m_allocator allocator_temp = ALLOCATOR_NONE;
static m_allocator allocator_global = ALLOCATOR_NONE;

static int malloc_count = 0;

m_allocator m_get_allocator_default() {
	return allocator_default;
}

m_allocator m_get_allocator_temp() {
	if (allocator_temp == ALLOCATOR_NONE) {
		allocator_temp = m_allocator_new();
	}
	return allocator_temp;
}

m_allocator m_get_allocator_global() {
	if (allocator_global == ALLOCATOR_NONE) {
		allocator_global = m_allocator_new();
	}
	return allocator_global;
}

m_allocator m_allocator_new() {
	m_allocator allocator = (m_allocator) m_malloc(sizeof(m_allocator_t),
	ALLOCATOR_NONE);
	allocator->memory_blocks = m_hash_set_new_set(ALLOCATOR_NONE);
	return allocator;
}


static const char * m_get_allocator_name(m_allocator a){
	if(a == ALLOCATOR_NONE){
		return "ALLOCATOR_NONE";
	}
	if(a == ALLOCATOR_TEMP){
		return "ALLOCATOR_TEMP";
	}
	if(a == ALLOCATOR_GLOBAL){
		return "ALLOCATOR_GLOBAL";
	}
	return "";
}

static void bind_memory_block(m_allocator a, m_pointer ptr, size_t size) {
	m_log_info_f("bind %s: %u", m_get_allocator_name(a), ptr);
	m_set_add(a->memory_blocks, m_element_init_ptr(ptr, M_TYPE_PTR));
}

static void unbind_memory_block(m_allocator a, m_pointer ptr) {
	m_log_info_f("unbind: %u", ptr);
	if(!m_set_remove(a->memory_blocks, m_element_init_ptr(ptr, M_TYPE_PTR))){
		m_fatal_error_f(OTHERS, "unbind_memory_block: allocator %s does not contains pointer: %u", m_get_allocator_name(a) , ptr);
	}
}

m_pointer m_malloc(size_t size, m_allocator allocator) {
	m_pointer ptr = malloc(size);
	malloc_count++;
	if (ptr == NULL) {
		m_fatal_error_f(BAD_ALLOCATION, "cannot allot memory: size=%u", size);
	}
	if (allocator != ALLOCATOR_NONE) {
		bind_memory_block(allocator, ptr, size);
	}
	return ptr;
}

m_pointer m_malloc_def(size_t size) {
	return m_malloc(size, ALLOCATOR_DEFAULT);
}

m_pointer m_malloc_temp(size_t size) {
	return m_malloc(size, ALLOCATOR_TEMP);
}

m_pointer m_realloc(m_pointer ptr, size_t size, m_allocator allocator) {
	m_pointer new_ptr = realloc(ptr, size);
	if (new_ptr == NULL) {
		m_fatal_error_f(BAD_ALLOCATION, "cannot reallot memory: size=%u", size);
	}
	if (ptr != new_ptr && allocator != ALLOCATOR_NONE) {
		unbind_memory_block(allocator, ptr);
		bind_memory_block(allocator, new_ptr, size);
	}
	return new_ptr;
}

m_pointer m_realloc_def(m_pointer ptr, size_t size) {
	return m_realloc(ptr, size, ALLOCATOR_DEFAULT);
}

m_pointer m_realloc_temp(m_pointer ptr, size_t size) {
	return m_realloc(ptr, size, ALLOCATOR_TEMP);
}

void m_free(m_pointer ptr, m_allocator allocator) {
	free(ptr);
	malloc_count--;
	//m_log_info_f("free: %u", ptr);
	if (allocator != ALLOCATOR_NONE) {
		unbind_memory_block(allocator, ptr);
	}
}

void m_free_def(m_pointer ptr) {
	m_free(ptr, ALLOCATOR_DEFAULT);
}

void m_free_and_set_null(m_pointer *ptr, m_allocator allocator) {
	m_free(*ptr, allocator);
	*ptr = NULL;
}

void m_free_and_set_null_def(m_pointer *ptr) {
	m_free_def(*ptr);
	*ptr = NULL;
}

void m_free_temp() {
	m_free_all(ALLOCATOR_TEMP);
}

void m_alloactor_use_as_default(m_allocator allocator) {
	allocator_default = allocator;
}

void m_free_all(m_allocator allocator) {
	m_iterator iter = m_set_iterate(allocator->memory_blocks, ALLOCATOR_NONE);
	while (m_iterator_has_next(iter)) {
		m_pointer ptr = m_ptr(m_iterator_next(iter), M_TYPE_PTR);
		m_free(ptr, allocator);
	}
	m_iterator_free(iter, ALLOCATOR_NONE);
}

void m_allocator_destory(m_allocator *allocator) {
	m_free_all(*allocator);
	m_set_free((*allocator)->memory_blocks);
	m_free(*allocator, ALLOCATOR_NONE);
	*allocator = ALLOCATOR_NONE;
}

void m_allocator_destory_tmp() {
	if (allocator_temp != ALLOCATOR_NONE)
		m_allocator_destory(&allocator_temp);
}

void m_allocator_destory_def() {
	if (allocator_default != ALLOCATOR_NONE)
		m_allocator_destory(&allocator_default);
}

void m_allocator_destory_global() {
	if (allocator_global != ALLOCATOR_NONE)
		m_allocator_destory(&allocator_global);
}

int m_get_malloc_count() {
	return malloc_count;
}
