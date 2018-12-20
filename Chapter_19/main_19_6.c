/*
 * main_19_6.c
 *
 * Created: 2018-12-19 오후 2:22:37
 *  Author: SunKim
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	uint8_t numbers[]
	= {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};
	int i, j;
	DDRD = 0xFF; // 세그먼트 제어 핀 8개를 출력으로 설정
	DDRB = 0x0F; // 자릿수 선택 핀 4개를 출력으로 설정
	while(1)
	{
		for(i = 0; i < 4; i++){
			// 해당 자리에만 0(GND)을 출력하고 나머지에는 1을 출력하여 자리 선택
			PORTB = 0x0F & ~(1 << i);
			//PORTB=0x00;
			for(j = 0; j < 10; j++){
				PORTD = numbers[j]; // 숫자 데이터 출력
				_delay_ms(500); // 0.1초 간격으로 전환
			}
		}
	}
	return 1;
}