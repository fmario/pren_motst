/**
*	File:	definitions.h
*	Date:	04.04.2014
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


/**------------------ DEFINES ------------------**/
#ifndef MAIN_H
#define MAIN_H

typedef unsigned char uint8;
#if sizeof(unsigned char) != 1
	#error Länge von uint8 inkorrekt
#endif

typedef unsigned short int uint16;
#if sizeof(unsigned short int) != 2
	#error Länge von uint16 inkorrekt
#endif

typedef unsigned short long int uint24;
#if sizeof(unsigned short long int) != 3
	#error Länge von uint24 inkorrekt
#endif

#endif  // !MAIN_H