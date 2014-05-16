/**
*	File:	L6470.h
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

/**------------------ PROTOTYPES ------------------**/
void L6470_setParam(uint8 address, uint8 param, uint24 value);
uint24	L6470_getParam(uint8 address, uint param);
void L6470_run(uint8 address, uint8 dir, uint24 spd);
void L6470_stepClock(uint8 address, uint8 dir);
void L6470_move(uint8 address, uint8 dir, uint24 n_step);
void L6470_goTo(uint8 address, uint24 abs_pos);
void L6470_goTo_Dir(uint8 address, uint8 dir, uint24 abs_pos);
void L6470_goUntil(uint8 address, uint8 act, uint8 dir, uint24 spd);
void L6470_releaseSW(uint8 address, uint8 act, uint8 dir);
void L6470_goHome(uint8 address);
void L6470_goMark(uint8 address);
void L6470_resetPos(uint8 address);
void L6470_resetDevice(uint8 address);
void L6470_softStop(uint8 address);
void L6470_hardStop(uint8 address);
void L6470_softHiZ(uint8 address);
void L6470_hardHiZ(uint8 address);
uint16 L6470_getStatus(uint8 address);
/**------------------ DEFINES ------------------**/
#ifndef L6470_H
#define L6470_H

// Register address redefines.
//  See the Param_Handler() function for more info about these.
#define ABS_POS              0x01
#define EL_POS               0x02
#define MARK                 0x03
#define SPEED                0x04
#define ACC                  0x05
#define DEC                  0x06
#define MAX_SPEED            0x07
#define MIN_SPEED            0x08
#define FS_SPD               0x15
#define KVAL_HOLD            0x09
#define KVAL_RUN             0x0A
#define KVAL_ACC             0x0B
#define KVAL_DEC             0x0C
#define INT_SPD              0x0D
#define ST_SLP               0x0E
#define FN_SLP_ACC           0x0F
#define FN_SLP_DEC           0x10
#define K_THERM              0x11
#define ADC_OUT              0x12
#define OCD_TH               0x13
#define STALL_TH             0x14
#define STEP_MODE            0x16
#define ALARM_EN             0x17
#define CONFIG               0x18
#define STATUS               0x19

//dSPIN commands
#define NOP                  0x00
#define SET_PARAM            0x00
#define GET_PARAM            0x20
#define RUN                  0x50
#define STEP_CLOCK           0x58
#define MOVE                 0x40
#define GOTO                 0x60
#define GOTO_DIR             0x68
#define GO_UNTIL             0x82
#define RELEASE_SW           0x92
#define GO_HOME              0x70
#define GO_MARK              0x78
#define RESET_POS            0xD8
#define RESET_DEVICE         0xC0
#define SOFT_STOP            0xB0
#define HARD_STOP            0xB8
#define SOFT_HIZ             0xA0
#define HARD_HIZ             0xA8
#define GET_STATUS           0xD0

#endif  // !L6470_H