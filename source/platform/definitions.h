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

//	Länge eines Befehle in Bytes
#define COMMAND_LENGTH 10

//	Länge einer Antwort in Bytes 
#define ANSWER_LENGTH 11

//	Anzahl Befehle
#define NUMBER_COMMAND 14


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

typedef struct __f
{
	uint8	fRC:1;		//Command Receive complete
	uint8	fRT:1;		//UART Receive Timeout
} flags;


/**------------------- VARIABLES -------------------**/
extern uint8 _received_Data[COMMAND_LENGTH]; 
extern uint8 _payload[COMMAND_LENGTH - 1];
extern flags _Flags;


#endif  // !MAIN_H