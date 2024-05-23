/*
 * PWM0.h
 *
 * Created: 17/05/2024 10:42:14
 *  Author: asrol
 */ 


#ifndef PWM0_H_
#define PWM0_H_
#include <avr/io.h>

#define invertido 1
#define no_invertido 0
void RSTPWM0(void);
float MapPWM0(float dutyCycle, float EnMin, float EnMax, float SalMin, float SalMax);
void setPWM0fastA(uint8_t inverted, uint16_t Preescaler);
void setPWM0fastB(uint8_t inverted, uint16_t Preescaler);
void setPWMChanel0A(uint8_t dutyCycle);
void setPWMChanel0B(uint8_t dutyCycle);

#endif /* PWM0_H_ */