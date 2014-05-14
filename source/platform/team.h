/**
*	File:	team.h
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
#ifndef TEAM_H
#define TEAM_H

#ifdef T27
#include "team27.h"
#endif // T27

#ifdef T23
#include "team23.h"
#endif // T23

#endif  // !TEAM_H