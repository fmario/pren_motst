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
	m4_state.speed = def_speed;
	m4_state.acc = def_acc;
	m4_state.dec = def_dec;
	m4_state.motorState = 0;

	m4_state.tarPos = 0;
	m4_state.softStop = 0;
	m4_state.stepCount = 0;

	/* TIMER 3 Init */
	T3RD16 = 1;	// Enables 16bit r/w operation
	T3CCP2 = 1; // Timer3 ist ccp clock source for CCP modules
	T3CKPS1 = 1;
	T3CKPS0 = 1;// Prescaler fosc/(4*8) -> 625kHz
	TMR3CS = 0; // Internal Clock
	TMR3ON = 0; // Stops Timer3

	/* CCP1 Init */
	CCP1CONbits.CCP1M = 2;	// Compare Mode, Toggle Pin on match
	CCP1IE = 1;	// Interrupt enable
}

void A3977_goTo_Dir(uint8 dir, uint24 abs_pos){
	uint24 n1, n2;
	uint24 constSpd, decPhase;
	uint24 divPos;
	uint16 deltaCCPR;

	if (abs_pos == m4_state.absPos)
		return;

	m4_state.tarPos = abs_pos & 0x3FFFFF;
	m4_state.dir = (dir > 0) ? 1 : 0;
	M4_DIR = m4_state.dir;
	m4_state.stepCount = 0;

	if(dir){
		divPos = (abs_pos - m4_state.absPos) & 0x3FFFFF;
	}else{
		divPos = (m4_state.absPos - abs_pos) & 0x3FFFFF;
	}

	// Anzahl Schritte wenn nur beschleunigt und gebremst wird
	n1 = divPos * m4_state.dec/(m4_state.acc + m4_state.dec);

	// Anzahl Schritte bis die Geschwindigkeit erreicht ist
	constSpd = (m4_state.speed^2 - START_SPEED^2)/(m4_state.acc ) << 3;


	/*if(constSpd > n1){ // Gesamte Strecke reicht nicht bis zur Geschwindigkeit
		m4_state.constStp = n1;
		m4_state.decStp = n1;
	}else*/{
		//m4_state.constStp = constSpd;

		// Anzahl Schritte bis zum Stillstand
		decPhase = (m4_state.speed^2 - START_SPEED^2)/(m4_state.dec ) << 3;
		m4_state.decStp = divPos - decPhase;

		deltaCCPR = ((625000 / START_SPEED) >> (1 + STP_MOD + 6)) -  ((625000 / m4_state.speed) >> (1 + STP_MOD + 6));

		m4_state.CCPR1dec = deltaCCPR / constSpd;
		m4_state.CCPR1inc = deltaCCPR / decPhase;
	}


	m4_state.motorState = 1;

	TMR3 = 0;
	m4_state.maxCCPR = (625000/START_SPEED) >> (6 + 1 + STP_MOD);
	m4_state.minCCPR = (625000/m4_state.speed) >> (6 + 1 + STP_MOD);
	CCPR1 = m4_state.maxCCPR;
	TMR3ON = 1;
}

void A3977_resetPos(void){
	m4_state.absPos = 0;
}

void A3977_stopMove(uint8 isHardStop){
	if(isHardStop > 0){
		TMR3ON = 0;
		m4_state.motorState = 0;
		m4_state.softStop = 0;
		m4_state.stepCount = 0;	
	}else
		m4_state.softStop = 1;
}

uint24 A3977_getAbsPos(void){
	return m4_state.absPos;
}

uint8 A3977_isMoving(void){
	return (m4_state.motorState == 0) ? 0 : 1;
}