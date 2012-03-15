/*
 * FakeRandomMinute.c
 *
 *  Created on: 08.03.2012
 *      Author: maersk
 */

static int seed = -1;
static int increment = -1;

void FakeRandomMinute_Reset(void)
{
	seed = -1;
	increment = -1;
}

void FakeRandomMinute_SetFirstAndIncrement(int s, int i)
{
	seed = s;
	increment = i;
}

int FakeRandomMinute_Get(void)
{
	int result = seed;
	seed += increment;
	return result;
}
