#include "i2c.h"


void I2C_Init() {
	I2C_DDR |= (1<<I2C_SCL) | (1<<I2C_SDA);
	
	// 통신 속도 조절
	TWBR = 72; // 100kHz
	// TWBR = 32; // 200kHz
	// TWBR = 12; // 400kHz
}

// I2C 통신 시작 함수
void I2C_Start() {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // Send START condition
	
	// Wait for TWINT flag set. This indicates that the
	// START condition has been transmitted
	while (!(TWCR & (1<<TWINT)));
	
}

// I2C 통신 정지 함수
void I2C_Stop() {
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // Transmit STOP condition
}

void I2C_TxData(uint8_t data) {
	TWDR = data; // Load DATA into TWDR Register
	TWCR = (1<<TWINT) | (1<<TWEN); // Clear TWINT bit in TWCR to start transmission of data
	
	// Wait for TWINT flag set. This indicates that
	// the DATA has been transmitted, and ACK/NACK has been received.
	while (!(TWCR & (1<<TWINT))); // ACK나 NACK올 때까지 대기
}

uint8_t I2C_RxData_Ack() {
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA); // Ack 신호 (TWEA)
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

uint8_t I2C_RxData_Nack() {
	TWCR = (1<<TWINT) | (1<<TWEN); // Ack 추가 안함 -> Nack
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

void I2C_TxByte(uint8_t devAddr, uint8_t data) {
	I2C_Start(); // Start 신호 전송
	I2C_TxData(devAddr); // dev 주소 전송
	I2C_TxData(data); // 데이터 전송
	I2C_Stop(); // stop 신호 전송
}