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

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/**------------------ CONFIGURATION -----------------**/
#pragma config OSC = HS		
#pragma config MCLRE = OFF
#pragma config DEBUG = OFF
#pragma config WDT = OFF


/**------------------- CONSTANTS -------------------**/
//	Länge eines Befehls in Bytes
#define COMMAND_LENGTH 9

//	Länge einer Antwort in Bytes 
#define ANSWER_LENGTH 4

//	Anzahl Befehle
#define NUMBER_COMMAND 15

//  Input/Output Wert für TRIS-Register
#define INPUT 1
#define OUTPUT 0

/**-------------------- TYPEDEF -------------------**/
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


/**------------------- VARIABLES -------------------**/
extern uint8 _received_Data[COMMAND_LENGTH]; 
extern uint8 _payload[COMMAND_LENGTH - 1];


#endif  // !DEFINITIONS_H