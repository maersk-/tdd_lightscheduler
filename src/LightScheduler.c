/*
 * LightScheduler.c
 *
 *  Created on: 24.02.2012
 *      Author: maersk
 */
#include "LightScheduler.h"
#include "LightController.h"
#include "RandomMinute.h"
#include <stdbool.h>

enum
{
    TURN_ON, TURN_OFF, DIM, RANDOM_ON, RANDOM_OFF
};

enum
{
    MAX_EVENTS = 128, UNUSED = -1
};

typedef struct {
	int id;
	int minuteOfDay;
	Day day;
	int event;
    int randomize;
    int randomMinutes;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

void LightScheduler_Create(void) {

	for (int i = 0; i != MAX_EVENTS; ++i) {
		scheduledEvents[i].id = UNUSED;
	}
	TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

void LightScheduler_Destroy(void) {
	TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

static void operateLight(ScheduledLightEvent *lightEvent) {
	if (lightEvent->event == TURN_ON) {
		LightController_TurnOn(lightEvent->id);
	} else if (lightEvent->event == TURN_OFF) {
		LightController_TurnOff(lightEvent->id);
	}
	if (lightEvent->randomize == RANDOM_ON) {
		lightEvent->randomMinutes = RandomMinute_Get();
	}
}

static bool doesLightRespondToday(Time *time, int reactionDay) {
	int today = time->dayOfWeek;
	if (reactionDay == EVERYDAY) return true;
	if (reactionDay == today) return true;
	if (reactionDay == WEEKEND && (today == SATURDAY || today == SUNDAY)) return true;
	if (reactionDay == WEEKDAY && today > SUNDAY && today < SATURDAY) return true;
	return false;

}

static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent) {
	int reactionDay = lightEvent->day;

	if (lightEvent->id == UNUSED) return;
	if (!doesLightRespondToday(time, reactionDay)) return;
	if ((lightEvent->minuteOfDay + lightEvent->randomMinutes) != time->minuteOfDay) return;
	operateLight(lightEvent);
}

void LightScheduler_Wakeup(void) {
	Time time;
	TimeService_GetTime(&time);
	for (int i = 0; i != MAX_EVENTS; ++i) {
		processEventDueNow(&time, &scheduledEvents[i]);
	}
}

static int scheduleEvent(int id, Day day, int minuteOfDay, int event) {

	if (id < 0 || id >= MAX_LIGHTS)
	        return LS_ID_OUT_OF_BOUNDS;

	for (int i = 0; i <= MAX_EVENTS; ++i) {
		if (scheduledEvents[i].id == UNUSED) {
			scheduledEvents[i].id = id;
			scheduledEvents[i].minuteOfDay = minuteOfDay;
			scheduledEvents[i].event = event;
			scheduledEvents[i].day = day;
			scheduledEvents[i].randomize = RANDOM_OFF;
			scheduledEvents[i].randomMinutes = 0;
			return LS_OK;
		}
	}
	return LS_TOO_MANY_EVENTS;
}

int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay) {
	return scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay) {
	return scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

void LightScheduler_ScheduleRemove(int id, Day day, int minute) {

    for (int i = 0; i < MAX_EVENTS; i++)
    {
    	ScheduledLightEvent *e = &scheduledEvents[i];
        if (e->id == id
         && e->day == day
         && e->minuteOfDay == minute)
         {
             e->id = UNUSED;
         }
    }
 }

void LightScheduler_Randomize(int id, Day day, int minuteOfDay) {

	for (int i = 0; i < MAX_EVENTS; ++i)
	{
		ScheduledLightEvent * e = &scheduledEvents[i];
		if (e->id == id && e->day == day && e->minuteOfDay == minuteOfDay)
		{
			e->randomize = RANDOM_ON;
			e->randomMinutes = RandomMinute_Get();
		}
	}

}


