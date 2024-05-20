/*
 * EPROM.c
 *
 * Created: 17/05/2024 17:05:17
 *  Author: asrol
 */ 
#include "EPROM.h"
//lectura de Eeprom
unsigned char EEPROM_read(unsigned int uiAddress){
	while(EECR & (1<<EEPE));
	EEAR = uiAddress;
	EEAR |=(1<<EERE);
	return EEDR;
}

void EEPROM_write(unsigned int uiAddress, unsigned char ucData){
	while(EECR & (1<<EEPE));
	EEAR = uiAddress;
	EEDR = ucData;
	EECR |=(1<<EEMPE);
	EECR |=(1<<EEPE);
	
}