/**
*	File:	team23.h
*	Date:	09.05.2014
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


/**------------------ DEFINES ------------------**/
#ifndef TEAM23_H
#define TEAM23_H
// Register: PORTA
extern volatile unsigned char           PRT_A               @ 0xF80;

extern volatile union {
    struct {
        unsigned IO0					:1;
        unsigned IO1					:1;
        unsigned IO2					:1;
        unsigned IO3					:1;
        unsigned IO4					:1;
        unsigned IO5					:1;
        unsigned						:1;
        unsigned						:1;
    };
} PORTA_IO @ 0xF80;


// Register: PORTB
extern volatile unsigned char           PRT_B               @ 0xF81;

extern volatile union {
    struct {
        unsigned Valve					:1;
        unsigned						:1;
        unsigned nBusy3					:1;
        unsigned nBusy2					:1;
        unsigned nBusy1					:1;
        unsigned nFlag1					:1;
        unsigned nFlag2					:1;
        unsigned nFlag3					:1;
    };
    struct {
        unsigned						:2;
		unsigned nBusy					:3;
		unsigned nFlag					:3;
    };
} PORTB_IO @ 0xF81;

// Register: PORTC
extern volatile unsigned char           PRT_C               @ 0xF82;

extern volatile union {
    struct {
        unsigned DC_RW					:1;
        unsigned DC_FW					:1;
    };
} PORTC_IO @ 0xF82;

// Register: PORTD
extern volatile unsigned char           PRT_D               @ 0xF83;

extern volatile union {
    struct {
        unsigned IO6					:1;
        unsigned IO7					:1;
        unsigned IO8					:1;
        unsigned IO9					:1;
        unsigned IO10					:1;
        unsigned IO11					:1;
        unsigned IO12					:1;
        unsigned IO13					:1;
    };
} PORTD_IO @ 0xF83;

// Register: PORTE
extern volatile unsigned char           PRT_E               @ 0xF84;

extern volatile union {
    struct {
        unsigned nCS1					:1;
		unsigned nCS2					:1;
		unsigned nCS3					:1;
    };
	struct {
        unsigned nCS					:3;
    };
} PORTE_IO @ 0xF84;


/*
 * Bit Definitions
 */
extern volatile bit                     IO0                 @ (((unsigned) &PRT_A)*8) + 0;
extern volatile bit                     IO1                 @ (((unsigned) &PRT_A)*8) + 1;
extern volatile bit                     IO2                 @ (((unsigned) &PRT_A)*8) + 2;
extern volatile bit                     IO3                 @ (((unsigned) &PRT_A)*8) + 3;
extern volatile bit                     IO4                 @ (((unsigned) &PRT_A)*8) + 4;
extern volatile bit                     IO5                 @ (((unsigned) &PRT_A)*8) + 5;

extern volatile bit                     IO6                 @ (((unsigned) &PRT_D)*8) + 0;
extern volatile bit                     IO7                 @ (((unsigned) &PRT_D)*8) + 1;
extern volatile bit                     IO8                 @ (((unsigned) &PRT_D)*8) + 2;
extern volatile bit                     IO9                 @ (((unsigned) &PRT_D)*8) + 3;
extern volatile bit                     IO10                @ (((unsigned) &PRT_D)*8) + 4;
extern volatile bit                     IO11                @ (((unsigned) &PRT_D)*8) + 5;
extern volatile bit                     IO12                @ (((unsigned) &PRT_D)*8) + 6;
extern volatile bit                     IO13                @ (((unsigned) &PRT_D)*8) + 7;

extern volatile bit                     Valve               @ (((unsigned) &PRT_B)*8) + 0;
extern volatile bit                     nBusy3              @ (((unsigned) &PRT_B)*8) + 2;
extern volatile bit                     nBusy2              @ (((unsigned) &PRT_B)*8) + 3;
extern volatile bit                     nBusy1              @ (((unsigned) &PRT_B)*8) + 4;
extern volatile bit                     nFlag1              @ (((unsigned) &PRT_B)*8) + 5;
extern volatile bit                     nFlag2              @ (((unsigned) &PRT_B)*8) + 6;
extern volatile bit                     nFlag3              @ (((unsigned) &PRT_B)*8) + 7;


extern volatile bit                     nCS1                @ (((unsigned) &PRT_E)*8) + 0;
extern volatile bit                     nCS2                @ (((unsigned) &PRT_E)*8) + 1;
extern volatile bit                     nCS3                @ (((unsigned) &PRT_E)*8) + 2;
#endif  // !TEAM23_H