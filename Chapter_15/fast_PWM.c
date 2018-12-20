/*
 * fast_PWM.c
 *
 * Created: 2018-12-17 오전 8:52:17
 *  Author: SunKim
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	//파형 출력 핀인 PB3핀 (OC2A핀, 아두이노 11번)을 출력으로 설정
	DDRB |= (1<<PB3);
	
	//타이머/카운터 2번을 고속 PWM으로 설정
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2A |= (1 << COM2A1);
	TCCR2B |= (1 << CS22);
	
	while(1){
		for(int i = 0; i<256; i++){
			OCR2A = i;
			_delay_ms(50);
		}
	}
}