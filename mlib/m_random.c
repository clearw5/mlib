/*
 * m_random.c
 *
 *  Created on: 2016Äê10ÔÂ2ÈÕ
 *      Author: Stardust
 */

#include "m_random.h"
#include <stdlib.h>
#include <time.h>

void m_random_set_seed(unsigned int seed) {
	srand(seed);
}

void m_random_set_time_seed() {
	srand((unsigned int) time(NULL));
}

int m_random_int() {
	return rand();
}

float m_random_float() {
	return (float) m_random_double();
}

double m_random_double() {
	return (double) rand() / RAND_MAX;
}

int m_random_range(int a, int b) {
	return (int) (a + m_random_double() * (b - a));
}
