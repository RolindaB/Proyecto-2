//***************************************************************************************************
// Universidad del Valle de Guatemala
// IE3028 Programación de microcontroladores
// Autor: Rolinda Beb
// Proyecto: Brazo
// Hardware: Arduino Nano - ATMega328p
//***************************************************************************************************
#define F_CPU 16000000UL

/* ---------------------------LIBRERIAS----------------------------------------*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC/ADC.h"    // Incluye la biblioteca para el ADC
#include "PWM2/PWM2.h"
#include "PWM0/PWM0.h"	 // Incluye la biblioteca para el PWM0
#include "EPROM/EPROM.h"//Biblioteca de Eprom

/* ---------------------------VARIABLES----------------------------------------*/

volatile uint8_t opcion_menu = 0;
//variables para el control de motores
uint8_t adc_value_A = 0;
uint8_t adc_value_B = 0;
uint8_t adc_value_C = 0;
uint8_t adc_value_D = 0;

/*--------------------Función para inicializar el hardware---------------------*/
void setUP() {
	cli();
	// Configurar el entradas
	DDRD &= ~((1 << DDD2)|(1 << DDD7)); // PD2 es el pin del botón CAMBIO DE ESTADO, (pd7) eprom
	PORTD |= (1 << DDD2)|(1 << DDD7); // activar pull-up
	DDRB &= ~((1 << DDB4)|(1 << DDB2)|(1 << DDB0)); //PIN DE BOTONES PARA GUADAR EN LA EMPROM PB4, PB2, PB0
	PORTB |= (1 << DDB4)|(1 << DDB2)|(1 << DDB0);// Habilitar pull-up

	// Habilita las interrupciones por cambio de pin en el puerto C para los pines PC0
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT18) ;

	// Configurar los pines de los LEDs como salidas
	DDRC |= (1 << DDC0)|(1<<DDC1)|(1<<DDC5); // C0 ,C1,C5 es el pin del primer LED
	DDRB |= (1 << DDB1); // PB1 guardar

	// Inicializar ADC y PWM
	initADC();
	RSTPWM0();
	RSTPWM2();
	setPWM0fastA(0, 1024);
	setPWM0fastB(0, 1024);
	setPWM2fastA(0, 1024);
	setPWM2fastB(0, 1024);

	// Habilitar las interrupciones globales
	sei();
}

/* -----------------------------Eprom------------------------------------*/
void GuardarEP(){
	
	// Leer el estado de los botones
	if (!(PINB & (1 << PB4))) {
		// PB4 está presionado
		EEPROM_write(0, adc_value_A);
		EEPROM_write(1, adc_value_B);
		EEPROM_write(2, adc_value_C);
		EEPROM_write(3, adc_value_D);
		PORTB |= (1 << 1);
		_delay_ms(20);
		PORTB &= ~(1 << 1); // Apagar

		} else if (!(PINB & (1 << PB2))) {
		// PB3 está presionado
		EEPROM_write(4, adc_value_A);
		EEPROM_write(5, adc_value_B);
		EEPROM_write(6, adc_value_C);
		EEPROM_write(7, adc_value_D);
		PORTB |= (1 << 1);
		_delay_ms(20);
		PORTB &= ~(1 << 1); // Apagar

		} else if (!(PIND & (1 << PD7))) {
		// PD7 está presionado
		EEPROM_write(8, adc_value_A);
		EEPROM_write(9, adc_value_B);
		EEPROM_write(10, adc_value_C);
		EEPROM_write(11, adc_value_D);
		PORTB |= (1 << 1);
		_delay_ms(20);
		PORTB &= ~(1 << 1); // Apagar

		} else if (!(PINB & (1 << PB0))) {
		// PB0 está presionado
		EEPROM_write(12, adc_value_A);
		EEPROM_write(13, adc_value_B);
		EEPROM_write(14, adc_value_C);
		EEPROM_write(15, adc_value_D);
		PORTB |= (1 << 1);
		_delay_ms(20);
		PORTB &= ~(1 << 1); // Apagar
	}

	// Pequeño retardo
	_delay_ms(50);
}

