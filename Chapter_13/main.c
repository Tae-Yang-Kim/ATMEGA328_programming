/*
 * Chapter_13.c
 *
 * Created: 2018-12-14 오전 9:52:14
 * Author : SunKim
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect){
	if(PIND&0x04){
		PORTB = 0x00;
	}
	else
	{
		PORTB=0x20;
	}
	_delay_ms(1000);
}

void INIT_PORT(void){
	DDRB = 0x20;
	PORTB = 0x00;
	
	DDRD = 0x00;
	PORTD = 0x04;
}

void INIT_INT0(void){
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC00);
	//EICRA |= 0x02;
	sei();
}

int main(void)
{
	INIT_PORT();
	INIT_INT0();
    /* Replace with your application code */
    while (1) 
    {
		//INIT_INT0();
    }
}

