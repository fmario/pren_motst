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
uint16 swap16(uint16 val);
uint24 swap24(uint24 val);

/**------------------ DEFINES ------------------**/
#ifndef PROTOCOL_H
#define PROTOCOL_H

/**--------------------------------
* --------- UART Protocol ---------
* -------------------------------*/
struct InitMovePayload
{
    uint8 motor;
    uint8 direction;
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
    uint8 motor;
    uint8 isHigh;
};

struct GetPinPayload
{
    uint8 motor;
};

struct GetPinResultPayload
{
    uint8 isHigh;
};

struct ConfigPinPayload
{
    uint8 motor;
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

struct MoveToWayPoint{
	uint8 motor;
	uint8 wayPoint;
	uint8 acc;
	uint8 dcc;
};

/**--------------------------------
* --------- SPI Protocol ----------
* -------------------------------*/

#endif  // !PROTOCOL_H