#include "main.h"


status mode = stopFan;
status prevMode = stopFan;


void switchMode(status nextMode) {
	BuzzerOut(1568);
	prevMode = mode;
	mode = nextMode;
}

// Timer 0 비교일치 인터럽트 (1ms)
ISR(TIMER0_COMP_vect) {
	incTimeTick();
	if ((mode == timerMode && prevMode == timerMode) ||
			(prevMode == emergencyStop && mode == timerMode)) 
		decMSec(getTimerData());
	if(mode != stopFan && mode != emergencyStop && getDistance() <= 10)
		switchMode(emergencyStop);
}

// 외부 인터럽트
ISR(INT2_vect) {
	US_INT_ISR_Process();
}



int main(void) {
	initMotor(); // timer 1 (16bit) 사용
	I2C_Init();
	LCD_Init();
	DHT11_Init();
	US_Init(); // timer 3 (16bit) 사용
	buttonInit();
	BuzzerInit(); // timer 2 사용
	timeTick_Init(); // timer 0 사용
	
	sei();

	uint32_t prevTime = 0;
	
	while (1) {
		US_getDist();
		if (getTimeTick() - prevTime > 2000) {
			prevTime = getTimeTick();
			DHT11_Exec();
		}
		if (getButton4State()) switchMode(stopFan); // push btn4 is stop at all mode
		
		switch (mode) {
			case stopFan:
				stopMotor();
				if (getButton1State()) switchMode(startFan);
				else if(getButton2State()) switchMode(autoMode);
				else if(getButton3State()) switchMode(timerMode);
				break;
			case startFan:
				motorExcute();
				break;
			case emergencyStop:
				stopMotor();
				while(!restartMotor()){};
				switchMode(prevMode);
				break;
			case autoMode:
				autoMotor();
				break;
			case timerMode:
				if(prevMode != timerMode && prevMode != emergencyStop) 
					if(!ExecTimer(0)) switchMode(stopFan);
					else switchMode(timerMode); // prev, now = timerMode
				else 
					if(!ExecTimer(1)) switchMode(stopFan);
				break;
		}
	}
}