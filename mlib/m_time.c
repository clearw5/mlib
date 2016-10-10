/*
 * m_time.c
 *
 *  Created on: 2016��10��2��
 *      Author: Stardust
 */

#include "m_time.h"
#include <sys/time.h>

long long m_time_current_millis(){
	 struct timeval tv;
	 gettimeofday(&tv, NULL);
	 return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

