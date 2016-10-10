/*
 *  �ڴ�ء����ھ��������ڴ�й©���ڴ���Ƭ(TODO)�������ṩһ�ֱ���C�������ȷ����ڴ��ٴ���ָ������ͷŲ����Ĳ������ݵķ������Լ�ͳһ�����ڴ�Ĺ��ߡ�
 *  m_allocatorʹ��һ��set����ǰʹ��hash_set��Ϊʵ�֣���¼�������������ָ�룬�����������ڽ���ʱͳһ�ͷš�
 *  �����кܶ�����������ڴ�ء�
 *  ��������Ҫ��ʼ��һ���ṹ��ָ������������ģ�
 *   something *ptr = (something*)malloc(sizoef(something));
 *   something_init(ptr);
 *	 //do something
 *	 free(ptr);
 *	 ʹ��m_allocator��Ĵ��뽫�������ģ�
 *	 m_allocator tmp = m_allocator_new();
 *	 something *ptr = something_new(tmp);
 *	 //dosomthing
 *	 m_allocator_destory(&tmp);
 *	 �⿴����ò��ûʲô���𡣵���ָ�����ʱ�����ڴ�ܶ��ʱ���ط���ܶࡣ����Բ���ô��С������������Լ�free��ֻҪ���ٶ�Ӧ���ڴ�ؼ��ɡ�
 *
 *
 *  �ڴ����Ҫ������������ m_malloc��m_free��ǰ�߽�����һ���ڴ沢����¼���������߽��ͷ��ڴ沢����¼��ȥ��������m_allocator_destoryʱ�Ὣ
 *  ��¼���ڴ�ȫ���ͷš�
 *  ��ʹ����Ҫ�ڴ�أ�Ҳ���鲻Ҫֱ��ʹ��malloc����ʹ��m_malloc(size, ALLOCATOR_NONE)���Ա��Ժ��������Ϊ���¶����Լ�����ͨ��m_malloc_count
 *  �ж��Ƿ��ڴ�й©����Ȼ���ڴ�������ߣ���
 *  �����������á����ڴ�أ��ֱ���ALLOCATOR_TEMP����ʱ���� ALLOCATOR_DEFAULT��Ĭ�ϣ���ALLOCATOR_GLOBAL��ȫ�֣���ǰ����������һ��ʼһ�����õ�
 *  ���������ֲ���ʵ�ֵ��������ʷ���������Բ�ûʲô�á����õ���ALLOCATOR_GLOBAL��һЩ��������������ͨ������������������ͬ���Ӷ����ǵ��ڴ�
 *  ���վ�������������������ܷ����ȡ���ڲ���ϵͳ�������������ͨ��ALLOCATOR_GLOBAL����Щ���������ڴ沢�ڳ������ʱ����m_allocator_destory_global���١�
 *  ����ʵ����Ҳ������Ϊ���������ϵͳ������ա��ⲻ���ڴ�й©����Ҫ���⡣
 *
 *
 * TODO
 * 		1.����С�ڴ����ʱ�����ڴ���Ƭ
 * */

#pragma once

#include <stdlib.h>
#include "m_pointer.h"

/* ��ͨ���ڴ�ط����ڴ� */
#define ALLOCATOR_NONE NULL
/* Deprecated */
#define ALLOCATOR_TEMP m_get_allocator_temp()
/* Deprecated */
#define ALLOCATOR_DEFAULT m_get_allocator_default()
/* ȫ���ڴ�أ����ڷ���ȫ�ֱ��� */
#define ALLOCATOR_GLOBAL m_get_allocator_global()

#ifndef m_set
typedef struct m_set_t* m_set;
#endif

typedef struct m_allocator_t {
	/* ��¼ÿ��������ڴ�ļ��� */
	m_set memory_blocks;
} m_allocator_t;

typedef m_allocator_t* m_allocator;

/* Deprecated */
m_allocator m_get_allocator_default();

/* Deprecated */
m_allocator m_get_allocator_temp();

/* ��ȡȫ���ڴ�� */
m_allocator m_get_allocator_global();

/* �½�һ���ڴ�� */
m_allocator m_allocator_new();

/* ͨ���ڴ��allocator �����СΪsize���ڴ� */
m_pointer m_malloc(size_t size, m_allocator allocator);

/* Deprecated */
m_pointer m_malloc_def(size_t size);

/* Deprecated */
m_pointer m_malloc_temp(size_t size);

/* ʹ���ڴ��allocator��ptr���·����СΪsize���ڴ沢�����µ��ڴ��ַ���μ�realloc�� */
m_pointer m_realloc(m_pointer ptr, size_t size, m_allocator allocator);

/* Deprecated */
m_pointer m_realloc_def(m_pointer ptr, size_t size);

/* Deprecated */
m_pointer m_realloc_temp(m_pointer ptr, size_t size);

/* Deprecated */
void m_free_def(m_pointer ptr);

/* ���ڴ��allocator�е��ڴ��ͷš����ptr�����ڸ��ڴ�ػᵼ�� fatal_error��
 * ��Ҫע����ǣ����ʹ��ALLOCATOR_NONE�ͷţ��ǿ����ͷŲ��Ҳ��ᵼ�´���ģ�
 * ����֮��ԭ���ڴ�ص�����ʱ��ptr�����Ѿ����ͷŵĴ���*/
void m_free(m_pointer ptr, m_allocator allocator);

/* ��*ptr�ͷŲ���Ϊnull */
void m_free_and_set_null(m_pointer *ptr, m_allocator allocator);

/* Deprecated */
void m_free_and_set_null_def(m_pointer *ptr);

/* Deprecated */
void m_free_temp();

/* Deprecated */
void m_alloactor_use_as_default(m_allocator allocator);

/* �ͷ����ڴ�ط���������ڴ� */
void m_free_all(m_allocator allocator);

/* �ͷ����ڴ�ط���������ڴ沢�����ڴ�ء������ٵ��ڴ�ػᱻ��ΪALLOCATOR_NONE�� */
void m_allocator_destory(m_allocator *allocator);

/* Deprecated */
void m_allocator_destory_tmp();

/* Deprecated */
void m_allocator_destory_def();

/* �ͷ���ȫ���ڴ�ط���������ڴ沢�����ڴ��
 * һ���ڳ������ʱ���á� */
void m_allocator_destory_global();

/* �õ�malloc������ȥfree�����������Ϊ0ʱ����û���ڴ�й©��*/
int m_get_malloc_count();
