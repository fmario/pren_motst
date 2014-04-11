/**
*	File:	spi.c
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

#include "definitions.h"

#include "spi.h"

/**
*	Function:	init_spi
*	Parameter:	void
*
*	Description:
*	Initialisiert die SPI-Schnittstelle
**/
void init_spi(void){
	TRISC5 = 0;			// Clear for SDO
	TRISC3 = 0;			// Clear for SCK

	SMP = 0;			// Input sampled at middle of data output time
	CKE = 0;			// Transmit occurs on idle to active clock state

	CKP = 1;			// Idle state for clock is high level
	SSPM0 = 0;			// SPI Master Mode, clock = Fosc/4
	SSPM1 = 0;
	SSPM2 = 0;
	SSPM3 = 0;
	
	SSPIE = 1;			// SPI Interrupt enabled
	SSPEN = 1;			// Enables SPI
}

/**
*	Function:	send_Byte
*	Parameter:	(uint8) cByte
*	Return:		void
*
*	Description:
*	Sendet ein Byte über die SPI Schnittstelle, 
*	sobald der Sendebuffer frei ist.
**/
void spi_send_Byte(uint8 cByte){
	do{
		WCOL = 0;
		while(BF);
		SSPBUF = cByte;
	}while(WCOL);
}

/**
*	Function:	receive_Byte
*	Parameter:	void
*	Return:		uint8
*
*	Description:
*	Empfängt ein Byte über die UART Schnittstelle, 
*	sobald dieses vollständig Empfangen ist.
**/
uint8 spi_receive_Byte(void){
	while(!SSPIF);
	return SSPBUF;
}

/**
*	Function:	send_Array
*	Parameter:	(uint8) iLength
				(uint8*) cArray
*	Return:		void
*
*	Description:
*	Sendet mehrere Bytes über die UART Schnittstelle. 
*	iLength ist die Anzahl Bytes, welche gesendet werden sollen
*	und cArray ist der Pointer auf das erste Byte.
**/
void spi_send_Array(uint8 iLength, uint8* cArray){
	for(int i = 0; i < iLength; i++)
		send_Byte(*(cArray + i));
}

/**
*	Function:	receive_Array
*	Parameter:	(uint8) iLength
				(uint8*) cBuffer
*	Return:		void
*
*	Description:
*	Empfängt mehrere Bytes über die UART Schnittstelle. 
*	iLength ist die Anzahl Bytes, welche empfangen werden sollen
*	und cBuffer ist der Pointer auf das erste Byte des reservierten Buffers.
**/
void spi_receive_Array(uint8 iLength, uint8* cBuffer){
	for(int i = 0; i < iLength; i++)
		*(cBuffer + i) = receive_Byte();
}