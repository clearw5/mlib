/*
 * m_random.h
 *
 *  Created on: 2016年10月2日
 *      Author: Stardust
 */

#ifndef MLIB_M_RANDOM_H_
#define MLIB_M_RANDOM_H_

/* 初始化随机种子 */
void m_random_set_seed(unsigned int seed);

/* 用当前时间设置随机种子 */
void m_random_set_time_seed();

/* 随机整数，参见c rand()*/
int m_random_int();

/*[0,1]的随机小数*/
float m_random_float();

/*[0,1]的随机小数*/
double m_random_double();

/*[a,b]的随机整数 */
int m_random_range(int a, int b);

#endif /* MLIB_M_RANDOM_H_ */
