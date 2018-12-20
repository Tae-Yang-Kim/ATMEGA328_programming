/*
 * main_2.c
 *
 * Created: 2018-12-19 오전 10:06:58
 *  Author: SunKim
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int interrupt_count = 0;

ISR(TIMER0_OVF_vect){
	interrupt_count++;
}

int main(void){
	uint8_t numbers[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};
	int count = 0;
	DDRD = 0xff;
	PORTD = numbers[0];
	
	//타이머 카운터 0번 인터럽트 설정
	TCCR0B |= (1<<CS02) | (1<<CS00);
	TIMSK0 |= (1 << TOIE0);
	sei();
	
	/* Replace with your application code */
	while (1)
	{
		if(interrupt_count==61){
			interrupt_count=0;
			
			count=(count+1)%10;
			PORTD=numbers[count];
		}
	}
	
	return 1;
}