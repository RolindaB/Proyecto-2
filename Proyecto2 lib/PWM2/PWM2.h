/*
 * PWM2.h
 *
 * Created: 21/05/2024 09:33:16
 *  Author: asrol
 */ 


#ifndef PWM2_H_
#define PWM2_H_
#include <avr/io.h>
#define invertido 1
#define no_invertido 0
void RSTPWM2(void);
float MapPWM2(float dutyCycle, float EnMin, float EnMax, float SalMin, float SalMax);
void setPWM2fastA(uint8_t inverted, uint16_t Preescaler);
void setPWM2fastB(uint8_t inverted, uint16_t Preescaler);
void setPWMChanel2A(uint8_t dutyCycle);
void setPWMChanel2B(uint8_t dutyCycle);

#endif /* PWM2_H_ */