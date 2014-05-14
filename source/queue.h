/**
*	File:	queue.h
*	Date:	14.05.2014
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
void reset_Queue(void);
int read_Queue(uint8* cBuffer);
int write_Queue(uint8 cData);

/**------------------ DEFINES ------------------**/
#ifndef QUEUE_H
#define QUEUE_H

#define NUMBER_NODES 3

typedef struct __qn
{
	uint8	iCounter:7;				//Counter for data element
	uint8	fRead:1;				//1 = Data to read, 0 = can write
	uint8	cData[COMMAND_LENGTH];
} queuenode;

typedef struct __q
{
	uint8	iCounterRead:2;
	uint8	iCounterWrite:2;
	uint8	fFull:1;
	queuenode qNodes[NUMBER_NODES];
} queue;

#endif  // !QUEUE_H