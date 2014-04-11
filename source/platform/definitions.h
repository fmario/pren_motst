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

#ifndef MAIN_H
#define MAIN_H

/**------------------- CONSTANTS -------------------**/
#define COMMAND_LENGTH 10
#define ANSWER_LENGTH 11
#define NUMBER_COMMAND 13

/**------------------- TYPEDEF -------------------**/
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

typedef struct __cs
{
	uint8	cByte[COMMAND_LENGTH];
} command_struct;

typedef struct __f
{
	uint8	fRC:1;	//Command Receive complete
} flags;


/**------------------- VARIABLES -------------------**/
extern command_struct _received_Data; 
extern uint8 _cReceivedCounter;
extern flags _Flags;


#endif  // !MAIN_H