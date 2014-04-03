/**
*	File:	uart.c
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

#include <htc.h>
#include "uart.h"

/**
*	Function:	init_uart
*	Parameter:	void
*	Return:		void
*
*	Description:
*	Initialisiert die UART-Schnittstelle
**/
void init_uart(void){
	SPBRG = SPBRG_VALUE;	// Set Baudrate
	BRGH = 1;				// High Speed
	BRG16 = 1;				// 16 bit Baudrate Gen
	SYNC = 0;				// Async mode
	SPEN = 1;				// Serial port enabled
	
	//Transmitter
	TXIE = 0;				// Transmit interrupt disabled
	TX9 = 0;				// Select 8-bit
	TXEN = 1;				// Transmit enbled
	
	//Receiver
	RCIE = 1;				// Receive interrupt enebled
	RX9 = 0;				// Select 8-bit
	CREN = 1;				// Enable receiver
}

/**
*	Function:	send_Byte
*	Parameter:	unsigned char cByte
*	Return:		void
*
*	Description:
*	Sendet ein Byte über die UART Schnittstelle, 
*	sobald die letze Transmission erfolgt ist.
**/
void send_Byte(unsigned char cByte){
	while(TXIF);
	TXREG = cByte;
}

/**
*	Function:	receive_Byte
*	Parameter:	void
*	Return:		unsigned char
*
*	Description:
*	Empfängt ein Byte über die UART Schnittstelle, 
*	sobald dieses vollständig Empfangen ist.
**/
unsigned char receive_Byte(void){
	while(!RCIF);
	return RCREG;
}

/**
*	Function:	send_Array
*	Parameter:	unsigned int iLength
				unsigned char* cArray
*	Return:		void
*
*	Description:
*	Sendet mehrere Bytes über die UART Schnittstelle. 
*	iLength ist die Anzahl Bytes, welche gesendet werden sollen
*	und cArray ist der Pointer auf das erste Byte.
**/
void send_Array(unsigned int iLength, unsigned char* cArray){
	for(int i = 0; i < iLength; i++)
		send_Byte(*(cArray + i));
}

/**
*	Function:	receive_Array
*	Parameter:	unsigned int iLength
				unsigned char* cBuffer
*	Return:		void
*
*	Description:
*	Empfängt mehrere Bytes über die UART Schnittstelle. 
*	iLength ist die Anzahl Bytes, welche empfangen werden sollen
*	und cBuffer ist der Pointer auf das erste Byte des reservierten Buffers.
**/
void receive_Array(unsigned int iLength, unsigned char* cBuffer){
	for(int i = 0; i < iLength; i++)
		*(cBuffer + i) = receive_Byte();
}