/*
 * UltraSonic.h
 *
 * Created: 2021-10-22 오후 4:11:42
 *  Author: rhoblack
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "stdio.h"
#include "I2C_LCD.h"

#define US_DDR		DDRD
#define US_PORT		PORTD
#define US_PIN		PIND
#define US_ECHO		2
#define US_TRIG		3


void US_getTimer();
void US_EchoFallingEdge();
void US_EchoRisingEdge();
void US_ClearTimer();
void US_StartTimer();
void US_StopTimer();
void US_Init();
void US_Trigger();
uint16_t US_Distance();
int US_getRxFlag();
void US_ClearRxFlag();
void US_SetRxFlag();
void US_INT_ISR_Process();
void US_getDist();
void printDist();


#endif /* ULTRASONIC_H_ */