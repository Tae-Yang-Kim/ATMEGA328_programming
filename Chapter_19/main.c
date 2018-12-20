/*
 * Chapter_19.c
 *
 * Created: 2018-12-19 오전 9:51:12
 * Author : SunKim
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	uint8_t numbers[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};
	int count = 0;
	DDRD = 0xff;
    /* Replace with your application code */
    while (1) 
    {
		PORTD=numbers[count];
		count = (count+1)%10;
		
		_delay_ms(1000);
    }
	
	return 1;
}

