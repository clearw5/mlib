/*
 * m_serializable.h
 *
 *  Created on: 2016��10��4��
 *      Author: Stardust
 */

#ifndef MLIB_M_SERIALIZABLE_H_
#define MLIB_M_SERIALIZABLE_H_

typedef void *m_serializable;
typedef char byte;

byte *m_serializable_to_bytes(m_serializable s, m_allocator a);

m_serializable m_serializable_from_bytes(byte *data, size_t size);

#endif /* MLIB_M_SERIALIZABLE_H_ */
