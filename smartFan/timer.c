#include "timer.h"

stTime timerData;


// 시간 구조체 값 수정하는 함수
void setTimeClock(stTime *timerData, int hh, int mm, int ss, int msec, int ms) {
	timerData->hour = hh;
	timerData->min = mm;
	timerData->sec = ss;
	timerData->msec = msec;
	timerData->ms = ms;
}

// 시간 계산하는 함수 (1ms 마다 실행  24:00:00 까지 측정가능)
void incMSec(stTime *timerData) {
	timerData->ms++; // 실행시 ms증가

	if (timerData->ms >= 100) {
		timerData->ms = 0;		// ms = 0 초기화
		timerData->msec++;		// 100ms 측정하는 msec 증가
		if (timerData->msec > 10) {
			timerData->msec = 0; // msec = 0 초기화
			timerData->sec++;	   // sec 증가
		}

		if (timerData->sec >= 60) {
			timerData->sec = 0;		// sec = 0 초기화
			timerData->min++;			// min 증가
			if (timerData->min >= 60) {
				timerData->min = 0;		 // min = 0 초기화
				timerData->hour++;		 // hour 증가
				if (timerData->hour >= 24) {
					timerData->hour = 0; // hour = 0 초기화
				}
			}
		}
	}
}

// 시간 계산하는 함수 (1ms 마다 실행  00:00:00 까지 측정가능)
void decMSec(stTime *timerData) {
	timerData->ms--; // 실행시 ms증가

	if (timerData->ms < 0) {
		timerData->ms = 100;		// ms = 100 초기화
		timerData->msec--;		// 100ms 측정하는 msec 감소
		if (timerData->msec < 0) {
			timerData->msec = 10; // msec = 10 초기화
			timerData->sec--;	   // sec 감소
		}

		if (timerData->sec < 0) {
			timerData->sec = 59;		// sec = 60 초기화
			timerData->min--;			// min 감소
			if (timerData->min < 0) {
				timerData->min = 59;		 // min = 60 초기화
				timerData->hour--;		 // hour 감소
				if (timerData->hour < 0) {
					timerData->hour = 24; // hour = 24 초기화
				}
			}
		}
	}
}

uint8_t isTimeZero() {
	if(timerData.hour == 0 && timerData.min == 0 
		&& timerData.sec == 0) return 1;
	else return 0;
}

stTime *getTimerData() {
	return &timerData;
}


uint8_t setTimer() {
	int hour = 0, min = 0, sec = 0;
	char buff[30];
	
	while(1) {
		sprintf(buff, "Timer : %02d:%02d:%02d", hour, min, sec);
		LCD_WriteStringXY(1, 0, buff);
		
		if(getButton2State()) {
			min++;
			if(min >= 60) {
				hour++;
				min = 0;
			}
		}
		else if(getButton1State()) {
			hour++;
			if(hour > 24) hour = 0;
		}
		else if(getButton3State()) {
			if(hour == 0 && min == 0 && sec == 0) return 0;
			else break;
		}
		else if(getButton4State()) return 0; // btn4 눌러 종료
	}
	setTimeClock(&timerData, hour, min, sec, 0, 0);
	return 1;
}


uint8_t ExecTimer(uint8_t isActive) {
	LCD_WriteStringXY(0, 0, "Mode : TimerMode");
	char buff[30];
	if(isActive == 0) {
		if(!setTimer()) return 0;
		else isActive = 1;
	}
	sprintf(buff, "T:%02d:%02d:%02d ", timerData.hour, timerData.min, timerData.sec);
	LCD_WriteStringXY(1, 0, buff);
	timerMotor();
	if(getButton4State() || isTimeZero()) {
		setTimeClock(&timerData, 0, 0, 0, 0, 0);
		isActive = 0;
		return 0;
	}
	return 1;
}
