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

#include "platform\definitions.h"

#include "protocol.h"
#include "platform\team.h"

#include "platform\L6470.h"

/**----------------- CONSTANTS -----------------**/
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

/**-------------- EXTERN VARIABLES ---------------**/
//Error codes
const uint8 err_fBuffer = 0xE0;
const uint8 err_InvCommand = 0xE1;
const uint8 err_InvAddress = 0xE2;
const uint8 err_MotornRdy = 0xE3;
const uint8 err_MotorErr = 0xE4;
const uint8 err_fWayPointBuf = 0xE5;
const uint8 err_InvWayPoint = 0xE6;

/**------------------ VARIABLES ------------------**/
uint24 wayPoint[SPI_MOTORS][NUMBER_WAYPOINTS];
uint8 cntrWayPoint[SPI_MOTORS];
rspstruct response;

/**------------------ FUNCTIONS ------------------**/

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

void initResp(rspstruct* resp){
	(*resp).ack = 0;
	(*resp).payload0 = 0;
	(*resp).payload1 = 0;
	(*resp).payload2 = 0;
}

/**
*	Function:	initMove
*	Parameter:	(struct InitMovePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct initMove(struct InitMovePayload* payload){
	uint8 iMotNr = (*payload).motor;
	initResp(&response);

	if(iMotNr < SPI_MOTORS){

		if (L6470_checkStartConditions(iMotNr) == 0){
			response.payload0 = err_MotornRdy;
			return response;
		}

		if ((*payload).acc != 0)
			L6470_setParam(iMotNr, ACC, L6470_accCalc((*payload).acc));
		if ((*payload).dec != 0)
			L6470_setParam(iMotNr, DEC, L6470_accCalc((*payload).dec));

		L6470_run(iMotNr, (*payload).direction, L6470_speedCalc((*payload).speed));

		while(PORTB_IO.nFlag & (1<<iMotNr));

		L6470_hardStop(iMotNr);

		L6470_status state = L6470_ParseStatus(L6470_getStatus(iMotNr));

		if (state.OCD && state.STEP_LOSS_A && state.STEP_LOSS_B){
			response.payload0 = err_MotorErr;
			return response; //Kein Schritt verloren oder Overcurrent
		}

		L6470_resetPos(iMotNr);

		response.ack = 1;
		return response;
	}

	response.payload0 = err_InvAddress;
	return response;
}

/**
*	Function:	moveTo
*	Parameter:	(struct MoveToPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct moveTo(struct MoveToPayload* payload){
	uint8 iMotNr = (*payload).motor;
	initResp(&response);

	if(iMotNr < SPI_MOTORS){
		if (L6470_checkStartConditions(iMotNr) == 0){
			response.payload0 = err_MotornRdy;
			return response;
		}

		if((*payload).acc != 0)
			L6470_setParam(iMotNr, ACC, L6470_accCalc((*payload).acc));
		if((*payload).dec != 0)
			L6470_setParam(iMotNr, DEC, L6470_accCalc((*payload).dec));
		if((*payload).speed != 0)
			L6470_setParam(iMotNr, MAX_SPEED, L6470_maxSpeedCalc((*payload).speed));

		L6470_goTo_Dir(iMotNr, (*payload).direction, (*payload).absPos);

		response.ack = 1;
		return response;
	}

	response.payload0 = err_InvAddress;
	return response;
}

/**
*	Function:	waitMoved
*	Parameter:	(struct WaitMovedPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct waitMoved(struct WaitMovedPayload* payload){
	uint8 iMotNr = (*payload).motor;
	initResp(&response);

	if (iMotNr < SPI_MOTORS){
		/*
		
		TODO **********************************************************************************************************
		
		*/
	}


	response.ack = 1;
	return response;
}

