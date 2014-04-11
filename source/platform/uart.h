/**
*	File:	uart.h
*	Date:	27.03.2014
*	Author:	Felder Mario
*
*
*	Version:		0.1
*	Last Change:	-/-
*	History:		-
*
*	Hardware:		PIC18F4610-I/P
*	Compiler:		HI-TECH C Compiler for PIC18 (v9.8)
**/

/**------------------ PROTOTYPES ------------------**/
void init_uart(void);
void uart_send_Byte(uint8 cByte);
uint8 uart_receive_Byte(void);
void uart_send_Array(uint8 iLength, uint8* cArray);
void uart_receive_Array(uint8 iLength, uint8* cBuffer);

/**------------------ DEFINES ------------------**/
#ifndef UART_H
#define UART_H

	#define SPBRG_VALUE 42	//Baudrate: 115'200

#endif  // !UART_H