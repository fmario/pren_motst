/**
*	File:	port.c
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

#include "port.h"
#include "team.h"

/**
*	Function:	init_spi
*	Parameter:	void
*
*	Description:
*	Initialisiert die SPI-Schnittstelle
**/
void init_port(void){
	TRISC1 = OUTPUT;
	TRISC2 = OUTPUT;
}