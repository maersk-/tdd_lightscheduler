/*
 * FakeTimeService.h
 *
 *  Created on: 23.02.2012
 *      Author: maersk
 */

#ifndef FAKETIMESERVICE_H_
#define FAKETIMESERVICE_H_

#include "TimeService.h"

enum {
	TIME_UNKNOWN = -1
};

void FakeTimeService_SetMinute(int minute);
void FakeTimeService_SetDay(int day);

WakeupCallback FakeTimeSource_GetAlarmCallback(void);
int FakeTimeSource_GetAlarmPeriod(void);


#endif /* FAKETIMESERVICE_H_ */
