#include "dht11.h"

uint8_t rhData[2], tempData[2];
uint8_t prevTime = 0;

void DHT11_Init(void) {
    DHT11_GPIO_DDR |= (1 << DHT11_PIN_NUM);
    DHT11_GPIO_PORT |= (1 << DHT11_PIN_NUM);  // pullup
}

void DHT11_set_gpio_output(void) {
    /*Configure GPIO pin output: PD0 */
    DHT11_GPIO_DDR |= (1 << DHT11_PIN_NUM);
}

void DHT11_set_gpio_input(void) {
    /*Configure GPIO pin input: PD0 */
    DHT11_GPIO_DDR &= ~(1 << DHT11_PIN_NUM);
    DHT11_GPIO_PORT |= (1 << DHT11_PIN_NUM);  // pullup
}

uint8_t DHT11_read_pin(void) {
    return DHT11_GPIO_PIN & (1 << DHT11_PIN_NUM);
}

void DHT11_start(void) {
    DHT11_set_gpio_output();                   // set the pin as output
    DHT11_GPIO_PORT &= ~(1 << DHT11_PIN_NUM);  // pull the pin low
    _delay_us(18000);                          // wait for 18ms
    DHT11_GPIO_PORT |= (1 << DHT11_PIN_NUM);   // pull the pin high
    DHT11_set_gpio_input();                    // set as input
}

uint8_t DHT11_check_response(uint32_t timeOut) {
    uint32_t timeOutCheck = getTimeTick();

    while (DHT11_read_pin()) {  // wait for the pin to go low
        if (getTimeTick() - timeOutCheck > timeOut) return DHT11_ERROR;
    }
    while (!DHT11_read_pin()) {  // wait for the pin to go high
        if (getTimeTick() - timeOutCheck > timeOut) return DHT11_ERROR;
    }
    while (DHT11_read_pin()) {  // wait for the pin to go low
        if (getTimeTick() - timeOutCheck > timeOut) return DHT11_ERROR;
    }
    return DHT11_OK;
}

uint8_t DHT11_read_data(uint8_t *dhtData, uint32_t timeOut) {
    uint8_t i = 0, j = 0, k = 0;
    uint32_t timeOutCheck = getTimeTick();

    for (k = 0; k < 5; k++) {
        for (j = 0; j < 8; j++) {
            while (!DHT11_read_pin()) {  // wait for the pin to go high
                if (getTimeTick() - timeOutCheck > timeOut) return DHT11_ERROR;
            }
            _delay_us(40);          // wait for 40 us
            if (!DHT11_read_pin())  // if the pin is low
            {
                i &= ~(1 << (7 - j));  // write 0
            } else
                i |= (1 << (7 - j));    // if the pin is high, write 1
            while (DHT11_read_pin()) {  // wait for the pin to go low
                if (getTimeTick() - timeOutCheck > timeOut) return DHT11_ERROR;
            }
        }
        dhtData[k] = i;
    }
    return DHT11_OK;
}

uint8_t DHT11_get_data(uint8_t *rh_data, uint8_t *temp_data, uint32_t timeOut) {
    uint8_t data[5];

    DHT11_start();
    if (DHT11_check_response(timeOut) == DHT11_ERROR) return DHT11_ERROR;
    if (DHT11_read_data(data, timeOut) == DHT11_ERROR) return DHT11_ERROR;
    rh_data[0] = data[0];
    rh_data[1] = data[1];
    temp_data[0] = data[2];
    temp_data[1] = data[3];
    return DHT11_OK;
}

void DHT11_Exec() {
	DHT11_get_data(rhData, tempData, 10);
}

uint8_t getTempData() {
    return tempData[0];
}

uint8_t getHumiData() {
	return rhData[0];
}