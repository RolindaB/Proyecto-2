/*
 * PWM0.c
 *
 * Created: 17/05/2024 10:41:48
 *  Author: asrol
 */ 
#include "PWM0.h"

void setupPWM0(void) {
	// Configurar los pines como salidas PWM
	DDRD |= (1 << DDD6); // Canal C (OC0A)
	DDRD |= (1 << DDD5); // Canal D (OC0B)

	// Configurar el modo de PWM en el Timer0
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01); // Modo Fast PWM, No invertido
	TCCR0B = (1 << CS01) | (1 << CS00); // Preescaler de 64
}

void setPWMChannelC(uint8_t duty_cycle) {
	OCR0A = (duty_cycle * 180) /255 + 10;
}

void setPWMChannelD(uint8_t duty_cycle) {
	OCR0B = (duty_cycle * 180) /255 + 10;
}