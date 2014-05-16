/**
*	File:	queue.c
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

#include "platform\definitions.h"

#include "queue.h"
#include "platform\uart.h"

/**------------------ VARIABLES ------------------**/
queue CommandQueue;

/**------------------ FUNCTIONS ------------------**/

/**
*	Function:	reset_Queue
*	Parameter:	void
*	Return:		void
*
*	Description:
*	Setzt alle Werte und Flags auf 0
**/
void reset_Queue(void){
	CommandQueue.fFull = 0;
	CommandQueue.iCounterRead = 0;
	CommandQueue.iCounterWrite = 0;

	for(int i = 0; i < NUMBER_NODES; i++){
		CommandQueue.qNodes[i].fRead = 0;
		CommandQueue.qNodes[i].iCounter = 0;

		for(int j = 0; j < COMMAND_LENGTH; j++)
			CommandQueue.qNodes[i].cData[j] = 0;
	}
}

/**
*	Function:	read_Queue
*	Parameter:	(uint8*) cBuffer
*	Return:		int
*
*	Description:
*	Schreibt den Array aus dem Aktuellen Queue-Element
*	in den Buffer.
**/
int read_Queue(uint8* cBuffer){
	if(CommandQueue.qNodes[CommandQueue.iCounterRead].fRead){
		
		for(int i = 0; i < COMMAND_LENGTH; i++)
			*(cBuffer + i) = CommandQueue.qNodes[CommandQueue.iCounterRead].cData[i];

		//Reset Node
		CommandQueue.qNodes[CommandQueue.iCounterRead].fRead = 0;
		CommandQueue.qNodes[CommandQueue.iCounterRead].iCounter = 0;

		CommandQueue.iCounterRead = (++CommandQueue.iCounterRead)%NUMBER_NODES;

		return 1;
	}

	return 0;
}

/**
*	Function:	write_Queue
*	Parameter:	(uint8) cBuffer
*	Return:		int
*
*	Description:
*	Schreibt ein Byte an die nächste Stelle.
**/
int write_Queue(uint8 cData){
	uint8 iWN = CommandQueue.iCounterWrite;
	uint8 iWD = CommandQueue.qNodes[iWN].iCounter;

	if(CommandQueue.qNodes[CommandQueue.iCounterWrite].fRead)
		return 0;

	CommandQueue.qNodes[iWN].cData[iWD] = cData;

	if(iWD == COMMAND_LENGTH - 1)
	{
		CommandQueue.qNodes[iWN].fRead = 1;
		CommandQueue.iCounterWrite = (++iWN)%NUMBER_NODES;
	}else{
		CommandQueue.qNodes[iWN].iCounter++;
	}

	return 1;
}