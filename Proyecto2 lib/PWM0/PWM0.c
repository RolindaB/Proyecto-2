/*
 * PWM0.c
 *
 * Created: 17/05/2024 10:41:48
 *  Author: asrol
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "PWM0.h"

void RSTPWM0(void) {
	TCCR0A = 0; // RESET
	TCCR0B = 0; // RESET
}

float MapPWM0(float dutyCycle, float EnMin, float EnMax, float SalMin, float SalMax) {
	return ((dutyCycle - EnMin) * (SalMax - SalMin) / (EnMax - EnMin));
}

void setPWM0fastA(uint8_t inverted, uint16_t Preescaler) {
	DDRD |= (1 << DDD6); // PIN D6 COMO SALIDA
	if (inverted) {
		TCCR0A |= (1 << COM0A1) | (1 << COM0A0); // OC0A INVERTIDO
		} else {
		TCCR0A |= (1 << COM0A1); // OC0A NO INVERTIDO
	}
	TCCR0A |= (1 << WGM00) | (1 << WGM01); // MODO PWM FAST, 8 bits
	if (Preescaler == 1024) {
		TCCR0B |= (1 << CS02) | (1 << CS00); // PRESCALER DE 1024
	}
}

void setPWM0fastB(uint8_t inverted, uint16_t Preescaler) {
	DDRD |= (1 << DDD5); // PIN D5 COMO SALIDA
	if (inverted) {
		TCCR0A |= (1 << COM0B1) | (1 << COM0B0); // OC0B INVERTIDO
		} else {
		TCCR0A |= (1 << COM0B1); // OC0B NO INVERTIDO
	}
	TCCR0A |= (1 << WGM00) | (1 << WGM01); // MODO PWM FAST, 8 bits
	if (Preescaler == 1024) {
		TCCR0B |= (1 << CS02) | (1 << CS00); // PRESCALER DE 1024
	}
}

void setPWMChanel0A(uint8_t dutyCycle) {
	dutyCycle = MapPWM0(dutyCycle, 0, 255, 6, 36);
	OCR0A = dutyCycle;
}

void setPWMChanel0B(uint8_t dutyCycle) {
	dutyCycle = MapPWM0(dutyCycle, 0, 255, 17,43);
	OCR0B = dutyCycle;
}