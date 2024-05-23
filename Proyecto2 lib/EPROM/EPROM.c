/*
 * EPROM.c
 *
 * Created: 17/05/2024 17:05:17
 *  Author: asrol
 */ 
#include "EPROM.h"
#include <stdint.h>
//lectura de Eeprom

// Lectura de EEPROM
unsigned char EEPROM_read(unsigned int uiAddress) {
	while (EECR & (1 << EEPE)); // Esperar a que termine la escritura anterior
	EEAR = uiAddress; // Establecer dirección de lectura
	EECR |= (1 << EERE); // Iniciar lectura
	return EEDR; // Retornar datos
}

// Escritura de EEPROM
void EEPROM_write(unsigned int uiAddress, unsigned char ucData) {
	while (EECR & (1 << EEPE)); // Esperar a que termine la escritura anterior
	EEAR = uiAddress; // Establecer dirección de escritura
	EEDR = ucData; // Establecer datos a escribir
	EECR |= (1 << EEMPE); // Habilitar la escritura de datos
	EECR |= (1 << EEPE); // Iniciar escritura
}