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
void spi_send_Command(uint8 iAddress, uint8 iCmdLength, uint8* cCmdArray, uint8 iRspLength, uint8* cRspBuffer);
void set_CS(uint8 iAddress);
void reset_CS(void);

/**------------------ DEFINES ------------------**/
#ifndef SPI_H
#define SPI_H

#define NUMBER_DEVICES 3
#define SPI_NOP 0x00

#endif  // !SPI_H