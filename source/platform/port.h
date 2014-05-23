/**
*	File:	port.h
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
void init_port(void);
uint8 port_configPin(uint8 pinNr, uint8 isOutput);
uint8 port_setPin(uint8 pinNr, uint8 isHigh);
uint8 port_getPin(uint8 pinNr);

/**------------------ DEFINES ------------------**/
#ifndef PORT_H
#define PORT_H

#define TRIS_OFF 0x12
#define LAT_OFF 0x09

#endif  // !PORT_H