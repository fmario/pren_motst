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

#include <htc.h>

#include "main.h"

#include "platform/uart.h"
#include "platform/spi.h"
#include "platform/port.h"

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
	
	}
	return 0;
}