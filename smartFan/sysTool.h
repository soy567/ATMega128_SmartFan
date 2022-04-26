#ifndef SYSTOOL_H_
#define SYSTOOL_H_
#include <avr/io.h>

void timeTick_Init(void);
void incTimeTick(void);
uint32_t getTimeTick(void);
void clearTimeTick(void);
void setTimeTick(uint32_t Value);



#endif /* SYSTOOL_H_ */