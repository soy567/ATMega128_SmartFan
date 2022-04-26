#include "I2C_LCD.h"

uint8_t lcdData;

void LCD_CmdMode() {
	// RS 값을 0으로 설정 (CMD mode)
	lcdData &= ~(1<<LCD_RS);
}

void LCD_DataMode() {
	// RS 값을 1로 설정 (Data mode)
	lcdData |= (1<<LCD_RS);
}

void LCD_WriteMode() {
	// RW 값을 0으로 설정 (Write mode)
	lcdData &= ~(1<<LCD_RW);
}

void LCD_Enable() {
	lcdData |= (1<<LCD_E); // En 신호 상승
	I2C_TxByte(LCD_DEV_ADDR_W, lcdData);
	lcdData &= ~(1<<LCD_E); // En 신호 하강
	I2C_TxByte(LCD_DEV_ADDR_W, lcdData);
	_delay_ms(2); // LCD 속도가 느려 Delay 적용
}

void LCD_SendData(uint8_t data) {
	// 매개변수 data 상위 4bit 전송 (Masking | 상위 4bit)
	lcdData = (lcdData & 0x0f) | (data & 0xf0);
	LCD_Enable();
	// 매개변수 data 하위 4bit 전송 (Masking | 하위 4bit)
	lcdData = (lcdData & 0x0f) | ((data & 0x0f)<<4);
	LCD_Enable();
}

void LCD_WriteCMD(uint8_t cmdData) {
	LCD_CmdMode();
	LCD_WriteMode();
	LCD_SendData(cmdData);
}

void LCD_WriteData(uint8_t charData) {
	LCD_DataMode();
	LCD_WriteMode();
	LCD_SendData(charData);
}

void LCD_BackLightOn() {
	lcdData |= (1<<LCD_BL);
	I2C_TxByte(LCD_DEV_ADDR_W, lcdData);
}

void LCD_BackLightOff() {
	lcdData &= ~(1<<LCD_BL);
	I2C_TxByte(LCD_DEV_ADDR_W, lcdData);
}

void LCD_Init() {
	// I2C_Init();
	
	_delay_ms(20);
	LCD_WriteCMD(0x03);
	_delay_ms(5);
	LCD_WriteCMD(0x02);
	_delay_ms(1);
	LCD_WriteCMD(CMD_FUNCSET_4BIT);
	LCD_WriteCMD(CMD_DISPLAY_OFF);
	LCD_WriteCMD(CMD_DISPLAY_CLEAR);
	LCD_WriteCMD(CMD_ENTRY_MODE_SET);
	LCD_WriteCMD(CMD_DISPLAY_ON);
	LCD_BackLightOn();
}

void LCD_WriteString(char *string) {
	for(int i = 0; string[i]; i++) {
		LCD_WriteData(string[i]);
	}
}

void LCD_GotoXY(uint8_t row, uint8_t col) {
	col %= 16;
	row %= 2;
	uint8_t address = (0x40 * row) + col;
	uint8_t command = 0x80 + address;
	LCD_WriteCMD(command);
}

void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string) {
	LCD_GotoXY(row, col);
	LCD_WriteString(string);
}