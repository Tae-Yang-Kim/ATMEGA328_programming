/*
 * main_3.c
 *
 * Created: 2018-12-14 오후 3:04:49
 *  Author: SunKim
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect){
	TCNT1=0;
}

int main(void)
{
	/* Replace with your application code */	
	TCCR1B |= (1<<CS12) | (1<<CS10);
	
	OCR1A = 0x2000;
	
	//비교일치 인터럽트 발생시 OC1A 핀의 출력을 반전
	TCCR1A |= (1<<COM1A0);
	
	DDRB |= (1<<PB1);
	
	TIMSK1 |= (1 <<OCIE1A);
	sei();
	
	while (1){ }
}