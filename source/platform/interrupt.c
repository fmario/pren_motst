/**
*	File:	interrupt.c
*	Date:	04.04.2014
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

#include "definitions.h"

#include "../protocol.h"

#include "interrupt.h"
#include "../queue.h"
#include "uart.h"
#include "spi.h"


/**
*	Function:	enable_interrupt
*	Parameter:	void
*	Return:		void
*
*	Description:
*	Aktiviert alle Interrupts ohne Prioritäten.
**/
void enable_interrupt(void){
	IPEN = 0;	//No priority (compatibility mode)
	GIE = 1;	//enable all interrupts
	PEIE = 1;	//enable all periphal interrupts
}

/**
*	Function:	handler
*	Parameter:	void
*	Return:		void
*
*	Description:
*	Handlet alle Interrupts.
**/
void interrupt handler(void){
	/* UART Receive Interrupt */
	if(RCIF){
		if(write_Queue(uart_receive_Byte()))
			uart_send_Array(ANSWER_LENGTH, err_fBuffer);
	}
}