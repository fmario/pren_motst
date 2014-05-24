/**
*	File:	A3977.h
*	Date:	24.05.2014
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
#ifndef A3977_H
#define A3977_H

#define STP_MOD 2 // 1:2^x Quarter Step

typedef struct __as{
	uint24 absPos : 22;
	uint24 dest : 22;
	uint16 speed : 8;
	uint16 acc : 8;
	uint16 dec : 8;
	uint8 dir : 1;
	uint8 busy : 1;
	uint8 softStop : 1;
	uint8 decStop : 1;
} a3977_state;

extern a3977_state m4_state;

#endif  // !A3977_H