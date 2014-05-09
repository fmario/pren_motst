/**
*	File:	main.c
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

#include "platform/definitions.h"

//Team wählen (T23, T27)
#define T27

#include "main.h"

#include "protocol.h"
#include "platform/interrupt.h"
#include "platform/uart.h"
#include "platform/spi.h"
#include "platform/port.h"

/**-------------- EXTERN VARIABLES ---------------**/
flags _Flags = 0;
uint8 _received_Data[COMMAND_LENGTH];
uint8 _payload[COMMAND_LENGTH - 1];

/**------------------ VARIABLES ------------------**/
uint24(*commandptr)(uint8[]);
uint24 response;
/**------------------ FUNCTIONS ------------------**/

/**
*	Function:	main
*	Parameter:	void
*
*	Description:
*	...
**/
int main(void){
	
	// Initialisation
	init_port();
	init_uart();
	init_spi();
	
	for(;;){
		if(_Flags.fRC){
			commandptr = parseCommand();
			_Flags.fRC = 0;

			if (commandptr != 0){
				response = commandptr(_payload);
			}
			else{
				/*
				ERROR
				*/
			}
		}
	}
	return 0;
}