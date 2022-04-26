#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <stdio.h>
#include "I2C_LCD.h"
#include "Button.h"
#include "dcMotor.h"

typedef struct _timeClock {
	int hour;
	int min;
	int sec;
	int msec;
	int ms;
} stTime;


void setTimeClock(stTime *timerData, int hh, int mm, int ss, int msec, int ms);
void incMSec(stTime *timerData);
void decMSec(stTime *timerData);
uint8_t isTimeZero();
stTime *getTimerData();
uint8_t setTimer();
uint8_t ExecTimer(uint8_t isActive);


#endif /* TIMER_H_ */