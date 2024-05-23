/*
 * PWM2.c
 *
 * Created: 21/05/2024 09:32:56
 *  Author: asrol
 */ 
#include <avr/io.h>
#include <stdint.h>
#include "PWM2.h"

void RSTPWM2(void){
	TCCR2A = 0;
	TCCR2B = 0;
}

float MapPWM2(float dutyCycle, float EnMin, float EnMax, float SalMin, float SalMax){
	return((dutyCycle -EnMin)*(SalMax -SalMin)/(EnMax - EnMin));
}

void setPWM2fastA(uint8_t inverted, uint16_t Preescaler){
	DDRB|= (1<<DDB3); /* pin de salida*/
	if(inverted){
		TCCR2A|= (1<<COM2A1)|(1<<COM2A0);
	}else{
		TCCR2A|= (1<<COM2A1);
	}
	TCCR2A |=(1<<WGM20)|(1<<WGM21);
	if (Preescaler == 1024){
		TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20);//Prescaler
	}
}

void setPWM2fastB(uint8_t inverted, uint16_t Preescaler){
	DDRD|= (1<<DDD3); /* pin de salida*/
	if(inverted){
		TCCR2A|= (1<<COM2B1)|(1<<COM2B0);
		}else{
		TCCR2A|= (1<<COM2B1);
	}
	TCCR2A |=(1<<WGM20)|(1<<WGM21);
	if (Preescaler == 1024){
	TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20);//Prescaler
	}
}

void setPWMChanel2A(uint8_t dutyCycle){
	dutyCycle = MapPWM2(dutyCycle, 0, 255,  6, 36);
	OCR2A = dutyCycle;
}

void setPWMChanel2B(uint8_t dutyCycle){
	dutyCycle = MapPWM2(dutyCycle, 0, 255,  25, 44);
	OCR2B = dutyCycle;
	}
