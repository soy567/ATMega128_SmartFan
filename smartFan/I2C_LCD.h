#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

#define LCD_RS	0
#define LCD_RW	1
#define	LCD_E	2
#define LCD_BL	3

#define LCD_DEV_ADDR_W (0x27<<1) // 첫번째 자리는 RW자리

#define CMD_DISPLAY_CLEAR	0x01
#define CMD_ENTRY_MODE_SET	0x06
#define CMD_DISPLAY_OFF		0x08
#define CMD_DISPLAY_ON		0x0c
#define CMD_FUNCSET_4BIT	0x28

void LCD_CmdMode();
void LCD_DataMode();
void LCD_WriteMode();
void LCD_Enable();
void LCD_SendData(uint8_t data);
void LCD_WriteCMD(uint8_t cmdData);
void LCD_WriteData(uint8_t charData);
void LCD_BacklightOn();
void LCD_BacklightOff();
void LCD_Init();
void LCD_WriteString(char *string);
void LCD_GotoXY(uint8_t row, uint8_t col);
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string);


#endif /* I2C_LCD_H_ */