/*
 * FakeTimeService.c
 *
 *  Created on: 23.02.2012
 *      Author: maersk
 */

#include "FakeTimeService.h"

static Time time;
static WakeupCallback callback;
static int period;

void TimeService_Create(void) {
	time.minuteOfDay = TIME_UNKNOWN;
	time.dayOfWeek = TIME_UNKNOWN;
}

void TimeService_Destroy(void) {

}

void TimeService_GetTime(Time *t) {
	t->minuteOfDay = time.minuteOfDay;
	t->dayOfWeek = time.dayOfWeek;
}

void FakeTimeService_SetMinute(int minute) {
	time.minuteOfDay = minute;
}

void FakeTimeService_SetDay(int day) {
	time.dayOfWeek = day;
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback cb) {
	callback = cb;
	period = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback cb) {
	if (cb == callback && period == seconds) {
		callback = 0;
		period = 0;
	}
}

WakeupCallback FakeTimeSource_GetAlarmCallback(void) {
	return callback;
}

int FakeTimeSource_GetAlarmPeriod(void) {
	return period;
}
