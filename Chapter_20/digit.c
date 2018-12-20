/*
 * light_on.c
 *
 * Created: 2018-12-20 오전 10:20:51
 *  Author: SunKim
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LEDMatrixTest.h"
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

void LEDMatrix_init(void)
{
	// 해당 column 핀을 출력으로 설정
	MATRIX_COL1_DDR |= (1 << MATRIX_COL1_PIN);
	MATRIX_COL2_DDR |= (1 << MATRIX_COL2_PIN);
	MATRIX_COL3_DDR |= (1 << MATRIX_COL3_PIN);
	MATRIX_COL4_DDR |= (1 << MATRIX_COL4_PIN);
	MATRIX_COL5_DDR |= (1 << MATRIX_COL5_PIN);
	MATRIX_COL6_DDR |= (1 << MATRIX_COL6_PIN);
	MATRIX_COL7_DDR |= (1 << MATRIX_COL7_PIN);
	MATRIX_COL8_DDR |= (1 << MATRIX_COL8_PIN);
	
	// 해당 row 핀을 출력으로 설정
	MATRIX_ROW1_DDR |= (1 << MATRIX_ROW1_PIN);
	MATRIX_ROW2_DDR |= (1 << MATRIX_ROW2_PIN);
	MATRIX_ROW3_DDR |= (1 << MATRIX_ROW3_PIN);
	MATRIX_ROW4_DDR |= (1 << MATRIX_ROW4_PIN);
	MATRIX_ROW5_DDR |= (1 << MATRIX_ROW5_PIN);
	MATRIX_ROW6_DDR |= (1 << MATRIX_ROW6_PIN);
	MATRIX_ROW7_DDR |= (1 << MATRIX_ROW7_PIN);
	MATRIX_ROW8_DDR |= (1 << MATRIX_ROW8_PIN);
}

void LEDMatrix_writeColumn(uint8_t col_data)	// column 데이터 출력
{
	if(col_data & (1 << 0))	MATRIX_COL1_PORT |= (1 << MATRIX_COL1_PIN); // ON
	else MATRIX_COL1_PORT &= ~(1 << MATRIX_COL1_PIN);	// OFF
	if(col_data & (1 << 1))	MATRIX_COL2_PORT |= (1 << MATRIX_COL2_PIN);
	else MATRIX_COL2_PORT &= ~(1 << MATRIX_COL2_PIN);
	if(col_data & (1 << 2))	MATRIX_COL3_PORT |= (1 << MATRIX_COL3_PIN);
	else MATRIX_COL3_PORT &= ~(1 << MATRIX_COL3_PIN);
	if(col_data & (1 << 3))	MATRIX_COL4_PORT |= (1 << MATRIX_COL4_PIN);
	else MATRIX_COL4_PORT &= ~(1 << MATRIX_COL4_PIN);
	if(col_data & (1 << 4))	MATRIX_COL5_PORT |= (1 << MATRIX_COL5_PIN);
	else MATRIX_COL5_PORT &= ~(1 << MATRIX_COL5_PIN);
	if(col_data & (1 << 5))	MATRIX_COL6_PORT |= (1 << MATRIX_COL6_PIN);
	else MATRIX_COL6_PORT &= ~(1 << MATRIX_COL6_PIN);
	if(col_data & (1 << 6))	MATRIX_COL7_PORT |= (1 << MATRIX_COL7_PIN);
	else MATRIX_COL7_PORT &= ~(1 << MATRIX_COL7_PIN);
	if(col_data & (1 << 7))	MATRIX_COL8_PORT |= (1 << MATRIX_COL8_PIN);
	else MATRIX_COL8_PORT &= ~(1 << MATRIX_COL8_PIN);
}

void LEDMatrix_writeRow(uint8_t row_data)	// row 데이터 출력
{
	if(row_data & (1 << 7))	MATRIX_ROW1_PORT |= (1 << MATRIX_ROW1_PIN);
	else MATRIX_ROW1_PORT &= ~(1 << MATRIX_ROW1_PIN);
	if(row_data & (1 << 6))	MATRIX_ROW2_PORT |= (1 << MATRIX_ROW2_PIN);
	else MATRIX_ROW2_PORT &= ~(1 << MATRIX_ROW2_PIN);
	if(row_data & (1 << 5))	MATRIX_ROW3_PORT |= (1 << MATRIX_ROW3_PIN);
	else MATRIX_ROW3_PORT &= ~(1 << MATRIX_ROW3_PIN);
	if(row_data & (1 << 4))	MATRIX_ROW4_PORT |= (1 << MATRIX_ROW4_PIN);
	else MATRIX_ROW4_PORT &= ~(1 << MATRIX_ROW4_PIN);
	if(row_data & (1 << 3))	MATRIX_ROW5_PORT |= (1 << MATRIX_ROW5_PIN);
	else MATRIX_ROW5_PORT &= ~(1 << MATRIX_ROW5_PIN);
	if(row_data & (1 << 2))	MATRIX_ROW6_PORT |= (1 << MATRIX_ROW6_PIN);
	else MATRIX_ROW6_PORT &= ~(1 << MATRIX_ROW6_PIN);
	if(row_data & (1 << 1))	MATRIX_ROW7_PORT |= (1 << MATRIX_ROW7_PIN);
	else MATRIX_ROW7_PORT &= ~(1 << MATRIX_ROW7_PIN);
	if(row_data & (1 << 0))	MATRIX_ROW8_PORT |= (1 << MATRIX_ROW8_PIN);
	else MATRIX_ROW8_PORT &= ~(1 << MATRIX_ROW8_PIN);
}

int main(void)
{
	LEDMatrix_init();

	uint8_t digits[10][8] = {
		 {0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x3c},
		 {0x1c,0x08,0x08,0x08,0x08,0x08,0x18,0x08},
		 {0x7e,0x20,0x10,0x08,0x04,0x02,0x42,0x3c},
		 {0x3c,0x42,0x02,0x02,0x1c,0x02,0x42,0x3c},
		 {0x04,0x04,0x04,0x7e,0x44,0x24,0x14,0x0c},
		 {0x7c,0x02,0x02,0x02,0x7c,0x40,0x40,0x7e},
		 {0x3c,0x42,0x42,0x7c,0x40,0x40,0x42,0x3c},
		 {0x40,0x20,0x10,0x08,0x04,0x02,0x02,0x7e},
		 {0x3c,0x42,0x42,0x42,0x3c,0x42,0x42,0x3c},
		 {0x20,0x10,0x08,0x04,0x3c,0x42,0x42,0x3c},
	};

	TCCR0B |= (1<<CS01) | (0 << CS00); // 분주비를 64로 설정
	TIMSK0 |= (1 << TOIE0); // 오버플로 인터럽트 허용
	sei(); // 전역적으로 인터럽트 허용
	unsigned long time_previous, time_current;
	
	time_previous = millis();
	int j=0;
	int count=0;
	while(1)
	{
		while(1){
			time_previous = millis();
			
			for(int i = 0; i < 8; i++){
				// 열 단위 스캔이므로 하나의 열에만 LOW를 가하고 나머지는 HIGH를 가함
				uint8_t col_data = ~(1 << i);
				LEDMatrix_writeColumn(col_data);
				// 각 열에 대응하는 스마일 문자 데이터를 출력
				LEDMatrix_writeRow(digits[j][i]);
			
				_delay_ms(2);
			}
			if((time_current - time_previous) > 1000){ // 1초 경과
				time_previous = time_current;
				count++;
				if(count==10){
					count=0;
					j++;
					if(j==10) j=0;
				}
			}
		}
	}
}
