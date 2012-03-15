/*
 * LightController.h
 *
 *  Created on: 23.02.2012
 *      Author: maersk
 */

#ifndef LIGHTCONTROLLER_H_
#define LIGHTCONTROLLER_H_


enum { MAX_LIGHTS = 32 };

void LightController_Create(void);
void LightController_Destroy(void);
void LightController_TurnOn(int id);
void LightController_TurnOff(int id);

#endif /* LIGHTCONTROLLER_H_ */
