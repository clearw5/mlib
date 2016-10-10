#include "m_list.h"

#include "m_except.h"

size_t m_list_size(m_list li) {
	return li->impl->size(li->instance);
}

m_element m_list_get(m_list li, size_t index) {
	return li->impl->get(li->instance, index);
}

void m_list_add(m_list li, m_element e) {
	li->impl->add(li->instance, e);
}

void m_list_insert(m_list li, size_t index, m_element e) {
	li->impl->insert(li->instance, index, e);
}

void m_list_remove(m_list li, size_t index) {
	li->impl->remove(li->instance, index);
}

void m_list_set(m_list li, size_t index, m_element e) {
	li->impl->set(li->instance, index, e);
}

void m_list_clear(m_list li) {
	li->impl->clear(li->instance);	
}

m_list m_list_sublist(m_list li, size_t start, size_t end) {
	//return li->impl->sublist(li->instance, start, end);
	// TODO
	m_fatal_error_f(UNIMPLEMENTED_ERROR, "m_list_sublist");
	return NULL;
}

bool m_list_remove_element(m_list li, m_element e){
	return li->impl->remove_element(li->instance, e);
}

bool m_list_contains(m_list li, m_element e){
	return li->impl->contains(li->instance, e);
}

void m_list_free(m_list li){
	li->impl->free(li->instance);
	m_free(li, li->allocator);
}

m_iterator m_list_iterate(m_list li, m_allocator allocator){
	return li->impl->iterate(li->instance, allocator);
}
