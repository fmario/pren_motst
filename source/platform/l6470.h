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

/**------------------- CONSTANTS ------------------**/
#define NUMBER_PARAM 25

/**------------------ PROTOTYPES ------------------**/
void L6470_setParam(uint8 address, uint8 param, uint24 value);
uint24	L6470_getParam(uint8 address, uint8 param);
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

uint8 L6470_isMoving(uint8 address);
uint8 L6470_checkStartConditions(uint8 address);
uint8 L6470_parseParamSend(uint8 param, uint24* value);
uint8 L6470_parseParamReceived(uint8 param, uint24* value);
uint24 L6470_speedCalc(uint8 stepsPerSec);
uint24 L6470_maxSpeedCalc(uint8 stepsPerSec);
uint24 L6470_accCalc(uint8 stepsPerSecSqrt);

typedef struct _st{
	uint8 HiZ : 1;
	uint8 BUSY : 1;
	uint8 SW_F : 1;
	uint8 SW_EVN : 1;
	uint8 DIR : 1;
	uint8 MOT_STATUS : 2;
	uint8 NOTPERF_CMD : 1;
	uint8 WRONG_CMD : 1;
	uint8 UVLO : 1;
	uint8 TH_WRN : 1;
	uint8 TH_SD : 1;
	uint8 OCD : 1;
	uint8 STEP_LOSS_A : 1;
	uint8 STEP_LOSS_B : 1;
	uint8 SCK_MOD : 1;
}L6470_status;

L6470_status L6470_ParseStatus(uint16 u16_state);

/**------------------ DEFINES ------------------**/
#ifndef L6470_H
#define L6470_H

// Register address redefines.
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

//L6470 commands
#define NOPP                 0x00
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

// constant definitions for overcurrent thresholds
#define OCD_TH_375mA 0x00
#define OCD_TH_750mA 0x01
#define OCD_TH_1125mA 0x02
#define OCD_TH_1500mA 0x03
#define OCD_TH_1875mA 0x04
#define OCD_TH_2250mA 0x05
#define OCD_TH_2625mA 0x06
#define OCD_TH_3000mA 0x07
#define OCD_TH_3375mA 0x08
#define OCD_TH_3750mA 0x09
#define OCD_TH_4125mA 0x0A
#define OCD_TH_4500mA 0x0B
#define OCD_TH_4875mA 0x0C
#define OCD_TH_5250mA 0x0D
#define OCD_TH_5625mA 0x0E
#define OCD_TH_6000mA 0x0F

// STEP_MODE option values.
#define STEP_SEL_1 0x00
#define STEP_SEL_1_2 0x01
#define STEP_SEL_1_4 0x02
#define STEP_SEL_1_8 0x03
#define STEP_SEL_1_16 0x04
#define STEP_SEL_1_32 0x05
#define STEP_SEL_1_64 0x06
#define STEP_SEL_1_128 0x07

#endif  // !L6470_H