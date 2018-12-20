/*
 * Chapter_11.c
 *
 * Created: 2018-12-13 오전 10:25:59
 * Author : SunKim
 */ 

#include <avr/io.h>

void INIT_PORT(void){
	DDRB = 0x20;
	PORTB = 0x00;
	
	DDRD = 0x00;
	PORTD= 0x04;
}


int main(void)
{
	INIT_PORT();
    /* Replace with your application code */
    while (1) 
    {
		if(PIND&0x04){
			PORTB=0x00;
		}
		else
		{
			PORTB=0x20;		
		}
    }
}

