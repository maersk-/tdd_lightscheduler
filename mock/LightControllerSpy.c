/*
 * LightControllerSpy.c
 *
 *  Created on: 23.02.2012
 *      Author: maersk
 */

#include "LightControllerSpy.h"
#include <string.h>

static int lastId;
static int lastState;
static int count;
static int lights[MAX_LIGHTS];

static int isIdInRange(int id) {
	return id >= 0 && id <= 31;
}

int LightControllerSpy_GetLightState(int id) {
	if (!isIdInRange(id)) return LIGHT_STATE_UNKNOWN;
	return lights[id];
}

int LightControllerSpy_GetLastId(void) {
	return lastId;
}

int LightControllerSpy_GetLastState(void) {
	return lastState;
}

int LightControllerSpy_GetEventCounts(void) {
    return count;
}

void LightController_Create(void) {
	lastId = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
	count = 0;
	memset(lights, LIGHT_STATE_UNKNOWN, sizeof lights);
}

void LightController_Destroy(void) {

}

void LightController_TurnOn(int id) {
	lastId = id;
	lastState = LIGHT_ON;
	count++;
	if (isIdInRange(id))
		lights[id] = LIGHT_ON;
}

void LightController_TurnOff(int id) {
	lastId = id;
	lastState = LIGHT_OFF;
	count++;
	if (isIdInRange(id))
		lights[id] = LIGHT_OFF;
}

