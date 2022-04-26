#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#define I2C_DDR		DDRD
#define I2C_SCL		PD0
#define I2C_SDA		PD1

void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_TxData(uint8_t data);
uint8_t I2C_RxData_Ack();
uint8_t I2C_RxData_Nack();
void I2C_TxByte(uint8_t devAddr, uint8_t data);


#endif /* I2C_H_ */