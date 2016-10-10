#include <memory.h>
#include "m_linked_list.h"
#include "m_except.h"
#include "m_linked_list_iterator.h"

m_linked_list_node *m_linked_list_get_node_at(m_linked_list li, index_t index) {
	bool backwards = index > li->size / 2;
	if(backwards){
		index = li->size - index - 1;
	}
	m_linked_list_node *node = backwards ? li->rear : li->front;
	for (index_t i = 0; i < index; i++) {
		node = backwards ? node->previous : node->next;
	}
	return node;
}

m_linked_list_node *m_linked_list_get_node_of(m_linked_list li, m_element e) {
	m_linked_list_node *node = li->front;
	for (index_t i = 0; i < li->size; i++) {
		if (m_element_equals(e, node->value)) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}

void m_linked_list_remove_node(m_linked_list li, m_linked_list_node *node) {
	if (node->previous == NULL) {
		li->front = node->next;
	}else{
		node->previous->next = node->next;
	}
	if (node->next == NULL) {
		li->rear = node->previous;
	}else{
		node->next->previous = node->previous;
	}
	m_element_free(node->value, li->allocator);
	m_free(node, li->allocator);
	li->size--;
}

m_linked_list_node *m_linked_list_new_node(m_allocator allocator) {
	m_linked_list_node *node = (m_linked_list_node*)m_malloc(sizeof(m_linked_list_node), allocator);
	node->next = NULL;
	node->previous = NULL;
	return node;
}

m_linked_list m_linked_list_new(m_allocator allocator){
	m_linked_list l = (m_linked_list)m_malloc(sizeof(m_linked_list_t), allocator);
	l->allocator = allocator;
	l->front = NULL;
	l->rear = NULL;
	l->size = 0;
	return l;
}

size_t m_linked_list_size(m_linked_list li){
	return li->size;
}

void m_linked_list_add(m_linked_list li, m_element e){
	m_linked_list_insert(li, li->size, e);
}

void m_linked_list_assert_bounds(index_t i, size_t size){
	if (i >= size) {
		m_fatal_error_f(OUT_OF_BOUNDS, "linked list access out of bounds: index=%u size=%u", i, size);
	}
}

m_element m_linked_list_get(m_linked_list li, size_t index){
	m_linked_list_assert_bounds(index, li->size);
	return m_linked_list_get_node_at(li, index)->value;
}

void m_linked_list_insert(m_linked_list li, size_t index, m_element e){
	if(index != li->size){
		m_linked_list_assert_bounds(index, li->size);
	}
	m_linked_list_node *previous;
	m_linked_list_node *next;
	if(index < li->size){
		next = m_linked_list_get_node_at(li, index);
		previous = next->previous;
	}else{
		next = NULL;
		previous = li->rear;
	}
	m_linked_list_node *new_node = m_linked_list_new_node(li->allocator);
	new_node->value = e;
	new_node->previous = previous;
	new_node->next = next;
	if(previous == NULL){
		li->front = new_node;
	}else{
		previous->next = new_node;
	}
	if(next == NULL){
		li->rear = new_node;
	}else{
		next->previous = new_node;
	}
	li->size++;
}

void m_linked_list_remove(m_linked_list li, size_t index){
	m_linked_list_assert_bounds(index, li->size);
	m_linked_list_remove_node(li, m_linked_list_get_node_at(li, index));
}

void m_linked_list_clear(m_linked_list li){
	m_linked_list_node *node = li->front;
	for (index_t i = 0; i < li->size; i++) {
		m_element_free(node->value, li->allocator);
		m_free(node, li->allocator);
	}
	li->front = NULL;
	li->rear = NULL;
	li->size = 0;
}

void m_linked_list_set(m_linked_list li, size_t index, m_element e){
	m_linked_list_assert_bounds(index, li->size);
	m_linked_list_node *node = m_linked_list_get_node_at(li, index);
	node->value = e;
}

void m_linked_list_free(m_linked_list li){
	m_linked_list_node *node = li->front;
	m_linked_list_node *next;
	for (index_t i = 0; i < li->size; i++) {
		next = node->next;
		m_free(node, li->allocator);
		node = next;
	}
	li->size = 0;
	li->front = NULL;
	li->rear = NULL;
	m_free(li, li->allocator);
}

m_linked_list m_linked_list_sublist(m_linked_list li, size_t start, size_t end){
	// TODO
	m_fatal_error_cstr(UNIMPLEMENTED_ERROR, "function m_linked_list_sublist");
	return NULL;
}

bool  m_linked_list_contains(m_linked_list li, m_element e) {
	return m_linked_list_get_node_of(li, e) != NULL;
}

bool m_linked_list_empty(m_linked_list li) {
	return li->size == 0;
}

bool m_linked_list_remove_element(m_linked_list li, m_element e) {
	m_linked_list_node *node = m_linked_list_get_node_of(li, e);
	if (node == NULL) {
		return false;
	}
	m_linked_list_remove_node(li, node);
	return true;
}


static size_t list_impl_size(m_list_instance li) {
	return m_linked_list_size((m_linked_list)li);
}

static m_element list_impl_get(m_list_instance li, size_t index) {
	return m_linked_list_get((m_linked_list)li, index);
}

static void list_impl_add(m_list_instance li, m_element e) {
	m_linked_list_add((m_linked_list)li, e);
}

static void list_impl_insert(m_list_instance li, size_t index, m_element e) {
	m_linked_list_insert((m_linked_list)li, index, e);
}

static void list_impl_remove(m_list_instance li, size_t index) {
	m_linked_list_remove((m_linked_list)li, index);
}

static void list_impl_set(m_list_instance li, size_t index, m_element e) {
	m_linked_list_set((m_linked_list)li, index, e);
}

static void list_impl_clear(m_list_instance li) {
	m_linked_list_clear((m_linked_list)li);
}

static bool list_impl_remove_element(m_list_instance li, m_element e){
	return m_linked_list_remove_element((m_linked_list)li, e);
}

static bool list_impl_contains(m_list_instance li, m_element e){
	return m_linked_list_contains((m_linked_list)li, e);
}

static void list_impl_free(m_list_instance li){
	m_linked_list_free((m_linked_list)li);
}

static m_iterator list_impl_iterate(m_list_instance li,  m_allocator allocator){
	return m_linked_list_iterate((m_linked_list)li, allocator);
}


static m_list_impl_t list_impl_linked_list = {
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

m_list m_linked_list_new_list(m_allocator allocator){
	m_list l = (m_list)m_malloc(sizeof(m_list_t), allocator);
	m_linked_list ll = m_linked_list_new(allocator);
	l->impl = &list_impl_linked_list;
	l->instance = ll;
	l->allocator = allocator;
	return l;
}




static size_t set_impl_size(m_set_instance s) {
	return m_linked_list_size((m_linked_list)s);
}

static void set_impl_add(m_set_instance s, m_element e) {
	if(!m_linked_list_contains((m_linked_list)s, e)){
		m_linked_list_add((m_linked_list)s, e);
	}
}

static bool set_impl_remove(m_set_instance s, m_element e) {
	return m_linked_list_remove_element((m_linked_list)s, e);
}

static void set_impl_clear(m_set_instance s) {
	m_linked_list_clear((m_linked_list)s);
}

static bool set_impl_contains(m_set_instance s, m_element e) {
	return m_linked_list_contains((m_linked_list)s, e);
}

static bool set_impl_empty(m_set_instance s) {
	return m_linked_list_empty((m_linked_list)s);
}

static m_iterator set_impl_iterate(m_set_instance s, m_allocator allocator){
	return m_linked_list_iterate((m_linked_list)s, allocator);
}

static void set_impl_free(m_set_instance s){
	m_linked_list_free((m_linked_list) s);
}

static m_set_impl_t set_impl_linked_list = {
	//.size = 
	set_impl_size,
	//.add = 
	set_impl_add,
	//.remove = 
	set_impl_remove,
	//.contains = 
	set_impl_contains,
	//.clear = 
	set_impl_clear,
	//.empty = 
	set_impl_empty,
	//.iterate =
	set_impl_iterate,
	//.free =
	set_impl_free
};

m_set m_linked_list_new_set(m_allocator allocator) {
	m_set s = (m_set)m_malloc(sizeof(m_set_t), allocator);
	s->allocator = allocator;
	m_linked_list ll = m_linked_list_new(allocator);
	s->impl = &set_impl_linked_list;
	s->instance = ll;
	return s;
}

