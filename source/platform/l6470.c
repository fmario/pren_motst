/**
*	File:	L6470.c
*	Date:	16.05.2014
*	Author:	Fallegger Michi
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

#include "L6470.h"
#include "..\protocol.h"
#include "team.h"
#include "spi.h"

/**------------------ VARIABLES ------------------**/
uint8 cCommand[4];
uint8 cResponse[3];
uint8 bit_len[NUMBER_PARAM + 1] = { 0,  //
								22,	// ABS_POS
								9,	// EL_POS
								22,	// MARK
								20, // SPEED
								12, // ACC
								12, // DEC
								10, // MAX_SPEED
								13, // MIN_SPEED
								8,	// KVAL_HOLD
								8,	// KVAL_RUN
								8,	// KVAL_ACC
								8,	// KVAL_DEC
								14,	// INT_SPEED
								8,	// ST_SLP
								8,	// FN_SLP_ACC
								8,	// FN_SLP_DEC
								4,	// K_THERM
								5,	// ADC_OUT
								4,	// OCD_TH
								7,	// TALL_TH
								10,	// FS_SPD
								8,	// STEP_MODE
								8,	// ALARM_EN
								16,	// CONFIG
								16};// STATUS

/**------------------ FUNCTIONS ------------------**/

/**
*	Function:	L6470_setParam
*	Parameter:	(uint8) address, 
				(uint8) param 
				(uint24) value
*
*	Description:
*	Setzt die Parameter
**/
void L6470_setParam(uint8 address, uint8 param, uint24 value){
	uint8 cmd = SET_PARAM;
	uint8 bytes = L6470_parseParamSend(param, &value); 
	
	cCommand[0] = cmd | param;
	*(uint24*)&cCommand[1] = value;
	
	spi_send_Command(address, (bytes + 1), cCommand, 0, 0);
}

/**
*	Function:	L6470_getParam
*	Parameter:	(uint8) address 
				(uint8) param
*	Return		(uint24)
*	Description:
*	Gibt die Parameter zurück
**/
uint24	L6470_getParam(uint8 address, uint8 param){
	uint8 cmd = GET_PARAM;
	cCommand[0] = cmd | param;
	
	spi_send_Command(address, 1, cCommand, 3, &cResponse);	
	L6470_parseParamReceived(param, (uint24*)&cResponse);

	return *(uint24*)cResponse;
}

/**
*	Function:	L6470_run
*	Parameter:	(uint8) address 
				(uint8) dir
				(uint24) spd
*
*	Description:
*	Dreht Motor mit vorgegebener Richtung und Speed
**/
void L6470_run(uint8 address, uint8 dir, uint24 spd){
	uint8 cmd = RUN;
	cCommand[0] = cmd | dir;
	*(uint24*)&cCommand[1] = spd;
	
	spi_send_Command(address, 4, cCommand, 0, 0);
}

/**
*	Function:	L6470_stepClock
*	Parameter:	(uint8) address
				(uint8) dir
*
*	Description:
*	Dreht den Motor in gewünschte Richtung
**/
void L6470_stepClock(uint8 address, uint8 dir){
	uint8 cmd = STEP_CLOCK;
	cCommand[0] = cmd | dir;
	
	spi_send_Command(address, 1, cCommand, 0, 0);
}

/**
*	Function:	L6470_move
*	Parameter:	(uint8) address
				(uint8) dir
				(uint24) n_step
*
*	Description:
*	Dreht den Motor in gewünschte Richtung, Anzahl Steps
**/
void L6470_move(uint8 address, uint8 dir, uint24 n_step){
	uint8 cmd = MOVE;
	cCommand[0] = cmd | dir;
	*(uint24*)&cCommand[1] = n_step;
	
	spi_send_Command(address, 4, cCommand, 0, 0);
}

/**
*	Function:	L6470_goTo
*	Parameter:	(uint8) address
				(uint24) abs_pos
*
*	Description:
*	Dreht den Motor zur absoluten Position
**/
void L6470_goTo(uint8 address, uint24 abs_pos){
	uint8 cmd = GOTO;
	cCommand[0] = cmd;
	*(uint24*)&cCommand[1] = abs_pos;
	
	spi_send_Command(address, 4, cCommand, 0, 0);
}

/**
*	Function:	L6470_goTo_Dir
*	Parameter:	(uint8) address
				(uint8) dir 
				(uint24) abs_pos
*
*	Description:
*	Dreht den Motor in gewünschte Richtung, absolute Position
**/
void L6470_goTo_Dir(uint8 address, uint8 dir, uint24 abs_pos){
	uint8 cmd = GOTO_DIR;
	cCommand[0] = cmd | dir;
	*(uint24*)&cCommand[1] = abs_pos;
	
	spi_send_Command(address, 4, cCommand, 0, 0);
}

