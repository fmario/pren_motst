/**
*	File:	protocol.c
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

#include "platform/definitions.h"

#include "protocol.h"

/**
*	Function:	checkCommand
*	Parameter:	void
*	Return:		uint16
*
*	Description:
*	Überprüft, ob ein gültiger Befehl vorliegt.
**/
uint16 parseCommand(void){
	return 0;
}





/**
*	Function:	swap16
*	Parameter:	(uint16) val
*	Return:		uint16
*
*	Description:
*	Ändert den Endian-Typ einer 16bit Zahl
**/
uint16 swap16(uint16 val){
	return (val << 8) | (val >> 8 );
}

/**
*	Function:	swap24
*	Parameter:	(uint24) val
*	Return:		uint24
*
*	Description:
*	Ändert den Endian-Typ einer 24bit Zahl
**/
uint24 swap24(uint24 val){
	return (val << 16) | (val >> 16) | (val & 0x0F0);
}