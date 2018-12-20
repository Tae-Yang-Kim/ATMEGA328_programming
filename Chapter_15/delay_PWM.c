/*
 * Chapter_15.c
 *
 * Created: 2018-12-17 오전 8:44:24
 * Author : SunKim
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define LED_TIME 20

void trun_on_LED_in_PWM_manner(int dim){
	int i;
	PORTB = 0xff;
	
	for(i=0; i<256; i++){
		if(i>dim) PORTB = 0x00;
		_delay_us(LED_TIME);
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRB = 0xff;
	
	int dim = 0;
	int direction = 1;
	
    while (1) 
    {
		if(dim==0) direction = 1;
		if(dim==255) direction=-1;
		
		dim += direction;		//밝기변화
		
		
		trun_on_LED_in_PWM_manner(dim);
    }
}

