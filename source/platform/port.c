/**
*	File:	port.c
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

#include "definitions.h"

#include "port.h"
#include "team.h"

/**
*	Function:	init_port
*	Parameter:	void
*
*	Description:
*	Initialisiert die Ports
**/
void init_port(void){
	//BUSY Inputs
	TRISB2 = INPUT;
	TRISB3 = INPUT;
	TRISB4 = INPUT;

	//FLAG Inputs
	TRISB5 = INPUT;
	TRISB6 = INPUT;
	TRISB7 = INPUT;

	//nCS Outputs
	TRISE0 = OUTPUT;
	TRISE1 = OUTPUT;
	TRISE2 = OUTPUT;

	//Unused as Outputs
	TRISB1 = OUTPUT;

	for (int i = 0; i < GPIO; i++){
		volatile uint8* tris = gpio_addr[i] + TRIS_OFF;
		uint8 mask = 1 << gpio_offs[i];

		*tris &= ~mask;
	}
}

/**
*	Function:	configPin
*	Parameter:	(uint8) pinNr
*				(uint8) isOutput
*
*	Description:
*	Prüft ob die Pin-Nummer gültig ist.
*	Wenn ja, dann wird der IO-Pin
*	als In- oder Output gesetzt.
*	Gibt 1 zurück bei Erfolg, sonst 0.
**/
uint8 port_configPin(uint8 pinNr, uint8 isOutput){
	if (pinNr < GPIO){
		volatile uint8* tris = gpio_addr[pinNr] + TRIS_OFF;
		uint8 mask = 1 << gpio_offs[pinNr];
		(isOutput > 0) ? (*tris &= ~mask) : (*tris |= mask);
		return 1;
	}

	return 0;
}

/**
*	Function:	setPin
*	Parameter:	(uint8) pinNr
*				(uint8) isHigh
*
*	Description:
*	Prüft ob die Pin-Nummer gültig ist.
*	Wenn ja, dann wird der IO-Pin
*	entsprechend auf High oder Low gesetzt.
*	Gibt 1 zurück bei Erfolg, sonst 0.
**/
uint8 port_setPin(uint8 pinNr, uint8 isHigh){
	if (pinNr < GPIO){
		volatile uint8* tris = gpio_addr[pinNr] + TRIS_OFF;
		volatile uint8* port = gpio_addr[pinNr];
		uint8 mask = 1 << gpio_offs[pinNr];

		if ((*tris & mask) == OUTPUT){
			(isHigh > 0) ? (*port |= mask) : (*port &= ~mask);
			return 1;
		}
	}

	return 0;
}

/**
*	Function:	getPin
*	Parameter:	(uint8) pinNr
*
*	Description:
*	Prüft ob die Pin-Nummer gültig ist.
*	Wenn ja, wird der Status (Low/High) des
*	Pins zurückgegeben.
*	Wenn die Pin-Nummer ungültig ist, wird 0xFF
*	zurück gegeben.
**/
uint8 port_getPin(uint8 pinNr){
	if (pinNr < GPIO){
		volatile uint8* port = gpio_addr[pinNr];
		uint8 mask = 1 << gpio_offs[pinNr];
		return (*port & mask) >> gpio_offs[pinNr];
	}

	return 0xFF;
}