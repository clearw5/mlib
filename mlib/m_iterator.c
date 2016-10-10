/*
 * m_iterator.c
 *
 *  Created on: 2016Äê10ÔÂ2ÈÕ
 *      Author: Stardust
 */

#include "m_iterator.h"
#include "m_allocator.h"

bool m_iterator_has_next(m_iterator iter){
	return iter->impl->has_next(iter->instance);
}

m_element m_iterator_next(m_iterator iter){
	return iter->impl->next(iter->instance);
}

void m_iterator_remove(m_iterator iter){
	iter->impl->remove(iter->instance);
}

void m_iterator_free(m_iterator iter, m_allocator allocator){
	if(iter->impl->free != NULL){
		iter->impl->free(iter->instance);
		iter->instance = NULL;
	}else{
		m_free_and_set_null(&iter->instance, allocator);
	}
	m_free(iter, allocator);
}

bool m_const_iterator_has_next(m_const_iterator iter){
	return iter->impl->has_next(iter->instance);
}

m_element m_const_iterator_next(m_const_iterator iter){
	return iter->impl->next(iter->instance);
}

void m_const_iterator_free(m_const_iterator iter, m_allocator allocator){
	m_free_and_set_null(&iter->instance, allocator);
	m_free(iter, allocator);
}
