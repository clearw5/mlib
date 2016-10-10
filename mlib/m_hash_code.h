/*
 * m_hash_code.h
 *
 *  Created on: 2016��10��3��
 *      Author: Stardust
 *       һЩ���õĹ�ϣ�㷨
 */

#ifndef MLIB_M_HASH_CODE_H_
#define MLIB_M_HASH_CODE_H_

#include "m_pointer.h"
#include "m_index_t.h"
#include <stdlib.h>

typedef unsigned int m_hash;

typedef m_hash (*m_hash_function)(m_pointer data, size_t size);

/* time33 ��ϣ�������ֽ� DJBX33A��Bernstein's hash
 * ����31Ҳ�����������ʵ������μ�������ϡ�*/
m_hash m_hash_code_bernstein(m_pointer data, size_t size);

/*FNV��ϣ�㷨��ȫ��ΪFowler-Noll-Vo�㷨*/
m_hash m_hash_code_fnv(m_pointer data, size_t size);


m_hash m_hash_code_rs(m_pointer data, size_t size);

m_hash m_hash_code_crc32(m_pointer data, size_t size);



#endif /* MLIB_M_HASH_CODE_H_ */
