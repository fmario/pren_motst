/**
*	File:	team27.c
*	Date:	23.05.2014
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

#ifdef T27

#include <htc.h>

#include "definitions.h"

#include "team27.h"
#include "L6470.h"
#include "A3977.h"

volatile unsigned char* gpio_addr[GPIO] = {	&PRT_A,
											&PRT_A,
											&PRT_A,
											&PRT_A,
											&PRT_A,
											&PRT_A,
											&PRT_D,
											&PRT_D,
											&PRT_D,
											&PRT_D,
											&PRT_D,
											&PRT_D,
											&PRT_D };


volatile unsigned char gpio_offs[GPIO] = {	0,
											1,
											2,
											3,
											4,
											5,
											0,
											1,
											7,
											6,
											5,
											4,
											3 };
/**
*	Function:	init_motors
*	Parameter:	void
*
*	Description:
*	Initialisiert alle Motoren mit Idealen werten.
**/
void init_motors(void){
	uint8 cAddress;


	/**************************
	**
	** Motor 0 (Lauf seitlich)
	**
	***************************/
	cAddress = 0;
	L6470_resetDevice(cAddress);
	//L6470_setParam(cAddress, ACC, 0x??);
	//L6470_setParam(cAddress, DEC, 0x??);
	//L6470_setParam(cAddress, MAX_SPEED, 0x??);
	//L6470_setParam(cAddress, FS_SPD, 0x??);
	L6470_setParam(cAddress, KVAL_HOLD, 0x19);	//0.098 x Vs
	L6470_setParam(cAddress, KVAL_RUN, 0x7F);	//0.996 x Vs
	L6470_setParam(cAddress, KVAL_ACC, 0x7F);	//0.996 x Vs
	L6470_setParam(cAddress, KVAL_DEC, 0x7F);	//0.996 x Vs
	//L6470_setParam(cAddress, OCD_TH, OCD_TH_1500mA);
	//L6470_setParam(cAddress, STALL_TH,  0x??);
	L6470_setParam(cAddress, STEP_MODE, 0x07);
	L6470_hardStop(cAddress);


	/**************************
	**
	** Motor 1 (Lauf höhe)
	**
	***************************/
	cAddress++;
	L6470_resetDevice(cAddress);
	//L6470_setParam(cAddress, ACC, 0x??);
	//L6470_setParam(cAddress, DEC, 0x??);
	//L6470_setParam(cAddress, MAX_SPEED, 0x??);
	//L6470_setParam(cAddress, FS_SPD, 0x??);
	L6470_setParam(cAddress, KVAL_HOLD, 0x19);	//0.098 x Vs
	L6470_setParam(cAddress, KVAL_RUN, 0x7F);	//0.496 x Vs
	L6470_setParam(cAddress, KVAL_ACC, 0x7F);	//0.496 x Vs
	L6470_setParam(cAddress, KVAL_DEC, 0x7F);	//0.496 x Vs
	//L6470_setParam(cAddress, OCD_TH, OCD_TH_750mA);
	//L6470_setParam(cAddress, STALL_TH, 0x??);
	L6470_setParam(cAddress, STEP_MODE, 0x07);
	L6470_hardStop(cAddress);


	/**************************
	**
	** Motor 2 (Spannvorrichtung)
	**
	***************************/
	cAddress++;
	L6470_resetDevice(cAddress);	
	//L6470_setParam(cAddress, ACC, 0x??);
	//L6470_setParam(cAddress, DEC, 0x??);
	//L6470_setParam(cAddress, MAX_SPEED, 0x??);
	//L6470_setParam(cAddress, FS_SPD, 0x??);
	L6470_setParam(cAddress, KVAL_HOLD, 0x19);	//0.098 x Vs
	L6470_setParam(cAddress, KVAL_RUN, 0xEF);	//0.996 x Vs
	L6470_setParam(cAddress, KVAL_ACC, 0x4F);	//0.996 x Vs
	L6470_setParam(cAddress, KVAL_DEC, 0x4F);	//0.996 x Vs
	//L6470_setParam(cAddress, OCD_TH, OCD_TH_1875mA);
	//L6470_setParam(cAddress, STALL_TH,  0x??);
	L6470_setParam(cAddress, STEP_MODE, 0x07);
	L6470_hardStop(cAddress);

	/**************************
	**
	** Motor 3 (Turm drehen)
	**
	***************************/
	TRISB0 = OUTPUT;	//Direction
	TRISC2 = OUTPUT;	//Step Clock
	TRISD2 = OUTPUT;	//Holding
	M4_Hold = 1;		//IsHolding
	init_a3977(128,9,9);

	/**************************
	**
	** DC Motor (Trichter
	**
	***************************/
	TRISC0 = OUTPUT;	//Reverse
	TRISC1 = OUTPUT;	//Forward
	DC_FW = 1;
	DC_RW = 1;			//HiZ State 
}

#endif
