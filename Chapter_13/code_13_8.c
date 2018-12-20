/*
 * code_13_8.c
 *
 * Created: 2018-12-14 오전 10:19:52
 *  Author: SunKim
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(PCINT2_vect){
	if(PIND&0x04){
		PORTB = 0x00;
	}
	else{
		PORTB = 0x20;
	}
}

void INIT_PORT(void){
	DDRB = 0x20;
	PORTB = 0x00;
	
	DDRD = 0x00;
	PORTD = 0x04;
}

void INIT_PCINT2(void){
	PCICR  |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT18);
	sei();
}

int main(void){
	INIT_PORT();
	INIT_PCINT2();
	
	while(1){}
}