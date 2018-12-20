/*
 * fast_PWM_2.c
 *
 * Created: 2018-12-17 오전 8:55:47
 *  Author: SunKim
 */ 


#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	//파형 출력 핀인 PD3핀 (OC2A핀, 아두이노 3번)을 출력으로 설정
	DDRD |= (1<<PD3);
	
	//타이머/카운터 2번을 고속 PWM으로 설정
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2B |= (1 << WGM22);
	TCCR2A |= (1 << COM2B1);
	TCCR2B |= (1 << CS22);
	
	OCR2A = 128;
	
	while(1){
		for(int i = 0; i<128; i++){
			OCR2B = i;
			_delay_ms(10);
		}
	}
}