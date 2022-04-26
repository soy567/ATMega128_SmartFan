//1. triggering을 한다. Low -> High 10us유지-> Low
//US_PORT |= (1<<US_TRIG);
//_delay_us(10);
//2. 초음파 송신
//3. Echo pin high 변경,
//4. Int발생, timer=0, timer 스타트
//4. 초음파 수신
//5. Echo pin low 변경,
//6. Int발생, timer값 read
//7. timer 값을 거리로 변경 

#include "UltraSonic.h"

uint16_t ultraSonicTimer = 0;
uint16_t distance = 0;
int ultraSonicRxFlag = 0;


void US_getTimer() {
    ultraSonicTimer = TCNT3;
}

void US_EchoFallingEdge() {
    EICRA |= (1 << ISC21);   // falling edge
    EICRA &= ~(1 << ISC20);  // falling edge
}

void US_EchoRisingEdge() {
    EICRA |= (1 << ISC21) | (1 << ISC20);  // rising edge
}

void US_ClearTimer() {
    TCNT3 = 0;
}

void US_StartTimer() {
    TCCR3B |= (1 << CS31) | (1 << CS30);  // 16bit TCNT3 64분주비
}

void US_StopTimer() {
    TCCR3B &= ~((1 << CS32) | (1 << CS31) | (1 << CS30));  // 16bit TCNT3 0분주비
}

void US_Init() {
    US_DDR |= (1 << US_TRIG);
    US_DDR &= ~(1 << US_ECHO);
    EIMSK |= (1 << INT2);
    EICRA |= (1 << ISC21) | (1 << ISC20);  // rising edge

    TCCR3B &= ~((1 << CS32) | (1 << CS31) | (1 << CS30));  // 16bit TCNT3 0분주비
}

void US_Trigger() {
    US_PORT |= (1 << US_TRIG);
    _delay_us(10);
    US_PORT &= ~(1 << US_TRIG);
}

uint16_t US_Distance() {
    return (uint16_t)(0.068 * ultraSonicTimer);
}

int US_getRxFlag() {
    return ultraSonicRxFlag;
}

void US_ClearRxFlag() {
    ultraSonicRxFlag = 0;
}

void US_SetRxFlag() {
    ultraSonicRxFlag = 1;
}

void US_INT_ISR_Process() {
    if (US_PIN & (1 << US_ECHO)) {
        US_ClearTimer();
        US_StartTimer();
        US_EchoFallingEdge();
    } 
	else {
        US_getTimer();
        US_StopTimer();
        US_EchoRisingEdge();
        US_SetRxFlag();
    }
}

void US_getDist() {
    US_Trigger();
	US_ClearRxFlag();
    while(!US_getRxFlag());
    distance = US_Distance();
}

// distance 변수에 저장된 거리값 return 함수
uint16_t getDistance() {
    return distance;
}

void printDist() {
	char buff[30];
	sprintf(buff, "Distance: %03dcm", distance);
	LCD_WriteStringXY(1, 0, buff);
}