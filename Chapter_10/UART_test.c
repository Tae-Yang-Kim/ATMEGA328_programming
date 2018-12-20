/*
 * UART_test.c
 *
 * Created: 2018-12-12 오전 10:04:05
 *  Author: SunKim
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

int main(int argc, char *argv[]){
	unsigned char data;
	
	UART_INIT();
	while(1){
		data = UART_receive();
		UART_transmit(data);
	}
	
	return 0;
}