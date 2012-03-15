/*
 * LightControllerSpy.h
 *
 *  Created on: 23.02.2012
 *      Author: maersk
 */

#ifndef LIGHTCONTROLLERSPY_H_
#define LIGHTCONTROLLERSPY_H_

#include "LightController.h"

enum {
	LIGHT_ID_UNKNOWN = -1,
	LIGHT_STATE_UNKNOWN = -1,
	LIGHT_OFF = 0,
	LIGHT_ON = 1
};

int LightControllerSpy_GetEventCounts(void);
int LightControllerSpy_GetLightState(int id);
int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);


#endif /* LIGHTCONTROLLERSPY_H_ */
