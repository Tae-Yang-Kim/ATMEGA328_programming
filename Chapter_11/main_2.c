/*
 * main_2.c
 *
 * Created: 2018-12-13 오전 11:18:08
 *  Author: SunKim
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

void INIT_PORT(void)
{
	DDRB = 0x20;
	PORTB=0x00;
	
	DDRD = 0x00;
	PORTD=0x04;
} 

int main(void){
	UART_INIT();
	INIT_PORT();
	int state = 0;
	
	while(1){
		if(PIND&0x04){
			state=0;
			PORTB=0x00;
		}
		else{
			//눌러지지 않은 상태에서 눌러진 상태로 바뀔때마다 '*' 문자 전송
			if(state==0) UART_transmit('*');
			state = 1;
			PORTB = 0x20;
		}
	}
}
