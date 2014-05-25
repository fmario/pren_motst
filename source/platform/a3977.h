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
void init_a3977(uint8 def_speed, uint8 def_acc, uint8 def_dec);
void A3977_goTo_Dir(uint8 dir, uint24 abs_pos);
void A3977_resetPos(void);
void A3977_stopMove(uint8 isHardStop);
uint24 A3977_getAbsPos(void);
uint8 A3977_isMoving(void);

/**------------------ DEFINES ------------------**/
#ifndef A3977_H
#define A3977_H

#define STP_MOD 2 // 1:2^x => Quarter Step
#define START_SPEED 1  // START_SPEED * 2^-16 / 250e-9 = step/s => (61)

typedef struct __as{
	uint24 absPos;		// Actuall position
	uint24 tarPos;		// Targetposition	
	uint24 stepCount;	// Countet Steps
	uint24 decStp;		// Number of steps to start with dec
	unsigned speed : 8;
	unsigned acc : 8;
	uint16 CCPR1dec;	// Change of CCPR1 while ACC
	unsigned dec : 8;
	uint16 CCPR1inc; 	// Change of CCPR1 while DEC
	uint16 maxCCPR;		// CCPR1 value of min Speed
	uint16 minCCPR; 	// CCPR1 value of max Speed
	unsigned dir : 1;
	unsigned motorState : 2; // 0 = ready, 1 = acc, 3 = const. speed, 4 = dec
	unsigned softStop : 1;
} a3977_state;

extern a3977_state m4_state;

#endif  // !A3977_H