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

#include "main.h"

#include "protocol.h"
#include "queue.h"
#include "platform/interrupt.h"
#include "platform/uart.h"
#include "platform/spi.h"
#include "platform/port.h"

/**-------------- EXTERN VARIABLES ---------------**/
uint8 _received_Data[COMMAND_LENGTH];
uint8 _payload[COMMAND_LENGTH - 1];

/**------------------ VARIABLES ------------------**/
uint24(*commandptr)(uint8[]);
struct AnswerStructure response;
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
	enable_interrupt();
	reset_Queue();

	for(;;){
		if(read_Queue(&_received_Data)){
			commandptr = (uint24*)parseCommand();

			if (commandptr != 0){
				response.payload = commandptr(_payload);
				response.ack = 1;

				if(response.payload != NULL)
					uart_send_Array(ANSWER_LENGTH, (uint8*)&response);
				else
					uart_send_Array(ANSWER_LENGTH, err_InvParam);
			}
			else{
				uart_send_Array(ANSWER_LENGTH, err_InvCommand);
			}
		}
	}
	return 0;
}