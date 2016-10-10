/*
 * m_set.c
 *
 *  Created on: 2016Äê10ÔÂ2ÈÕ
 *      Author: Stardust
 */

#include "m_set.h"

size_t m_set_size(m_set s){
	return s->impl->size(s->instance);
}

void m_set_add(m_set s, m_element e){
	s->impl->add(s->instance, e);
}

bool m_set_remove(m_set s, m_element e){
	return s->impl->remove(s->instance, e);
}

bool m_set_contains(m_set s, m_element e){
	return s->impl->contains(s->instance, e);
}

void m_set_clear(m_set s){
	s->impl->clear(s->instance);
}

bool m_set_empty(m_set s){
	return s->impl->empty(s->instance);
}

m_iterator m_set_iterate(m_set s, m_allocator allocator){
	return  s->impl->iterate(s->instance, allocator);
}

void m_set_free(m_set s){
	s->impl->free(s->instance);
	m_free(s, s->allocator);
}
