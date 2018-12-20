/*
 * main.c
 *
 * Created: 2018-12-12 오전 10:08:41
 *  Author: SunKim
 */

#define F_CPU 16000000L
#define TERMINATOR '$'

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "UART.h"

int main(void){
	int counter = 100;					//카운터
	int index = 0;						//수신 버퍼에 저장할 위치
	int process_data = 0;				//문자열 처리
	char buffer[20]="";					//수신 데이터 버퍼
	char data;							//수신 데이터
	
	UART_INIT();						//UART 통신 초기화
	
	UART_printString("Current Counter Value : ");
	UART_print16bitNumber(counter);
	UART_printString("\n");
	
	while(1){
		data = UART_receive();			//데이터 수신
		if(data == TERMINATOR){
			buffer[index]='\0';
			process_data = 1;
		}
		else{
			buffer[index] = data;
			index++;
		}
		
		if(process_data==1){
			if(strcmp(buffer,"DOWN")==0){
				counter--;
				UART_printString("Current Counter Value : ");
				UART_print16bitNumber(counter);
				UART_printString("\n");
			}
			else if(strcmp(buffer, "UP")==0){
				counter++;
				UART_printString("Current Counter Value : ");
				UART_print16bitNumber(counter);
				UART_printString("\n");
			}
			else{
				UART_printString("** Unknown Command **");
				UART_printString("\n");
			}
			index = 0;
			process_data = 0;
		}
	}
}