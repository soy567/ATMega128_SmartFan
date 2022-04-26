#include "Button.h"

void buttonInit() {
    //버튼 초기화 코드
    BUTTON_DDR &= ~((1 << BUTTON1) | (1 << BUTTON2) | (1 << BUTTON3) | (1 << BUTTON4));
}

uint8_t getButton1State() {
    static uint8_t prevButton1State = RELEASED;
    // Button 1 자리에 있는 비트값만 추출 (나머지 비트는 0)
    uint8_t curButtonState = BUTTON_PIN & (1 << BUTTON1);

    if (prevButton1State != PUSHED && curButtonState == PUSHED) {
        //_delay_ms(50);
        prevButton1State = PUSHED;
        return FALSE;
    } else if (prevButton1State == PUSHED && curButtonState != PUSHED) {
        //_delay_ms(50);
        prevButton1State = RELEASED;
        return TRUE;
    }
    return FALSE;
}

uint8_t getButton2State() {
    static uint8_t prevButton2State = RELEASED;
    uint8_t curButtonState = BUTTON_PIN & (1 << BUTTON2);

    if (prevButton2State != PUSHED && curButtonState == PUSHED) {
        //_delay_ms(50);
        prevButton2State = PUSHED;
        return FALSE;
    } else if (prevButton2State == PUSHED && curButtonState != PUSHED) {
        //_delay_ms(50);
        prevButton2State = RELEASED;
        return TRUE;
    }
    return FALSE;
}

uint8_t getButton3State() {
    static uint8_t prevButton3State = RELEASED;
    uint8_t curButtonState = BUTTON_PIN & (1 << BUTTON3);

    if (prevButton3State != PUSHED && curButtonState == PUSHED) {
        //_delay_ms(50);
        prevButton3State = PUSHED;
        return FALSE;
    } else if (prevButton3State == PUSHED && curButtonState != PUSHED) {
        //_delay_ms(50);
        prevButton3State = RELEASED;
        return TRUE;
    }
    return FALSE;
}

uint8_t getButton4State() {
    static uint8_t prevButton4State = RELEASED;
    uint8_t curButtonState = BUTTON_PIN & (1 << BUTTON4);

    if (prevButton4State != PUSHED && curButtonState == PUSHED) {
        //_delay_ms(50);
        prevButton4State = PUSHED;
        return FALSE;
    } else if (prevButton4State == PUSHED && curButtonState != PUSHED) {
        //_delay_ms(50);
        prevButton4State = RELEASED;
        return TRUE;
    }
    return FALSE;
}