/*
 * FakeRandomMinute.h
 *
 *  Created on: 08.03.2012
 *      Author: maersk
 */

#ifndef FAKERANDOMMINUTE_H_
#define FAKERANDOMMINUTE_H_

#include "RandomMinute.h"

void FakeRandomMinute_SetFirstAndIncrement(int seed, int increment);
int FakeRandomMinute_Get(void);
void FakeRandomMinute_Reset(void);


#endif /* FAKERANDOMMINUTE_H_ */
