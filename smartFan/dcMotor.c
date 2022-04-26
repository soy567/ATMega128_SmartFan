#include "dcMotor.h"

char buff[30];
uint16_t prevRate = 0;

void initMotor() {
    DDRB |= (1 << PB5);
    // TIM1 분주비 8
    TCCR1B |= (1 << CS11);
    // TIM1 Fast PWM Mode설정, TOP = ICR1
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12);
    ICR1 = 1000 - 1;  // Top값 설정하여 분주비 설정 (2kHz)
    // 출력설정
    TCCR1A |= (1 << COM1A1); // non-inverting mode
    OCR1A = 0;
}

void stopMotor() {
	char buff[30];
	LCD_WriteStringXY(0, 0, "Mode : Stop Fan ");
    prevRate = OCR1A;
    OCR1A = 0;
	sprintf(buff, "H: %d%%, T: %d`C ", getHumiData(), getTempData());
	LCD_WriteStringXY(1, 0, buff);
}

void switchMotor() {
	// duty rate 40 -> 65 -> 85 -> 95 -> 0
	if(getButton2State()) {
		switch (OCR1A) {
			case 400:
			OCR1A = 650;
			break;
			case 650:
			OCR1A = 850;
			break;
			case 850:
			OCR1A = 950;
			break;
			case 950:
			OCR1A = 0;
			break;
			default:
			OCR1A = 400;
			break;
		}
	}
}

uint8_t restartMotor() {
	char buff[30];
	US_getDist();
	uint16_t dist = getDistance();
	LCD_WriteStringXY(0, 0, "Emergency stop!");
	if (dist >= 20) {
		OCR1A = prevRate;
		return 1;
	}
	sprintf(buff, "Distance: %03dcm", dist);
	LCD_WriteStringXY(1, 0, buff);
	return 0;
}

void motorExcute() {
	LCD_WriteStringXY(0, 0, "Mode : Start Fan ");
	switchMotor();
	sprintf(buff, "Fan Speed : %2d%%", OCR1A / 10);
	LCD_WriteStringXY(1, 0, buff);
}

void autoMotor() {
	char buff[30];
	LCD_WriteStringXY(0, 0, "Mode : Auto Mode ");
	uint8_t temp = getTempData();
	
	if (temp <= 10) OCR1A = 0;
	else if (temp > 10 && temp <= 15) OCR1A = 500;
	else if (temp > 15 && temp <= 20) OCR1A = 600;
	else if (temp > 20 && temp <= 25) OCR1A = 700;
	else if (temp > 25 && temp <= 30) OCR1A = 850;
	else OCR1A = 950;
	
	sprintf(buff, "T: %d`C, F: %d%% ", temp, OCR1A / 10);
	LCD_WriteStringXY(1, 0, buff);
}

void timerMotor() {
	char buff[30];
	switchMotor();
	sprintf(buff, "F:%2d%%", OCR1A / 10);
	LCD_WriteStringXY(1, 11, buff);
}