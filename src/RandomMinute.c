/*
 * RandomMinute.c
 *
 *  Created on: 07.03.2012
 *      Author: maersk
 */

#include "RandomMinute.h"
#include <stdlib.h>

static int b;

void RandomMinute_Create(int bound) {
	b = bound;
	srand(10);
}
int RandomMinute_GetImpl(void) {
//	return (rand() % (2 * b + 1)) - b;
	return b - rand() % (b * 2 + 1);
}

int (*RandomMinute_Get)(void) = RandomMinute_GetImpl;

