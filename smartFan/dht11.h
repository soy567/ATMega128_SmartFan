#ifndef DHT11_H_
#define DHT11_H_

#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "sysTool.h"
#include "I2C_LCD.h"

#define DHT11_PIN_NUM	0
#define DHT11_GPIO_DDR	DDRG
#define DHT11_GPIO_PORT	PORTG
#define DHT11_GPIO_PIN	PING

#define DHT11_OK	0
#define DHT11_ERROR	1

void DHT11_Init(void);
void DHT11_set_gpio_output (void);
void DHT11_set_gpio_input (void);
uint8_t DHT11_read_pin(void);
void DHT11_start (void);
//void DHT11_check_response (void);
uint8_t DHT11_check_response (uint32_t timeOut);
//uint8_t DHT11_read_data (void);
uint8_t DHT11_read_data (uint8_t *dhtData, uint32_t timeOut);
uint8_t DHT11_get_data(uint8_t *rh_data, uint8_t *temp_data, uint32_t timeOut);
void DHT11_Exec();
uint8_t getTempData();
uint8_t getHumiData();


#endif /* DHT11_H_ */
