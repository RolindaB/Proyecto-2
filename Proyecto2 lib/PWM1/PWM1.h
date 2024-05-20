/*
 * PWM1.h
 *
 * Created: 17/05/2024 10:42:38
 *  Author: asrol
 */ 


#ifndef PWM1_H_
#define PWM1_H_


#include <avr/io.h>

void setupPWM1(void);
void setPWMChannelA(uint8_t duty_cycle);
void setPWMChannelB(uint8_t duty_cycle);


#endif /* PWM1_H_ */