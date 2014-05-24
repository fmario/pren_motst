/**
*	File:	A3977.c
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
#include <htc.h>

#include "definitions.h"

#include "A3977.h"
#include "..\protocol.h"
#include "team.h"

/**------------------ VARIABLES ------------------**/
a3977_state m4_state;


void init_a3977(uint8 def_speed, uint8 def_acc, uint8 def_dec){
	m4_state.absPos = 0;
	m4_state.speed = A3977_calcSpeed(def_speed);
	m4_state.acc = def_acc;
	m4_state.dec = def_dec;
	m4_state.busy = 0;

	m4_state.dest = 0;
	m4_state.softStop = 0;

	/* TIMER 3 Init */
	RD16 = 1;	// Enables 16bit r/w operation
	T3CCP2 = 1; // Timer3 ist ccp clock source for CCP modules
	T3CKPS1 = 1;
	T3CKPS0 = 1;// Prescaler fosc/(4*8) -> 625kHz
	TMR3CS = 0; // Internal Clock
	TMR3ON = 0; // Stops Timer3

	/* CCP1 Init */
	CCP1M = 2;	// Compare Mode, Toggle Pin on match
	CCP1IE = 1;	// Interrupt enable
}

void A3977_goTo_Dir(uint8 dir, uint24 abs_pos, uint8 speed){
	if (abs_pos == m4_state.absPos)
		return;

	m4_state.dest = abs_pos & 0x3FFFFF;
	m4_state.dir = (dir > 0) ? 1 : 0;
	m4_state.busy = 1;

	TMR3 = 0;
	CCPR1 = 0xFFFF;
	TMR3ON = 1;
}

void A3977_resetPos(void){
	m4_state.absPos = 0;
}

uint8 A3977_isMoving(void){
	return m4_state.busy;
}

uint16 A3977_calcSpeed(uint8 speed){
	return speed << 6;
}