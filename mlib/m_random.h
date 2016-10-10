/*
 * m_random.h
 *
 *  Created on: 2016��10��2��
 *      Author: Stardust
 */

#ifndef MLIB_M_RANDOM_H_
#define MLIB_M_RANDOM_H_

/* ��ʼ��������� */
void m_random_set_seed(unsigned int seed);

/* �õ�ǰʱ������������� */
void m_random_set_time_seed();

/* ����������μ�c rand()*/
int m_random_int();

/*[0,1]�����С��*/
float m_random_float();

/*[0,1]�����С��*/
double m_random_double();

/*[a,b]��������� */
int m_random_range(int a, int b);

#endif /* MLIB_M_RANDOM_H_ */
