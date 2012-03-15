/*
 * TimeService.h
 *
 *  Created on: 23.02.2012
 *      Author: maersk
 */

#ifndef TIMESERVICE_H_
#define TIMESERVICE_H_

typedef enum Day {
    NOT_A_DAY=-4,
    EVERYDAY=-3, WEEKDAY=-2, WEEKEND=-1,
    SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
} Day;

typedef enum Month {
    JAN=1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
} Month;

typedef struct Time Time;

struct Time {
    int usec;
    int sec;
    int minuteOfDay;
    int minuteOfHour;
    Day dayOfWeek;
    int dayOfMonth;
    Month month;
};

void TimeService_Create(void);
void TimeService_Destroy(void);
int TimeService_GetMinute(void);
int TimeService_GetDay(void);

void TimeService_GetTime(Time *);

typedef void (*WakeupCallback)(void);

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback);
void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback);


#endif /* TIMESERVICE_H_ */
