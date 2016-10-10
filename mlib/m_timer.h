/*
 * m_timer.h
 *
 *  Created on: 2016Äê10ÔÂ2ÈÕ
 *      Author: Stardust
 */

#ifndef MLIB_M_TIMER_H_
#define MLIB_M_TIMER_H_

typedef struct m_timer {
	long long start_millis;
} m_timer;

void m_timer_reset(m_timer *timer);

long m_timer_get_minute(const m_timer *timer);

long m_timer_get_hour(const m_timer *timer);

long long m_timer_get_second(const m_timer *timer);

long long m_timer_get_millis(const m_timer *timer);

#endif /* MLIB_M_TIMER_H_ */
