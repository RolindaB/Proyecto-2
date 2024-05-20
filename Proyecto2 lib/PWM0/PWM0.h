/*
 * PWM0.h
 *
 * Created: 17/05/2024 10:42:14
 *  Author: asrol
 */ 


#ifndef PWM0_H_
#define PWM0_H_

#include <avr/io.h>

void setupPWM0(void);
void setPWMChannelC(uint8_t duty_cycle);
void setPWMChannelD(uint8_t duty_cycle);

#endif /* PWM0_H_ */