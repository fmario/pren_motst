/**
*	File:	protocol.h
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

/**------------------ PROTOTYPES ------------------**/
void* parseCommand(void);

typedef struct __rp{
	uint8 ack;
	uint8 payload0;
	uint8 payload1;
	uint8 payload2;
} rspstruct;

void initResp(rspstruct*);

rspstruct initMove(struct InitMovePayload* payload);
rspstruct moveTo(struct MoveToPayload* payload);
void saveLogTo(uint24 pos);
rspstruct waitMoved(struct WaitMovedPayload* payload);
rspstruct isReady(struct IsReadyPayload* payload);
rspstruct move(struct MovePayload* payload);
rspstruct stopMove(struct StopMovePayload* payload);
rspstruct getAbsPos(struct GetAbsPosPayload* payload);
void saveLogAP(uint24 pos);
rspstruct setPin(struct SetPinPayload* payload);
rspstruct getPin(struct GetPinPayload* payload);
rspstruct configPin(struct ConfigPinPayload* payload);
rspstruct saveHome(struct SaveHomePayload* payload);
rspstruct goHome(struct GoHomePayload* payload);
rspstruct saveWayPoint(struct SaveWayPointPayload* payload);
rspstruct moveToWayPoint(struct MoveToWayPointPayload* payload);
rspstruct dcMove(struct DcMovePayload* payload);

uint8 getChecksum(uint8* data, uint8 length);

uint16 swap16(uint16 val);
uint24 swap24(uint24 val);

/**----------------- VARIABLE ------------------**/

//Error codes
extern const uint8 err_fBuffer;
extern const uint8 err_InvCommand;
extern const uint8 err_InvAddress;
extern const uint8 err_MotornRdy;
extern const uint8 err_MotorErr;
extern const uint8 err_fWayPointBuf;
extern const uint8 err_InvWayPoint;
extern const uint8 err_WrongPin;

extern uint24 log[20];
extern uint24 log1[20];

/**------------------ DEFINES ------------------**/
#ifndef PROTOCOL_H
#define PROTOCOL_H

#define NUMBER_WAYPOINTS 15

/**--------------------------------
* --------- UART Protocol ---------
* -------------------------------*/
struct InitMovePayload
{
    uint8 motor;
    uint8 direction;
	uint8 speed;
    uint8 acc;
    uint8 dec;
};

struct MoveToPayload
{
    uint8 motor;
    uint8 direction;
    uint24 absPos;
    uint8 speed;
    uint8 acc;
    uint8 dec;
};

struct WaitMovedPayload
{
    uint8 motor;
    uint16 timeout;
};

struct IsReadyPayload
{
    uint8 motor;
};

struct IsReadyResultPayload
{
    uint8 isReady;
};

struct MovePayload
{
    uint8 motor;
    uint8 direction;
    uint8 speed;
    uint8 acc;
    uint8 dec;
};

struct StopMovePayload
{
    uint8 motor;
    uint8 isHardStop;
};

struct GetAbsPosPayload
{
    uint8 motor;
};

struct GetAbsPosResultPayload
{
    uint24 position;
};

struct SetPinPayload
{
	uint8 pinNr;
    uint8 isHigh;
};

struct GetPinPayload
{
    uint8 pinNr;
};

struct ConfigPinPayload
{
	uint8 pinNr;
    uint8 isOutput;
};

struct SaveHomePayload{
	uint8 motor;
};

struct GoHomePayload{
	uint8 motor;
};

struct SaveWayPointPayload{
	uint8 motor;
};

struct MoveToWayPointPayload{
	uint8 motor;
	uint8 wayPoint;
	uint8 speed;
	uint8 acc;
	uint8 dec;
};

struct DcMovePayload{
	uint8 dir;
	uint16 time;
	uint8 goHiZ;
};

#endif  // !PROTOCOL_H