void leerEP(){
	// Leer el estado de los botones
	if (!(PINB & (1 << PB4))) { // PB4 está presionado
		adc_value_A = EEPROM_read(0);
		setPWMChanel0A(adc_value_A);
		adc_value_B = EEPROM_read(1);
		setPWMChanel0B(adc_value_B);
		adc_value_C = EEPROM_read(2);
		setPWMChanel2A(adc_value_C);
		adc_value_D = EEPROM_read(3);
		setPWMChanel2B(adc_value_D);
		PORTB |= (1 << 1);
		_delay_ms(50);
		PORTB &= ~(1 << 1); // Apagar

		} else if (!(PINB & (1 << PB2))) { // PB3 está presionado
		adc_value_A = EEPROM_read(4);
		setPWMChanel0A(adc_value_A);
		adc_value_B = EEPROM_read(5);
		setPWMChanel0B(adc_value_B);
		adc_value_C = EEPROM_read(6);
		setPWMChanel2A(adc_value_C);
		adc_value_D = EEPROM_read(7);
		setPWMChanel2B(adc_value_D);
		PORTB |= (1 << 1);
		_delay_ms(50);
		PORTB &= ~(1 << 1); // Apagar

		} else if (!(PIND & (1 << PD7))) { // PD7 está presionado
		adc_value_A = EEPROM_read(8);
		setPWMChanel0A(adc_value_A);
		adc_value_B = EEPROM_read(9);
		setPWMChanel0B(adc_value_B);
		adc_value_C = EEPROM_read(10);
		setPWMChanel2A(adc_value_C);
		adc_value_D = EEPROM_read(11);
		setPWMChanel2B(adc_value_D);
		PORTB |= (1 << 1);
		_delay_ms(50);
		PORTB &= ~(1 << 1); // Apagar

		} else if (!(PINB & (1 << PB0))) { // PB0 está presionado
		adc_value_A = EEPROM_read(12);
		setPWMChanel0A(adc_value_A);
		adc_value_B = EEPROM_read(13);
		setPWMChanel0B(adc_value_B);
		adc_value_C = EEPROM_read(14);
		setPWMChanel2A(adc_value_C);
		adc_value_D = EEPROM_read(15);
		setPWMChanel2B(adc_value_D);
		PORTB |= (1 << 1);
		_delay_ms(50);
		PORTB &= ~(1 << 1); // Apagar
	}

	// Pequeño retardo
	_delay_ms(50);
}

/* -----------------------------Modo manual------------------------*/
void Manual(){
	// Inicia una conversión ADC para el canal D (A6)
	ADMUX = (ADMUX & 0xF8) | 0x06;
	ADCSRA |= (1 << ADSC);
	_delay_ms(10);

	// Inicia una conversión ADC para el canal C (A4)
	ADMUX = (ADMUX & 0xF8) | 0x04;
	ADCSRA |= (1 << ADSC);
	_delay_ms(10);

	// Inicia una conversión ADC para el canal B (A3)
	ADMUX = (ADMUX & 0xF8) | 0x03;
	ADCSRA |= (1 << ADSC);
	_delay_ms(10);

	// Inicia una conversión ADC para el canal A (A2)
	ADMUX = (ADMUX & 0xF8) | 0x02;
	ADCSRA |= (1 << ADSC);
	_delay_ms(10);
}

/* -------------Función para manejar la opción seleccionada----------------*/
void manejar_opcion() {
	// Apagar todos los LEDs
	PORTC &= ~(1 << 0); // Apagar el primer LED (C0)
	PORTC &= ~(1 << 1); // Apagar el segundo LED (C1)
	PORTC &= ~(1 << 5); // Apagar el tercer LED (C5)

	switch (opcion_menu) {
		/* --------------------------Modo Manual ------------------------*/
		case 0:
		// Encender el primer LED
		PORTC |= (1 << 0); // Encender el primer LED (C0)
		Manual(); //Habilitar la función manual
		GuardarEP();// habilitar la funcion de guardar en la eprom
		break;

		/* -------------------------- Modo EEPROM ------------------------*/
		case 1:
		// Encender el segundo LED
		PORTC |= (1 << 1); // Encender el segundo LED (C1)
		leerEP();
		break;

		/* -----------------------Modo Adafruit---------------------------*/
		case 2:
		// Encender el tercer LED
		PORTC |= (1 << 5); // Encender el tercer LED (C5)
		break;
	}
}

/* -----------------------------Interrupción del ADC------------------------*/
ISR(ADC_vect) {
	if (opcion_menu == 0) { // Solo actualizar los valores en el modo manual
		if ((ADMUX & 0x07) == 0x03) { // Asegúrate de que este es el canal correcto
			adc_value_B = ADCH;
			setPWMChanel0B(adc_value_B); //A3
			} else if ((ADMUX & 0x07) == 0x06) {
			adc_value_D = ADCH;
			setPWMChanel2B(adc_value_D);//A6
			} else if ((ADMUX & 0x07) == 0x02) {
			adc_value_A = ADCH;
			setPWMChanel0A(adc_value_A);//A2
			} else if ((ADMUX & 0x07) == 0x04) {
			adc_value_C = ADCH;
			setPWMChanel2A(adc_value_C);//A4
		}
	}
	ADCSRA |= (1 << ADSC); // Iniciar la próxima conversión
}

/* -------------Interrupción del DEL BOTON----------------*/
ISR(PCINT2_vect) {
	static uint8_t ultimo_estado = 0;
	uint8_t estado_actual = PIND & (1 << PD2); // PD2 es el pin del botón
	
	// Comprobar si el estado del botón ha cambiado de alto a bajo (presionado)
	if (estado_actual == 0 && ultimo_estado != 0) {
		// Incrementar la opción del menú
		opcion_menu++;
		if (opcion_menu > 2) // Reiniciar ciclo de opciones
		opcion_menu = 0;
	}
	
	// Guardar el estado actual del botón para la próxima comparación
	ultimo_estado = estado_actual;
	PCIFR|=(1<<PCIF2);
}

/* -----------------------------Función principal--------------------------*/
int main(void) {
	// Deshabilitar todas las interrupciones
	cli();
	// Inicializar hardware
	setUP();

	while (1) {
		// Manejar la opción seleccionada (Menú)
		manejar_opcion();
	}

	return 0;
}
