/*
 * LED_varible.c
 *
 * Created: 2018-12-13 오후 2:17:48
 *  Author: SunKim
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void ADC_INIT(unsigned char channel){
	ADMUX	|= 0x40;
	ADCSRA	|= 0x07;
	ADCSRA	|= (1<<ADEN);
	ADCSRA	|= (1<<ADATE);
	
	ADMUX	= ((ADMUX&0xE0) | channel);
	ADCSRA	|= (1<<ADSC);
}

int read_ADC(void){
	while(!(ADCSRA & (1<<ADIF)));
	
	return ADC;
}

void PORT_INIT(void){
	DDRD = 0xFF;
	PORTD = 0x00;
}

int main(void){
	int value;
	uint8_t on_off;
	
	ADC_INIT(0);
	PORT_INIT();
	
	while(1){
		value = read_ADC() >> 7;
		
		on_off = 0;
		for(int i=0; i<=value; i++){
			on_off |= (0x01 << i);
		}
		PORTD = on_off;
	}
}