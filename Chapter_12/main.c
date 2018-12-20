/*
 * Chapter_12.c
 *
 * Created: 2018-12-13 오후 12:08:37
 * Author : SunKim
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART.h"

void ADC_INIT(unsigned char channel){
	ADMUX	|= 0x40;
	ADCSRA	|= 0x07;
	ADCSRA	|= (1<<ADEN);
	ADCSRA	|= (1<<ADATE);
	
	ADMUX	= ((ADMUX&0xE0) | channel);
	ADCSRA	|= (1<<ADSC);
}

int read_ADC(void){
	while(!(ADCSRA & (1<<ADIF)));
	
	return ADC;
}

void int_to_string(int n, char* buffer){
	sprintf(buffer, "%04d", n);
	buffer[4]='\0';
}

int main(void)
{
	int read;
	char buffer[5];
	
	UART_INIT();
	ADC_INIT(0);
    /* Replace with your application code */
    while (1) 
    {
		read = read_ADC();
		int_to_string(read, buffer);
		UART_printString(buffer);
		UART_printString("\n");
		
		_delay_ms(1000);
    }
}