/**
*	Function:	L6470_goUntil
*	Parameter:	(uint8) address
				(uint8) act 
				(uint8) dir
				(uint24) spd
*
*	Description:
*	Dreht den Motor mit gewählter Beschleunigung, Abbremsung und Speed
**/
void L6470_goUntil(uint8 address, uint8 act, uint8 dir, uint24 spd){
	uint8 cmd = GO_UNTIL;
	cCommand[0] = cmd | dir | (act<<3);
	*(uint24*)&cCommand[1] = spd;
	
	spi_send_Command(address, 4, cCommand, 0, 0);
}

/**
*	Function:	L6470_releaseSW
*	Parameter:	(uint8) address 
				(uint8) act
				(uint8) dir
*
*	Description:
*	Resetet das ABS-Pos Register oder wird ins Mark Register kopiert
**/
void L6470_releaseSW(uint8 address, uint8 act, uint8 dir){
	uint8 cmd = RELEASE_SW;
	cCommand[0] = cmd | dir | (act<<3);
		
	spi_send_Command(address, 1, cCommand, 0, 0);
}

/**
*	Function:	L6470_goHome
*	Parameter:	(uint8) address
*
*	Description:
*	Geht zurück an die 0 Position
**/
void L6470_goHome(uint8 address){
	uint8 cmd = GO_HOME;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, 0);
}

/**
*	Function:	L6470_goMark
*	Parameter:	(uint8) address
*
*	Description:
*	Bewegt den Motor zur Mark Position mit dem kürzesten Weg
**/
void L6470_goMark(uint8 address){
	uint8 cmd = GO_MARK;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, 0);
}

/**
*	Function:	L6470_resetPos
*	Parameter:	(uint8) address
*
*	Description:
*	Setzt die ABS_Pos auf 0
**/
void L6470_resetPos(uint8 address){
	uint8 cmd = RESET_POS;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, 0);
}

/**
*	Function:	L6470_resetDevice
*	Parameter:	(uint8) address
*
*	Description:
*	Setzt das Device auf die Power-Up Kondition
**/
void L6470_resetDevice(uint8 address){
	uint8 cmd = RESET_DEVICE;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, 0);
}

/**
*	Function:	L6470_softStop
*	Parameter:	(uint8) address
*
*	Description:
*	Bremst den Motor mit der Abremsungsbeschleunigung
**/
void L6470_softStop(uint8 address){
	uint8 cmd = SOFT_STOP;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, 0);
}

/**
*	Function:	L6470_hardStop
*	Parameter:	(uint8) address
*
*	Description:
*	Bremst den Motor abrupt
**/
void L6470_hardStop(uint8 address){
	uint8 cmd = HARD_STOP;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, 0);
}

/**
*	Function:	L6470_softHiZ
*	Parameter:	(uint8) address
*
*	Description:
*	Setzt die Power Bridges disables (hohe Impedanz)
**/
void L6470_softHiZ(uint8 address){
	uint8 cmd = SOFT_HIZ;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, 0);
}

/**
*	Function:	L6470_hardHiZ
*	Parameter:	(uint8) address
*
*	Description:
*	Setzt die Power Bridges abrupt auf disable (hohe Impedanz)
**/
void L6470_hardHiZ(uint8 address){
	uint8 cmd = HARD_HIZ;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, 0);
}

/**
*	Function:	L6470_getStatus
*	Parameter:	(uint8) address
*	Return:		uint16
*
*	Description:
*	Gibt den Status zurück
**/
uint16 L6470_getStatus(uint8 address){
	uint8 cmd = GET_STATUS;
	cCommand[0] = cmd;
	
	spi_send_Command(address, 1, cCommand, 2, &cResponse);
	
	return swap16(*(uint16*)cResponse);
}

/**
*	Function:	L6470_isMoving
*	Parameter:	(uint8) address
*	Return:		uint8
*
*	Description:
*	Gibt zurück, ob der Motor noch fährt.
**/
uint8 L6470_isMoving(uint8 address){
	L6470_status state = L6470_ParseStatus(L6470_getStatus(address));

	return (!state.BUSY || state.MOT_STATUS);
}

uint8 L6470_checkStartConditions(uint8 address){
	if (L6470_isMoving(address))
		return 0;

	if (!PORTB_IO.nFlag & (1 << address))
		L6470_getStatus(address);

	return 1;
}

