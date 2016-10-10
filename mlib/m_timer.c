/*
 * m_timer.c
 *
 *  Created on: 2016Äê10ÔÂ2ÈÕ
 *      Author: Stardust
 */

#include "m_timer.h"
#include "m_time.h"


void m_timer_reset(m_timer *timer){
	timer->start_millis = m_time_current_millis();
}

long long m_timer_get_second(const m_timer *timer){
	return m_timer_get_millis(timer) / 1000;
}

long long m_timer_get_millis(const m_timer *timer){
	return m_time_current_millis() - timer->start_millis;
}
