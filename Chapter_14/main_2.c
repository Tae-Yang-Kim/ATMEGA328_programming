/*
 * main_2.c
 *
 * Created: 2018-12-14 오후 3:03:38
 *  Author: SunKim
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int count = 0;
int state = 0;

ISR(TIMER0_COMPA_vect){
	count++;
	TCNT0=0;
}

int main(void)
{
	/* Replace with your application code */
	DDRB = 0x20;
	PORTB = 0x00;
	
	TCCR0B |= (1<<CS02) | (1<<CS00);
	
	OCR0A = 128;
	
	TIMSK0 |= (1 <<OCIE0A);
	sei();
	
	while (1)
	{
		if(count==64){
			count=0;
			state =! state;
			if(state) PORTB=0xff;
			else PORTB = 0x00;
		}
	}
}

