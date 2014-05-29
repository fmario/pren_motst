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

#include "team.h"
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
	TRISC3 = 0;			// Clear for SCK
	TRISC4 = 1;			// Set for SDI
	TRISC5 = 0;			// Clear for SDO

	SMP = 0;			// Input sampled at middle of data output time
	CKE = 0;			// Transmit occurs on idle to active clock state

	CKP = 1;			// Idle state for clock is high level
	SSPM0 = 1;			// SPI Master Mode, clock = Fosc/8
	SSPM1 = 0;
	SSPM2 = 0;
	SSPM3 = 0;
	
	SSPIE = 0;			// SPI Interrupt disabled
	SSPEN = 1;			// Enables SPI
}

/**
*	Function:	spi_send_Byte
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
		SSPBUF = cByte;
	}while(WCOL);	//repeat if write collision
}

/**
*	Function:	spi_receive_Byte
*	Parameter:	void
*	Return:		uint8
*
*	Description:
*	Empfängt ein Byte über die UART Schnittstelle, 
*	sobald dieses vollständig Empfangen ist.
**/
uint8 spi_receive_Byte(void){
	while(!BF);
	return SSPBUF;
}

/**
*	Function:	spi_send_Command
*	Parameter:	(uint8) iAddress
				(uint8) iCmdLength
				(uint8*) cCmdArray
				(uint8) iRspLength
				(uint8*) cRspBuffer
*	Return:		void
*
*	Description:
*	Sendet einen Befehl über SPI an den gewählten (iAddress)
*	Device. Falls der Befehl eine Antwort zu Folge hat, wird
*	diese in cRspBuffer gespeichert.
**/
void spi_send_Command(uint8 iAddress, uint8 iCmdLength, uint8* cCmdArray, uint8 iRspLength, uint8* cRspBuffer){

	for(int i = 0; i < iCmdLength; i++){
		set_CS(iAddress);
		spi_send_Byte(*(cCmdArray + i));
		spi_receive_Byte();
		reset_CS();
	}

	for(int i = 0; i < iRspLength; i++){
		set_CS(iAddress);
		spi_send_Byte(SPI_NOP);
		*(cRspBuffer + i) = spi_receive_Byte();
		reset_CS();
	}
}

/**
*	Function:	set_CS
*	Parameter:	(uint8) iAddress
*	Return:		void
*
*	Description:
*	Setzt die ChipSelect-Leitung des Entprechenden
*	Devices.
**/
void set_CS(uint8 iAddress){
	PORTE_IO.nCS = ~(uint8)(1 << iAddress);
	_delay(0x02);	//wait 400ns (t_setCS > 350ns)
}

/**
*	Function:	reset_CS
*	Parameter:	(void)
*	Return:		void
*
*	Description:
*	Deselecktiert alles Devices und wartet die minimale
*	entsprechende Zeit.
**/
void reset_CS(void){
	PORTE_IO.nCS = 7;
	_delay(0x05);	//wait 1us (t_disCS > 800ns)
}