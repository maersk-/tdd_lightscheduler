/*
 * LightSchedulerTest.cpp
 *
 *  Created on: 24.02.2012
 *      Author: maersk
 */
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
}

TEST_GROUP(LightSchedulerInitAndCleanup) {

};

TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm) {
	LightScheduler_Create();
	POINTERS_EQUAL((void*)LightScheduler_Wakeup, (void*)FakeTimeSource_GetAlarmCallback());
	LONGS_EQUAL(60, FakeTimeSource_GetAlarmPeriod());
	LightScheduler_Destroy();
}

TEST(LightSchedulerInitAndCleanup, DestroyCancelOneMinuteAlarm) {
	LightScheduler_Create();
	LightScheduler_Destroy();
	POINTERS_EQUAL(NULL, (void*)FakeTimeSource_GetAlarmCallback());
	LONGS_EQUAL(0, FakeTimeSource_GetAlarmPeriod());
}


TEST_GROUP(LightScheduler) {
    void setup() {
      LightController_Create();
      LightScheduler_Create();
    }

    void teardown() {
       LightScheduler_Destroy();
       LightController_Destroy();
    }

    void setTimeTo(int day, int minute) {
    	FakeTimeService_SetDay(day);
    	FakeTimeService_SetMinute(minute);
    }

    void checkLightState(int id, int level) {
    	if (id == LIGHT_ID_UNKNOWN) {
    		LONGS_EQUAL(id, LightControllerSpy_GetLastId());
    		LONGS_EQUAL(level, LightControllerSpy_GetLastState());
    	} else {
    		LONGS_EQUAL(level, LightControllerSpy_GetLightState(id));
    	}

    }
};

TEST(LightScheduler, NoScheduleNothingHappens) {
	setTimeTo(MONDAY, 100);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayNotTimeYet) {
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1199);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydyItsTime) {
	LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_Wakeup();
	checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffEverydayItsTime) {
	LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_Wakeup();
	checkLightState(3, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleTuesdayButItsMonday) {
	LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_Wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleTuesdayItsTuesday) {
	LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
	setTimeTo(TUESDAY, 1200);
	LightScheduler_Wakeup();
	checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekendItsFriday) {
	LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(FRIDAY, 1200);
	LightScheduler_Wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekendItsSaturday) {
	LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(SATURDAY, 1200);
	LightScheduler_Wakeup();
	checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekendItsMonday) {
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekdayItsSunday) {
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekdayItsMonday) {
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsFridayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSaturdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(SATURDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleTwoEventsAtTheSameTime) {
	LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
	LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);
	setTimeTo(SUNDAY, 1200);
	LightScheduler_Wakeup();
	LONGS_EQUAL(2, LightControllerSpy_GetEventCounts());
	checkLightState(3, LIGHT_ON);
	checkLightState(12, LIGHT_ON);
}

TEST(LightScheduler, RejectsTooManyEvents) {
	int i;
	for (i = 0; i != 128; ++i)
		LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

	LONGS_EQUAL(LS_TOO_MANY_EVENTS,
	                LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
}

TEST(LightScheduler, RemoveRecyclesScheduleSlot) {
    int i;
    for (i = 0; i < 128; i++)
        LONGS_EQUAL(LS_OK,
                    LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
}

TEST(LightScheduler, RemoveMultipleScheduledEvent) {
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(7, MONDAY, 600);

    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    setTimeTo(MONDAY, 600);

    LightScheduler_Wakeup();

    checkLightState(6, LIGHT_STATE_UNKNOWN);
    checkLightState(7, LIGHT_ON);
}

TEST(LightScheduler, AcceptsValidLightIds) {
    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
}

TEST(LightScheduler, RejectsInvalidLightIds) {
    LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS,
                LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
    LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS,
                LightScheduler_ScheduleTurnOn(32, MONDAY, 600));
}

//TEST(LightScheduler, NoChangeToLightsDuringInitialization) {
//    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
//    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
//}
