/*
 * UART.h
 *
 * Created: 2018-12-12 오전 9:41:19
 *  Author: SunKim
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void UART_INIT(void);					//UART 초기화
unsigned char UART_receive(void);		//1바이트 수신
void UART_transmit(unsigned char data); //1바이트 송신
void UART_printString(char *str);		//문자열 송신
void UART_print8bitNumber(uint8_t no);	//숫자를 문자열로 변환하여 송신
void UART_print16bitNumber(uint16_t no);
void UART_print32bitNumber(uint32_t no);

#endif /* UART_H_ */