/**
*	Function:	isReady
*	Parameter:	(struct IsReadyPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct isReady(struct IsReadyPayload* payload){
	uint8 iMotNr = (*payload).motor;
	initResp(&response);

	if (iMotNr < SPI_MOTORS){
		response.payload0 = L6470_isMoving(iMotNr) ? 0 : 1;
		response.ack = 1;
		return response;
	}

	response.payload0 = err_InvAddress;
	return response;
}

/**
*	Function:	move
*	Parameter:	(struct MovePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct move(struct MovePayload* payload){
	uint8 iMotNr = (*payload).motor;
	initResp(&response);

	if (iMotNr < SPI_MOTORS){
		if (L6470_checkStartConditions(iMotNr) == 0){
			response.payload0 = err_MotornRdy;
			return response;
		}

		if ((*payload).acc != 0)
			L6470_setParam(iMotNr, ACC, L6470_accCalc((*payload).acc));
		if ((*payload).dec != 0)
			L6470_setParam(iMotNr, DEC, L6470_accCalc((*payload).dec));

		L6470_run(iMotNr, (*payload).direction, (*payload).speed);

		response.ack = 1;
		return response;
	}

	response.payload0 = err_InvAddress;
	return response;
}

/**
*	Function:	stopMove
*	Parameter:	(struct StopMovePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct stopMove(struct StopMovePayload* payload){
	uint8 iMotNr = (*payload).motor;
	initResp(&response);

	if (iMotNr < SPI_MOTORS){

		if ((*payload).isHardStop != 0)
			L6470_hardStop(iMotNr);
		else
			L6470_softStop(iMotNr);

		response.ack = 1;
		return response;
	}

	response.payload0 = err_InvAddress;
	return response;
}

/**
*	Function:	getAbsPos
*	Parameter:	(struct GetAbsPosPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct getAbsPos(struct GetAbsPosPayload* payload){
	uint8 iMotNr = (*payload).motor;
	initResp(&response);

	if (iMotNr < SPI_MOTORS){
		response.ack = 1;
		*(uint24*)&response.payload0 = L6470_getParam(iMotNr, ABS_POS);
		return response;
	}

	response.payload0 = err_InvAddress;
	return response;
}

/**
*	Function:	setPin
*	Parameter:	(struct SetPinPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct setPin(struct SetPinPayload* payload){
	initResp(&response);
	response.ack = 1;
	return response;
}

/**
*	Function:	getPin
*	Parameter:	(struct GetPinPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct getPin(struct GetPinPayload* payload){
	initResp(&response);
	response.ack = 1;
	return response;
}

/**
*	Function:	configPin
*	Parameter:	(struct ConfigPinPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct configPin(struct ConfigPinPayload* payload){
	initResp(&response);
	response.ack = 1;
	return response;
}

/**
*	Function:	saveHome
*	Parameter:	(struct SaveHomePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct saveHome(struct SaveHomePayload* payload){
	uint8 iMotNr = (*payload).motor;
	initResp(&response);

	if (iMotNr < SPI_MOTORS){
		L6470_resetPos(iMotNr);

		response.ack = 1;
		return response;
	}

	response.payload0 = err_InvAddress;
	return response;
}

/**
*	Function:	goHome
*	Parameter:	(struct GoHomePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct goHome(struct GoHomePayload* payload){
	uint8 iMotNr = (*payload).motor;
	initResp(&response);

	if (iMotNr < SPI_MOTORS){
		L6470_goHome(iMotNr);

		response.ack = 1;
		return response;
	}

	response.payload0 = err_InvAddress;
	return response;
}

/**
*	Function:	saveWayPoint
*	Parameter:	(struct SaveWayPointPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct saveWayPoint(struct SaveWayPointPayload* payload){
	uint8 iMotNr = (*payload).motor;
	initResp(&response);

	if (iMotNr < SPI_MOTORS){

		if (cntrWayPoint[iMotNr] >= NUMBER_WAYPOINTS){
			response.payload0 = err_fWayPointBuf;
			return response;
		}

		wayPoint[iMotNr][cntrWayPoint[iMotNr]++] = L6470_getParam(iMotNr, ABS_POS);

		response.payload0 = (cntrWayPoint[iMotNr] - 1);
		response.ack = 1;
		return response;
	}

	response.payload0 = err_InvAddress;
	return response;
}

/**
*	Function:	moveToWayPoint
*	Parameter:	(struct MoveToWayPointPayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct moveToWayPoint(struct MoveToWayPointPayload* payload){
	uint8 iMotNr = (*payload).motor;
	initResp(&response);

	if (iMotNr < SPI_MOTORS){
		if (cntrWayPoint[iMotNr] >= (*payload).wayPoint){
			response.payload0 = err_InvWayPoint;
			return response;
		}
		if (L6470_checkStartConditions(iMotNr) == 0){
			response.payload0 = err_MotornRdy;
			return response;
		}

		if ((*payload).acc != 0)
			L6470_setParam(iMotNr, ACC, L6470_accCalc((*payload).acc));
		if ((*payload).dec != 0)
			L6470_setParam(iMotNr, DEC, L6470_accCalc((*payload).dec));
		if ((*payload).speed != 0)
			L6470_setParam(iMotNr, MAX_SPEED, L6470_maxSpeedCalc((*payload).speed));

		L6470_goTo(iMotNr, wayPoint[iMotNr][(*payload).wayPoint]);

		response.ack = 1;
		return response;
	}

	response.payload0 = err_InvAddress;
	return response;
}

/**
*	Function:	dcMove
*	Parameter:	(struct DcMovePayload*) data
*	Return:		uint24
*
*	Description:
*	...
**/
rspstruct dcMove(struct DcMovePayload* payload){
	initResp(&response);
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
				asm("NOP");
				asm("NOP");
				asm("NOP");
				asm("NOP");
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
	response.ack = 1;
	return response;
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