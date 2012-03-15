/*
 * FakeTimeServiceTest.cpp
 *
 *  Created on: 23.02.2012
 *      Author: maersk
 */


#include "CppUTest/TestHarness.h"

extern "C"
{
#include "TimeService.h"
#include "FakeTimeService.h"
}

TEST_GROUP(FakeTimeService)
{
    void setup() {
      TimeService_Create();
    }

    void teardown() {
       TimeService_Destroy();
    }
};

TEST(FakeTimeService, Create) {
	Time time;
	TimeService_GetTime(&time);
	LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
	LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Set) {
	Time time;
	FakeTimeService_SetMinute(42);
	FakeTimeService_SetDay(SATURDAY);
	TimeService_GetTime(&time);
	LONGS_EQUAL(42, time.minuteOfDay);
	LONGS_EQUAL(SATURDAY, time.dayOfWeek);

}


