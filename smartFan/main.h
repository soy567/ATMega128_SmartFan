#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "Button.h"
#include "i2c.h"
#include "I2C_LCD.h"
#include "dcMotor.h"
#include "UltraSonic.h"
#include "Buzzer.h"
#include "dht11.h"
#include "sysTool.h"
#include "timer.h"

typedef enum {
	stopFan,
	startFan,
	emergencyStop,
	autoMode,
	timerMode,
} status;

void switchMode(status nextMode);


#endif /* MAIN_H_ */