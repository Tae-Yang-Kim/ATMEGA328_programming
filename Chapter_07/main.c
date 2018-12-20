/*
 * Chapter_07.c
 *
 * Created: 2018-12-11 오전 9:28:36
 * Author : SunKim
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

void UART_INIT(void){
	UCSR0A |= _BV(U2X0);//2배속 모드
	
	UBRR0H = 0x00; //통신 속도(보율)조정
	UBRR0L = 207;
	
	//비동기, 8비트 데이터, 패리티 없음, 1비트 정지 비트 모드
	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);
}

unsigned char UART_receive(void){
 	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void UART_transmit(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

int main(int argc, char *argv[]){
	unsigned char data;
	
	UART_INIT();
	while(1){
		data = UART_receive();

		UART_transmit(data);
	}
	
	return 0;
}

#if 0

#define F_CPU 16000000L
#include <avr/io.h>
#include<util/delay.h>

int main(void)
{
	int i;
	DDRD = 0xff;
    /* Replace with your application code */
    while (1) 
    {
		/*//PORTD*=2;
		PORTD<<=1;
		if(PORTD==0x00){
			PORTD=0x01;
		}*/
		for(i=0; i<8; i++){
			_delay_ms(1000);
			PORTD=0x01<<i;
		}
		for(i=0; i<8; i++){
			_delay_ms(1000);
			PORTD=0x80>>i;
		}
    }
	return 1;
}

#endif