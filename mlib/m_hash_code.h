/*
 * m_hash_code.h
 *
 *  Created on: 2016年10月3日
 *      Author: Stardust
 *       一些常用的哈希算法
 */

#ifndef MLIB_M_HASH_CODE_H_
#define MLIB_M_HASH_CODE_H_

#include "m_pointer.h"
#include "m_index_t.h"
#include <stdlib.h>

typedef unsigned int m_hash;

typedef m_hash (*m_hash_function)(m_pointer data, size_t size);

/* time33 哈希函数，又叫 DJBX33A，Bernstein's hash
 * 乘数31也换成其他合适的数，参见相关资料。*/
m_hash m_hash_code_bernstein(m_pointer data, size_t size);

/*FNV哈希算法，全名为Fowler-Noll-Vo算法*/
m_hash m_hash_code_fnv(m_pointer data, size_t size);


m_hash m_hash_code_rs(m_pointer data, size_t size);

m_hash m_hash_code_crc32(m_pointer data, size_t size);



#endif /* MLIB_M_HASH_CODE_H_ */
