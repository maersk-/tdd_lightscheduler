/*
 * LightScheduler.h
 *
 *  Created on: 24.02.2012
 *      Author: maersk
 */

#ifndef LIGHTSCHEDULER_H_
#define LIGHTSCHEDULER_H_

#include "TimeService.h"

enum { LS_OK, LS_TOO_MANY_EVENTS, LS_ID_OUT_OF_BOUNDS };

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);

void LightScheduler_Wakeup(void);
int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);
void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay);
void LightScheduler_Randomize(int id, Day day, int minuteOfDay);


#endif /* LIGHTSCHEDULER_H_ */
