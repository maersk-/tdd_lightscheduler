/*
 * RandomMinuteTest.cpp
 *
 *  Created on: 07.03.2012
 *      Author: maersk
 */

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "RandomMinute.h"
}

enum {
	BOUND = 30
};

TEST_GROUP(RandomMinute) {

	int minute;

	void setup() {
		RandomMinute_Create(BOUND);
		srand(1);
	}

	void AssertMinuteIsInRange() {
		if (minute < -BOUND || minute > BOUND) {
			printf("bad minute value: %d\n", minute);
			FAIL("minute out of range");
		}
	}
};

TEST(RandomMinute, GetIsInRange) {
	for (int i = 0; i != 100; ++i) {
		minute = RandomMinute_Get();
		AssertMinuteIsInRange();
	}
}

TEST(RandomMinute, AllValuesPossible) {
	int hit[2*BOUND+1];
	memset(hit, 0, sizeof hit);

	for (int i = 0; i != 300; ++i) {
		minute = RandomMinute_Get();
		AssertMinuteIsInRange();
		hit[minute+BOUND]++;
	}

	for (int i = 0; i != (2*BOUND+1); ++i) {
		printf("%d ", hit[i]);
		CHECK(hit[i] > 0);
	}
}
