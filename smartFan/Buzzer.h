#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 16000000UL // delay.h 보다 위에 있어야함
#include <avr/io.h>
#include <util/delay.h>


#define BUZZER_DDR	DDRB
#define BUZZER		PB7
#define BUZZER_BOT	TCNT2

void BuzzerInit();
void BuzzerSound(uint16_t note);
void BuzzerOn();
void BuzzerOff();
void BuzzerPowerOn();
void BuzzerButton1();
void BuzzerOut(uint16_t note);


#endif /* BUZZER_H_ */