/**
*	Function:	L6470_parseParamSend
*	Parameter:	(uint8) param
*				(uint24*) value
*	Return:		uint8
*
*	Description:
*	Verarbeitet einen Wert so, dass dieser über SPI an
*	den L6470 gesendet werden kann. Da sich die Werte
*	in den Bit und Byte längen unterscheiden.
*	Die Bytelänge des Parameters wird zurückgegeben.
**/
uint8 L6470_parseParamSend(uint8 param, uint24* value){
	uint24 mask = 0xFFFFFF;
	uint8 cBit_len = bit_len[param];
	uint8 cByte_len = cBit_len / 8;

	if (cBit_len % 8 > 0)
		cByte_len++;

	mask = mask >> (24 - cBit_len);
	if (*value > mask)
		*value = mask;

	*value = swap24((*value) << ((3 - cByte_len) * 8));

	return cByte_len;
}

/**
*	Function:	L6470_parseParamReceived
*	Parameter:	(uint8) param
*				(uint24*) value
*	Return:		uint8
*
*	Description:
*	Verarbeitet den Empfangenen wert so, dass dieser
*	richtig gelesen werden kann.
*	Die Bytelänge des Parameters wird zurückgegeben.
**/
uint8 L6470_parseParamReceived(uint8 param, uint24* value){
	uint8 cBit_len = bit_len[param];
	uint8 cByte_len = cBit_len / 8;

	if (cBit_len % 8 > 0)
		cByte_len++;

	*value = (*value) >> ((3 - cByte_len) * 8);

	return cByte_len;
}

/**
*	Function:	L6470_ParseStatus
*	Parameter:	(uint8) u16_state
*	Return:		L6470_status
*
*	Description:
*	Parst den uint16 Wert in die Status Struktur.
**/
L6470_status L6470_ParseStatus(uint16 u16_state){
	L6470_status state;

	state.HiZ = u16_state & 1;
	state.BUSY = (u16_state & 2) >> 1;
	state.SW_F = (u16_state & 4) >> 2;
	state.SW_EVN = (u16_state & 8) >> 3;
	state.DIR = (u16_state & 16) >> 4;
	state.MOT_STATUS = (u16_state & 96) >> 5;
	state.NOTPERF_CMD = (u16_state & 128) >> 7;
	state.WRONG_CMD = (u16_state & 256) >> 8;
	state.UVLO = (u16_state & 512) >> 9;
	state.TH_WRN = (u16_state & 1024) >> 10;
	state.TH_SD = (u16_state & 2048) >> 11;
	state.OCD = (u16_state & 4096) >> 12;
	state.STEP_LOSS_A = (u16_state & 8192) >> 13;
	state.STEP_LOSS_B = (u16_state & 16384) >> 14;
	state.SCK_MOD = (u16_state & 32768) >> 15;

	return state;
}

/**
*	Function:	L6470_speedCalc
*	Parameter:	(uint8) stepsPerSec
*	Return:		uint24
*
*	Description:
*	Rechnet von Step/s in Step/tick um. Die Formel für
*	die Umrechnung ist im Datenplatt gegeben mit:
*	([(steps/s)*(tick)]/(2^-28))
*	Ein Tick ist angegeben mit 250ns und die Registergrösse
*	ist 20-bit
**/
uint24 L6470_speedCalc(uint8 stepsPerSec){
	uint24 temp = (uint24)stepsPerSec << 12; // faktor = (2^20 - 1)/(2^8 - 1)
	temp /= SPEED_DIVISOR;
	
	return (temp > 0x0FFFFF) ? 0x0FFFFF : temp;
}

/**
*	Function:	L6470_speedCalc
*	Parameter:	(uint8) stepsPerSec
*	Return:		uint24
*
*	Description:
*	Rechnet von Step/s in Step/tick um für das Register
*	MAX_SPEED. Die Formel für die Umrechnung ist 
*	im Datenblatt gegeben mit:
*	([(steps/s)*(tick)]/(2^-18))
*	Ein Tick ist angegeben mit 250ns und die Registergrösse
*	ist 10-bit
**/
uint24 L6470_maxSpeedCalc(uint8 stepsPerSec){
	uint24 temp = (uint24)stepsPerSec << 2; // faktor = (2^10 - 1)/(2^8 - 1)
	temp /= SPEED_DIVISOR;

	return (temp > 0x0003FF) ? 0x0003FF : temp;
}

/**
*	Function:	L6470_accCalc
*	Parameter:	(uint8) stepsPerSecSqrt
*	Return:		uint24
*
*	Description:
*	Rechnet von Step/s^2 in Step/tick^2 um.
*	Die Formel für die Umrechnung ist im Datenblatt
*	gegeben mit:
*	([(steps/s^2)*(tick^2)]/(2^-40))
*	Ein Tick ist angegeben mit 250ns und die Registergrösse
*	ist 12-bit
**/
uint24 L6470_accCalc(uint8 stepsPerSecSqrt){
	uint24 temp = (uint24)stepsPerSecSqrt << 4; // faktor = (2^12 - 1)/(2^8 - 1)
	temp /= ACC_DIVISOR;

	return (temp > 0x000FFF) ? 0x000FFF : temp;

}