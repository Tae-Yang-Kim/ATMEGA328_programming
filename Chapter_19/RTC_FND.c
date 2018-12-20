/*
 * RTC_FND.c
 *
 * Created: 2018-12-19 오후 4:44:51
 *  Author: SunKim
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "I2C.h"
#define SEGMENT_DELAY 5
// 1마이크로초당 클록의 수
#define CLOCKS_PER_MICRO ( F_CPU / 1000000L )
// 클록 수를 마이크로초로 변환
#define CLOCKS_TO_MICROSECONDS(a) ( (a) / CLOCKS_PER_MICRO )
// 타이머0의 분주비를 64로 설정한 경우
// 오버플로 인터럽트가 발생하기까지의 마이크로초 단위 경과 시간
#define MICROSECONDS_PER_TIMER0_OVERFLOW ( CLOCKS_TO_MICROSECONDS(64 * 256) )
// 오버플로 인터럽트가 발생한 경우 밀리초 단위 증가 시간
#define MILLIS_INCREMENT_PER_OVERFLOW ( MICROSECONDS_PER_TIMER0_OVERFLOW / 1000 )
// 오버플로 인터럽트가 발생한 경우
// 밀리초 단위 증가를 제외하고 남는 마이크로초 단위 증가 시간
#define MICROS_INCREMENT_PER_OVERFLOW ( MICROSECONDS_PER_TIMER0_OVERFLOW % 1000 )
// 프로그램 시작 이후의 경과 시간
volatile unsigned long timer0_millis = 0;
volatile int timer0_micros = 0;
ISR(TIMER0_OVF_vect)
{
	unsigned long m = timer0_millis;
	int f = timer0_micros;
	m += MILLIS_INCREMENT_PER_OVERFLOW; // 밀리초 단위 시간 증가
	f += MICROS_INCREMENT_PER_OVERFLOW; // 마이크로초 단위 시간 증가
	// 마이크로초가 1000을 넘어가면 밀리초를 증가시킴
	int micro_to_millis = f / 1000;
	m += micro_to_millis;
	f = f % 1000;
	timer0_millis = m;
	timer0_micros = f;
}
unsigned long millis()
{
	unsigned long m;
	uint8_t oldSREG = SREG; // 상태 레지스터 값 저장
	// timer0_millis 값을 읽는 동안
	// timer0_millis 값이 변하지 않도록 인터럽트를 비활성화
	cli();
	m = timer0_millis;
	SREG = oldSREG; // 이전 상태 레지스터 값 복원
	return m; // 프로그램 시작 후 경과 시간
}

uint8_t bcd_to_decimal(uint8_t bcd){ // BCD 형식 -> 이진수 형식
	return (bcd >> 4) * 10 + (bcd & 0x0F);
}
uint8_t decimal_to_bcd(uint8_t decimal){ // 이진수 형식 -> BCD 형식
	return ( ((decimal / 10) << 4) | (decimal % 10) );
}
int main(void)
{
	int sec;
	int minute;
	int hour;
	int week;
	int day;
	int month;
	int year;
	TCCR0B |= (0<<CS02) | (1<<CS01) | (0 << CS00); // 분주비를 64로 설정
	TIMSK0 |= (1 << TOIE0); // 오버플로 인터럽트 허용
	sei(); // 전역적으로 인터럽트 허용
	unsigned long time_previous, time_current;
	DDRD = 0xFF; // 세그먼트 제어 핀 8개를 출력으로 설정
	DDRB = 0x0F; // 자릿수 선택 핀 4개를 출력으로 설정
	
	uint8_t numbers[]
	= {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};
	int count = 0000; // 현재 표시할 숫자(0~9)
	int thousands, hundreds, tens, ones;
	
	uint8_t i;
	I2C_init(); // I2C 초기화
	uint8_t address = 0x68; // RTC 모듈의 I2C 주소
	// 초, 분, 시, 요일, 일, 월, 년
	// 2014년 9월 1일 월요일 12시 34분 56초
	uint8_t data[] = {10, 00, 12, 2, 1, 9, 14};
	// RTC 모듈에 시간 설정
	I2C_start(); // I2C 시작
	I2C_transmit(address << 1); // I2C 주소 전송. 쓰기 모드
	// RTC에 데이터를 기록할 메모리 시작 주소 전송
	I2C_transmit(0);
	for(i = 0; i < 7; i++){
		I2C_transmit(decimal_to_bcd(data[i])); // 시간 설정
	}
	I2C_stop(); // I2C 정지
	_delay_ms(2000); // 2초 대기
	I2C_start(); // I2C 시작
	I2C_transmit(address << 1); // I2C 주소 전송. 쓰기 모드
	// RTC에서 데이터를 읽어 올 메모리 시작 주소 전송
	I2C_transmit(0);
	I2C_stop(); // I2C 정지
	_delay_ms(1000);
	I2C_start(); // I2C 읽기 모드로 다시 시작
	I2C_transmit( (address << 1) + 1 ); // I2C 주소 전송. 읽기 모드
	sec		= bcd_to_decimal(I2C_receive());
	minute  = bcd_to_decimal(I2C_receive());
	hour	= bcd_to_decimal(I2C_receive());
	week	= bcd_to_decimal(I2C_receive());
	day		= bcd_to_decimal(I2C_receive());
	month	= bcd_to_decimal(I2C_receive());
	year	= bcd_to_decimal(I2C_receive());
	I2C_stop(); // I2C 정지
	while(1){
		I2C_start(); // I2C 시작
		I2C_transmit(address << 1); // I2C 주소 전송. 쓰기 모드
		// RTC에 데이터를 기록할 메모리 시작 주소 전송
		I2C_transmit(0);
		I2C_stop(); // I2C 정지
		I2C_start(); // I2C 시작
		I2C_transmit(address << 1); // I2C 주소 전송. 쓰기 모드
		// RTC에서 데이터를 읽어 올 메모리 시작 주소 전송
		I2C_transmit(0);
		I2C_stop(); // I2C 정지
		I2C_start(); // I2C 읽기 모드로 다시 시작
		I2C_transmit( (address << 1) + 1 ); // I2C 주소 전송. 읽기 모드
		sec		= bcd_to_decimal(I2C_receive());
		minute  = bcd_to_decimal(I2C_receive());
		hour	= bcd_to_decimal(I2C_receive());
		week	= bcd_to_decimal(I2C_receive());
		day		= bcd_to_decimal(I2C_receive());
		month	= bcd_to_decimal(I2C_receive());
		year	= bcd_to_decimal(I2C_receive());
		I2C_stop(); // I2C 정지

		PORTB = 0x0E; // 천의 자리 출력
		PORTD = numbers[minute/10];
		_delay_ms(SEGMENT_DELAY);
		PORTB = 0x0D; // 백의 자리 출력
		PORTD = numbers[minute%10];
		_delay_ms(SEGMENT_DELAY);
		PORTB = 0x0B; // 십의 자리 출력
		PORTD = numbers[sec/10];
		_delay_ms(SEGMENT_DELAY);
		PORTB = 0x07; // 일의 자리 출력
		PORTD = numbers[sec%10];
		_delay_ms(SEGMENT_DELAY);
	}
}