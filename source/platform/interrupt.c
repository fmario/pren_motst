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
#include "a3977.h"

rspstruct full_Buf;
uint8 cError = 0;
uint8 cStep = 0;

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
void /*interrupt*/ handler(void){
	/* UART Receive Interrupt */
	if(RCIF){
		if (!write_Queue(uart_receive_Byte())){
			if (++cError == COMMAND_LENGTH){
				cError = 0;
				initResp(&full_Buf);
				full_Buf.payload0 = err_fBuffer;
				uart_send_Array(ANSWER_LENGTH, (uint8*)&full_Buf);
			}
		}
	}
	/* Compare Interrupt */
	else if(CCP1F){
		//Reset timer
		TMR3ON = 0;
		TMR3 = 0;
		TMR3ON = 1;

		// Aktueller Geschwindigkeit berechnen
		uint16 currentSpeed = (625000 >> (STP_MOD+1)) / CCPR1;

		// Berechnet die Strecke bis zum Stillstand
		uint24 streakToStop = (uint24)(currentSpeed >> 4) * (uint24)(currentSpeed >> 5)/m4_state.dec;

		if (m4_state.dir){

			// neue aktuelle Position
			m4_state.absPos++;

			// Ziel erreicht
			if (m4_state.absPos != m4_state.dest){ 
				TMR3ON = 0;
				m4_state.busy = 0;
				m4_state.decStop = 0;
				m4_state.softStop = 0;
				CCP1F = 0;
				return;
			}

			// Berechnet die Strecke bis zum Ziel
			uint24 divPos = m4_state.dest - m4_state.absPos;
			divPos &= 0x3FFFFF;
	
			if (m4_state.softStop){ //Interrupted Stop
				uint16 divSpeed = ((CCPR1) / 625000 * m4_state.dec) << 8;
				divSpeed *= ++cStep;

				if (divSpeed > currentSpeed){ //Stehen bleiben
					TMR3ON = 0;
					m4_state.busy = 0;
					m4_state.decStop = 0;
					CCP1F = 0;
					return;
				}
				else
					currentSpeed -= divSpeed;

				uint16 newSpeed = (625000 >> (STP_MOD + 1)) / currentSpeed;

				if (newSpeed != CCPR1)
					cStep = 0;

				CCPR1 = newSpeed;
			}
			else if (m4_state.decStop){ // Bremsen
				uint16 divSpeed = ((CCPR1) / 625000 * m4_state.dec) << 8;
				divSpeed *= ++cStep;

				if (divSpeed > currentSpeed)
					currentSpeed = 1;
				else
					currentSpeed -= divSpeed;

				uint16 newSpeed = (625000 >> (STP_MOD + 1)) / currentSpeed;

				if (newSpeed != CCPR1)
					cStep = 0;

				CCPR1 = newSpeed;
			}
			else if (divPos <= streakToStop){ // Bremsen einleiten
				m4_state.decStop = 1;
				cStep = 0;
			}
			else if (currentSpeed < m4_state.speed){ // Beschleunigen
				uint16 divSpeed = ((CCPR1)/625000*m4_state.acc) << 8;
				divSpeed *= ++cStep;

				uint16 newSpeed = currentSpeed + divSpeed;

				if (newSpeed > m4_state.speed)
					newSpeed = m4_state.speed;

				newSpeed = (625000 >> (STP_MOD + 1)) / newSpeed;

				if (newSpeed != CCPR1)
					cStep = 0;

				CCPR1 = newSpeed;
			}
			
		}
		else{
			// neue aktuelle Position
			m4_state.absPos--;

			// Ziel erreicht
			if (m4_state.absPos != m4_state.dest){
				TMR3ON = 0;
				m4_state.busy = 0;
				m4_state.decStop = 0;
				CCP1F = 0;
				return;
			}

		}

		
		CCP1F = 0;
	}
}