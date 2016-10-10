/*
 *  内存池。用于尽量减少内存泄漏和内存碎片(TODO)。并且提供一种避免C语言中先分配内存再传入指针最后释放参数的参数传递的方法。以及统一回收内存的工具。
 *  m_allocator使用一个set（当前使用hash_set作为实现）记录所有由他分配的指针，并在生命周期结束时统一释放。
 *  本库中很多操作依赖于内存池。
 *  例如以往要初始化一个结构体指针可能是这样的：
 *   something *ptr = (something*)malloc(sizoef(something));
 *   something_init(ptr);
 *	 //do something
 *	 free(ptr);
 *	 使用m_allocator后的代码将是这样的：
 *	 m_allocator tmp = m_allocator_new();
 *	 something *ptr = something_new(tmp);
 *	 //dosomthing
 *	 m_allocator_destory(&tmp);
 *	 这看起来貌似没什么区别。但在指针和临时分配内存很多的时候呢方便很多。你可以不那么再小心翼翼地提醒自己free，只要销毁对应的内存池即可。
 *
 *
 *  内存池主要包括两个函数 m_malloc与m_free。前者将申请一块内存并将记录起来，后者将释放内存并将记录除去。当调用m_allocator_destory时会将
 *  记录的内存全部释放。
 *  即使不需要内存池，也建议不要直接使用malloc而是使用m_malloc(size, ALLOCATOR_NONE)。以便以后对这类行为重新定义以及方便通过m_malloc_count
 *  判断是否内存泄漏（虽然有内存分析工具）。
 *  有三个“常用”的内存池，分别是ALLOCATOR_TEMP（临时）， ALLOCATOR_DEFAULT（默认），ALLOCATOR_GLOBAL（全局）。前两个是由于一开始一个美好的
 *  但后来发现不能实现的设想的历史遗留，所以并没什么用。有用的是ALLOCATOR_GLOBAL。一些变量的生命周期通常与程序的生命周期相同，从而他们的内存
 *  回收经常被遗忘（程序结束能否回收取决于操作系统），所以你可以通过ALLOCATOR_GLOBAL给这些变量分配内存并在程序结束时调用m_allocator_destory_global销毁。
 *  但其实作用也不大。因为大多数操作系统都会回收。这不是内存泄漏的主要问题。
 *
 *
 * TODO
 * 		1.增加小内存分配时减少内存碎片
 * */

#pragma once

#include <stdlib.h>
#include "m_pointer.h"

/* 不通过内存池分配内存 */
#define ALLOCATOR_NONE NULL
/* Deprecated */
#define ALLOCATOR_TEMP m_get_allocator_temp()
/* Deprecated */
#define ALLOCATOR_DEFAULT m_get_allocator_default()
/* 全局内存池，用于分配全局变量 */
#define ALLOCATOR_GLOBAL m_get_allocator_global()

#ifndef m_set
typedef struct m_set_t* m_set;
#endif

typedef struct m_allocator_t {
	/* 记录每个分配的内存的集合 */
	m_set memory_blocks;
} m_allocator_t;

typedef m_allocator_t* m_allocator;

/* Deprecated */
m_allocator m_get_allocator_default();

/* Deprecated */
m_allocator m_get_allocator_temp();

/* 获取全局内存池 */
m_allocator m_get_allocator_global();

/* 新建一个内存池 */
m_allocator m_allocator_new();

/* 通过内存池allocator 分配大小为size的内存 */
m_pointer m_malloc(size_t size, m_allocator allocator);

/* Deprecated */
m_pointer m_malloc_def(size_t size);

/* Deprecated */
m_pointer m_malloc_temp(size_t size);

/* 使用内存池allocator对ptr重新分配大小为size的内存并返回新的内存地址。参见realloc。 */
m_pointer m_realloc(m_pointer ptr, size_t size, m_allocator allocator);

/* Deprecated */
m_pointer m_realloc_def(m_pointer ptr, size_t size);

/* Deprecated */
m_pointer m_realloc_temp(m_pointer ptr, size_t size);

/* Deprecated */
void m_free_def(m_pointer ptr);

/* 将内存池allocator中的内存释放。如果ptr不属于该内存池会导致 fatal_error。
 * 需要注意的是，如果使用ALLOCATOR_NONE释放，是可以释放并且不会导致错误的，
 * 但在之后原本内存池的销毁时会ptr出现已经被释放的错误。*/
void m_free(m_pointer ptr, m_allocator allocator);

/* 将*ptr释放并置为null */
void m_free_and_set_null(m_pointer *ptr, m_allocator allocator);

/* Deprecated */
void m_free_and_set_null_def(m_pointer *ptr);

/* Deprecated */
void m_free_temp();

/* Deprecated */
void m_alloactor_use_as_default(m_allocator allocator);

/* 释放由内存池分配的所有内存 */
void m_free_all(m_allocator allocator);

/* 释放由内存池分配的所有内存并销毁内存池。被销毁的内存池会被置为ALLOCATOR_NONE。 */
void m_allocator_destory(m_allocator *allocator);

/* Deprecated */
void m_allocator_destory_tmp();

/* Deprecated */
void m_allocator_destory_def();

/* 释放由全局内存池分配的所有内存并销毁内存池
 * 一般在程序结束时调用。 */
void m_allocator_destory_global();

/* 得到malloc数量减去free数量。当结果为0时表明没有内存泄漏。*/
int m_get_malloc_count();
