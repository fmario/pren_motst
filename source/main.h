/**
*	File:	main.h
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
int main(void);

/**------------------ DEFINES ------------------**/
#ifndef MAIN_H
#define MAIN_H

#ifdef T27
#include "platform/team27.h"
#endif // T27

#ifdef T23
#include "platform/team23.h"
#endif // T23

#endif  // !MAIN_H