/**
*	File:	spi.h
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
void init_spi(void);
void spi_send_Byte(uint8 cByte);
uint8 spi_receive_Byte(void);
void spi_send_Array(uint8 iLength, uint8* cArray);
void spi_receive_Array(uint8 iLength, uint8* cBuffer);

/**------------------ DEFINES ------------------**/
#ifndef SPI_H
#define SPI_H

#endif  // !SPI_H