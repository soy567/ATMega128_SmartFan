#ifndef DCMOTOR_H_
#define DCMOTOR_H_


#include <avr/io.h>
#include <stdio.h>
#include "Button.h"
#include "I2C_LCD.h"
#include "UltraSonic.h"
#include "dht11.h"


void initMotor();
void motorExcute();
void stopMotor();
void switchMotor();
uint8_t restartMotor();
void autoMotor();
void timerMotor();


#endif /* DCMOTOR_H_ */