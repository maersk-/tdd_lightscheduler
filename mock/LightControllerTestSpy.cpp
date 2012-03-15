/*
 * LightSchedulerTest.cpp
 *
 *  Created on: 23.02.2012
 *      Author: maersk
 */

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightControllerSpy.h"

}

TEST_GROUP(LightControllerSpy)
{
	void setup() {
		LightController_Create();
    }

    void teardown() {
    	LightController_Destroy();
    }
};

TEST(LightControllerSpy, Create) {
	LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
	LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, RememberTheLastLightIdControlled) {
	LightController_TurnOn(10);
	LONGS_EQUAL(10, LightControllerSpy_GetLastId());
	LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, RememberAllLightStates) {
	LightController_TurnOn(0);
	LightController_TurnOff(31);
	LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLightState(0));
	LONGS_EQUAL(LIGHT_OFF, LightControllerSpy_GetLightState(31));
}

