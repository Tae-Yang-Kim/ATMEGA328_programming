/*
 * Chapter_16.c
 *
 * Created: 2018-12-17 오후 1:53:22
 * Author : SunKim
 */ 
#define F_CPU 160000000UL
#include <avr/io.h>
#include <string.h>
#include "UART.h"
#include "25LC010.h"

int main(void)
{
	uint8_t i;
	
	SPI_Init();
	UART_INIT();
    /* Replace with your application code */
	
	for(i=0; i<128; i++){
		EEPROM_writeByte(i,i);
	}
	
	for(i=0; i<128; i++){
		UART_print8bitNumber(EEPROM_readByte(i));
		UART_transmit('\n');
	}
	
    while (1) 
    {
    }
	
	return 0;
}

