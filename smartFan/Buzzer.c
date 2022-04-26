#include "Buzzer.h"

uint16_t note[7] = {1046, 1174, 1318, 1396, 1567, 1760, 1975};


void BuzzerInit() {
	BUZZER_DDR |= (1<<BUZZER);
	
	// TIM2 사용, OC2, Fast PWM mode, BOT->TCNT2, Duty Cycle = 50%, 비반전 모드
	TCCR2 |= (1<<CS21); // prescaler = 8분주
	// Fast PWM mode
	TCCR2 |= (1<<WGM21) | (1<<WGM20);
}

void BuzzerSound(uint16_t note) {
	
	if (note > 65500) note = 65500;
	
	// BOT 설정 TCNT2 8bit (0~255)
	BUZZER_BOT = 255 - (2000000 / note);
	// Duty rate 설정
	OCR2 = (255 + BUZZER_BOT) / 2;
}

void BuzzerOn() {
	// 비반전모드 PWM OC2 출력
	TCCR2 |= (1<<COM21);
}

void BuzzerOff() {
	// 비반전모드 PWM OC2 출력 차단
	TCCR2 &= ~(1<<COM21);
}

void BuzzerOut(uint16_t note) {
	BuzzerOn();
	BuzzerSound(note);
	_delay_ms(100);
	BuzzerOff();
}

void BuzzerPowerOn() {
	
}

void BuzzerButton1() {
	BuzzerOn();
	BuzzerSound(1568);
	_delay_ms(100);
	BuzzerSound(1480);
	_delay_ms(100);
	BuzzerOff();
}