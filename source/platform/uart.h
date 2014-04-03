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
void send_Byte(unsigned char cByte);
unsigned char receive_Byte(void);
void send_Array(unsigned int iLength, unsigned char* cArray);
void receive_Array(unsigned int iLength, unsigned char* cBuffer);

/**------------------ DEFINES ------------------**/
#ifndef UART_H
#define UART_H

	#define SPBRG_VALUE 42	//Baudrate: 115'200

#endif  // !UART_H