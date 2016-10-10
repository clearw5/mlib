#pragma once

#include "m_element.h"
#include "m_iterator.h"
#include <stdbool.h>

struct m_set_impl_t;
typedef struct m_set_impl_t* m_set_impl;
typedef void* m_set_instance;

typedef struct m_set_t {
	m_set_impl impl;
	m_set_instance instance;
	m_allocator allocator;
} m_set_t;

typedef m_set_t* m_set;

typedef struct m_set_impl_t {
	size_t (*size)(m_set_instance s);
	void (*add)(m_set_instance s, m_element e);
	bool (*remove)(m_set_instance s, m_element e);
	bool (*contains)(m_set_instance s, m_element e);
	void (*clear)(m_set_instance s);
	bool (*empty)(m_set_instance s);
	m_iterator (*iterate)(m_set_instance s, m_allocator allocator);
	void (*free)(m_set_instance s);
} m_set_impl_t;

size_t m_set_size(m_set s);

void m_set_add(m_set s, m_element e);

bool m_set_remove(m_set s, m_element e);

bool m_set_contains(m_set s, m_element e);

void m_set_clear(m_set s);

bool m_set_empty(m_set s);

m_iterator m_set_iterate(m_set s, m_allocator allocator);

void m_set_free(m_set s);

