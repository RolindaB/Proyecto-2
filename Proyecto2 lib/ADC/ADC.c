/*
 * ADC.c
 *
 * Created: 17/05/2024 10:43:18
 *  Author: asrol
 */ 
#include "ADC.h"
#include <stdint.h>


void initADC(void) {
	ADMUX = 0;
	// Selecciona ADC6 como entrada anal�gica (MUX2:0 = 0b110)
	//ADMUX |= (1 << MUX2) | (1 << MUX1);
	// Configura referencia de voltaje AVCC con capacitor en AREF
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	// Configura el ADC para operar en modo de 8 bits
	ADMUX |= (1 << ADLAR);
	ADCSRA = 0;
	// Habilita el ADC y configura la prescaler a 128 (Frecuencia de muestreo = F_CPU / 128)
	ADCSRA |= (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADEN); // habilitar interrupci�n
}