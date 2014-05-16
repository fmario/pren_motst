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
#include "spi.h"

uint8 cCommand[4] = {0, 0, 0, 0};
uint8 cResponse[3] = {0, 0, 0};

/**
*	Function:	L6470_setParam
*	Parameter:	(uint8) address, 
				(uint8) param 
				(uint24) value
*
*	Description:
*	Setzt die Parameter
**/
void L6470_setParam(uint8 address, uint8 param, uint24 value)
{
	uint8 cmd = SET_PARAM;
	cCommand[0] = cmd & param;
	*(uint24)&cCommand[1] = value;
	
	spi_send_Command(address, 4, cCommand, 0, NULL);
}

/**
*	Function:	L6470_getParam
*	Parameter:	(uint8) address 
				(uint8) param
*	Return		(uint24)
*	Description:
*	Gibt die Parameter zurück
**/
uint24	L6470_getParam(uint8 address, uint8 param)
{
	uint8 cmd = GET_PARAM;
	cCommand[0] = cmd & param;
	
	spi_send_Command(address, 1, cCommand, 3, cResponse);
	
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
void L6470_run(uint8 address, uint8 dir, uint24 spd)
{
	uint8 cmd = RUN;
	cCommand[0] = cmd & dir;
	*(uint24)&cCommand[1] = spd;
	
	spi_send_Command(address, 4, cCommand, 0, NULL);
}

/**
*	Function:	L6470_stepClock
*	Parameter:	(uint8) address
				(uint8) dir
*
*	Description:
*	Dreht den Motor in gewünschte Richtung
**/
void L6470_stepClock(uint8 address, uint8 dir)
{
	uint8 cmd = STEP_CLOCK;
	cCommand[0] = cmd & dir;
	
	spi_send_Command(address, 1, cCommand, 0, NULL);
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
void L6470_move(uint8 address, uint8 dir, uint24 n_step)
{
	uint8 cmd = MOVE;
	cCommand[0] = cmd & dir;
	*(uint24)&cCommand[1] = n_step;
	
	spi_send_Command(address, 4, cCommand, 0, NULL);
}

/**
*	Function:	L6470_goTo
*	Parameter:	(uint8) address
				(uint24) abs_pos
*
*	Description:
*	Dreht den Motor zur absoluten Position
**/
void L6470_goTo(uint8 address, uint24 abs_pos)
{
	uint8 cmd = GOTO;
	cCommand[0] = cmd;
	*(uint24)&cCommand[1] = abs_pos;
	
	spi_send_Command(address, 4, cCommand, 0, NULL);
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
void L6470_goTo_Dir(uint8 address, uint8 dir, uint24 abs_pos)
{
	uint8 cmd = GOTO_DIR;
	cCommand[0] = cmd & dir;
	*(uint24)&cCommand[1] = abs_pos;
	
	spi_send_Command(address, 4, cCommand, 0, NULL);
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
void L6470_goUntil(uint8 address, uint8 act, uint8 dir, uint24 spd)
{
	uint8 cmd = GO_UNTIL;
	cCommand[0] = cmd & dir & (act<<3);
	*(uint24)&cCommand[1] = spd;
	
	spi_send_Command(address, 4, cCommand, 0, NULL);
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
void L6470_releaseSW(uint8 address, uint8 act, uint8 dir)
{
	uint8 cmd = RELEASE_SW;
	cCommand[0] = cmd & dir & (act<<3);
		
	spi_send_Command(address, 1, cCommand, 0, NULL);
}

/**
*	Function:	L6470_goHome
*	Parameter:	(uint8) address
*
*	Description:
*	Geht zurück an die 0 Position
**/
void L6470_goHome(uint8 address)
{
	uint8 cmd = GO_HOME;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, NULL);
}

/**
*	Function:	L6470_goMark
*	Parameter:	(uint8) address
*
*	Description:
*	Bewegt den Motor zur Mark Position mit dem kürzesten Weg
**/
void L6470_goMark(uint8 address)
{
	uint8 cmd = GO_MARK;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, NULL);
}

/**
*	Function:	L6470_resetPos
*	Parameter:	(uint8) address
*
*	Description:
*	Setzt die ABS_Pos auf 0
**/
void L6470_resetPos(uint8 address)
{
	uint8 cmd = RESET_POS;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, NULL);
}

/**
*	Function:	L6470_resetDevice
*	Parameter:	(uint8) address
*
*	Description:
*	Setzt das Device auf die Power-Up Kondition
**/
void L6470_resetDevice(uint8 address)
{
	uint8 cmd = RESET_DEVICE;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, NULL);
}

/**
*	Function:	L6470_softStop
*	Parameter:	(uint8) address
*
*	Description:
*	Bremst den Motor mit der Abremsungsbeschleunigung
**/
void L6470_softStop(uint8 address)
{
	uint8 cmd = SOFT_STOP;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, NULL);
}

/**
*	Function:	L6470_hardStop
*	Parameter:	(uint8) address
*
*	Description:
*	Bremst den Motor abrupt
**/
void L6470_hardStop(uint8 address)
{
	uint8 cmd = HARD_STOP;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, NULL);
}

/**
*	Function:	L6470_softHiZ
*	Parameter:	(uint8) address
*
*	Description:
*	Setzt die Power Bridges disables (hohe Impedanz)
**/
void L6470_softHiZ(uint8 address)
{
	uint8 cmd = SOFT_HIZ;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, NULL);
}

/**
*	Function:	L6470_hardHiZ
*	Parameter:	(uint8) address
*
*	Description:
*	Setzt die Power Bridges abrupt auf disables (hohe Impedanz)
**/
void L6470_hardHiZ(uint8 address)
{
	uint8 cmd = HARD_HIZ;
	cCommand[0] = cmd;
		
	spi_send_Command(address, 1, cCommand, 0, NULL);
}

/**
*	Function:	L6470_getStatus
*	Parameter:	(uint8) address
*	Return:		uint16
*
*	Description:
*	Gibt den Status zurück
**/
uint16 L6470_getStatus(uint8 address)
{
	uint8 cmd = GET_PARAM;
	cCommand[0] = cmd;
	
	spi_send_Command(address, 1, cCommand, 2, cResponse);
	
	return *(uint16*)cResponse;
}