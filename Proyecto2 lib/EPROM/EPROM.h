/*
 * EPROM.h
 *
 * Created: 17/05/2024 17:04:06
 *  Author: asrol
 */ 


#ifndef EPROM_H_
#define EPROM_H_
#include <avr/io.h>

unsigned char EEPROM_read(unsigned int uiAddress);
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

#endif /* EPROM_H_ */