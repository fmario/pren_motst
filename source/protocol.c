/**
*	File:	protocol.c
*	Date:	27.03.2014
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

#include "platform/definitions.h"

#include "protocol.h"
#include "platform\team.h"

#include "platform\team27.h"

//Array mit allen Funktionspointern
const void* pCommand[NUMBER_COMMAND] = {
					&initMove,
					&moveTo,
					&waitMoved,
					&isReady,
					&move,
					&stopMove,
					&getAbsPos,
					&setPin,
					&getPin,
					&configPin,
					&saveHome,
					&goHome,
					&saveWayPoint,
					&moveToWayPoint,
					&dcMove
				};

//Error codes
uint8 err_fBuffer[ANSWER_LENGTH] = {0x00, 0xE0, 0x00, 0x00 /*, CHECKSUM*/};
uint8 err_InvCommand[ANSWER_LENGTH] = {0x00, 0xE1, 0x00, 0x00 /*, CHECKSUM*/};
uint8 err_InvParam[ANSWER_LENGTH] = {0x00, 0xE2, 0x00, 0x00 /*, CHECKSUM*/};

/**
*	Function:	checkCommand
*	Parameter:	void
*	Return:		uint16
*
*	Description:
*	Überprüft, ob ein gültiger Befehl vorliegt 
*	und gibt die Adresse auf entsprechende Funktion zurück.
**/
void* parseCommand(void){
	if (_received_Data[0] < NUMBER_COMMAND){

		for (int i = 0; i < NUMBER_COMMAND - 1; i++){
			_payload[i] = _received_Data[i + 1];
		}
		return (void*)pCommand[_received_Data[0]];
	}
	else{
		return 0;
	}
}

/**
*	Function:	initMove
*	Parameter:	(struct InitMovePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 initMove(struct InitMovePayload* payload){
	uint8 iMotNr = (*payload).motor;

	if(iMotNr < SPI_MOTORS){
		L6470_setParam(iMotNr, ACC, L6470_accCalc((*payload).acc));
		L6470_setParam(iMotNr, DEC, L6470_accCalc((*payload)..dec));
		L6470_run(iMotNr, (*payload).direction, L6470_speedCalc((*payload).speed));

		while(!PORTB_IO.nFlag & (1<<iMotNr));

		L6470_hardStop(iMotNr);
		L6470_getStatus(iMotNr);
		/*
			DO ANTYTHING
		*/
		L6470_resetPos(iMotNr);

		return 0;
	}

	return NULL;
}

/**
*	Function:	moveTo
*	Parameter:	(struct MoveToPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 moveTo(struct MoveToPayload* payload){

	return 0;
}

/**
*	Function:	waitMoved
*	Parameter:	(struct WaitMovedPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 waitMoved(struct WaitMovedPayload* payload){

	return 0;
}

/**
*	Function:	isReady
*	Parameter:	(struct IsReadyPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 isReady(struct IsReadyPayload* payload){
	return 0;
}

/**
*	Function:	move
*	Parameter:	(struct MovePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 move(struct MovePayload* payload){
	return 0;
}

/**
*	Function:	stopMove
*	Parameter:	(struct StopMovePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 stopMove(struct StopMovePayload* payload){
	return 0;
}

/**
*	Function:	getAbsPos
*	Parameter:	(struct GetAbsPosPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 getAbsPos(struct GetAbsPosPayload* payload){
	return 0;
}

/**
*	Function:	setPin
*	Parameter:	(struct SetPinPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 setPin(struct SetPinPayload* payload){
	return 0;
}

/**
*	Function:	getPin
*	Parameter:	(struct GetPinPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 getPin(struct GetPinPayload* payload){
	return 0;
}

/**
*	Function:	configPin
*	Parameter:	(struct ConfigPinPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 configPin(struct ConfigPinPayload* payload){
	return 0;
}

/**
*	Function:	saveHome
*	Parameter:	(struct SaveHomePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 saveHome(struct SaveHomePayload* payload){
	return 0;
}

/**
*	Function:	goHome
*	Parameter:	(struct GoHomePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 goHome(struct GoHomePayload* payload){
	return 0;
}

/**
*	Function:	saveWayPoint
*	Parameter:	(struct SaveWayPointPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 saveWayPoint(struct SaveWayPointPayload* payload){
	return 0;
}

/**
*	Function:	moveToWayPoint
*	Parameter:	(struct MoveToWayPointPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 moveToWayPoint(struct MoveToWayPointPayload* payload){
	return 0;
}

/**
*	Function:	dcMove
*	Parameter:	(struct DcMovePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
uint24 dcMove(struct DcMovePayload* payload){
	if(DC_MOTORS){
		if((*payload).dir){
			DC_FW = 0;
			DC_RW = 1;
		}else{
			DC_RW = 0;
			DC_FW = 1;
		}
		
		for(uint16 i = 0; i < (*payload).time; i++){
			for(int j = 0; j < 7; j++){
				_delay3(4);
			}
				
		}

		if((*payload).goHiZ){
			DC_FW = 1;
			DC_RW = 1;
		}else{
			DC_FW = 0;
			DC_RW = 0;
		}
	}
	return 0;
}

/**
*	Function:	getChecksum
*	Parameter:	(uint8*) data
				(uint8) length
*	Return:		uint8
*
*	Description:
*	Berechnet die Checksume der Daten. 
*	data ist der Pointer auf das erste Byte 
*	und length ist die Anzahl zu integrierenden Bytes.
**/
uint8 getChecksum(uint8* data, uint8 length){

	return 42;
}

/**
*	Function:	swap16
*	Parameter:	(uint16) val
*	Return:		uint16
*
*	Description:
*	Ändert den Endian-Typ einer 16bit Zahl
**/
uint16 swap16(uint16 val){
	return (val << 8) | (val >> 8 );
}

/**
*	Function:	swap24
*	Parameter:	(uint24) val
*	Return:		uint24
*
*	Description:
*	Ändert den Endian-Typ einer 24bit Zahl
**/
uint24 swap24(uint24 val){
	return (val << 16) | (val >> 16) | (val & 0x0F0);
}