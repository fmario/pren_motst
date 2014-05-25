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
	if(CCP1IF){
		//Reset timer
		TMR3ON = 0;
		TMR3 = 0;

		// Update aktuelle Position
		(m4_state.dir == 0) ? m4_state.absPos-- : m4_state.absPos++;
		m4_state.stepCount++;

		if(m4_state.softStop == 1){
			if(CCPR1 > m4_state.maxCCPR || (0xFFFF - CCPR1) < m4_state.CCPR1inc){
				m4_state.motorState = 0;
				m4_state.softStop = 0;
				m4_state.stepCount = 0;
				CCP1IF = 0;
				return;
			}			
			CCPR1 += m4_state.CCPR1inc;
		}else if(m4_state.motorState == 1){ // Beschleunigen
			if(CCPR1 < m4_state.minCCPR || CCPR1 < m4_state.CCPR1dec){
				CCPR1 = m4_state.minCCPR;
				m4_state.motorState = 2; // konstante Phase
			}else{
				CCPR1 -= m4_state.CCPR1dec;
			}

			if(m4_state.stepCount == m4_state.decStp)
				m4_state.motorState = 3; // Verzögerungsphase
		}else if(m4_state.motorState == 2){ // konstante Geschw.
			if(m4_state.stepCount == m4_state.decStp)
				m4_state.motorState = 3; // Verzögerungsphase
		}else if(m4_state.motorState == 3){ // Bremsen
			CCPR1 += m4_state.CCPR1inc;

			if(CCPR1 > m4_state.maxCCPR)
				CCPR1 = m4_state.maxCCPR;

			if(m4_state.tarPos == m4_state.absPos){
				m4_state.motorState = 0;
				m4_state.softStop = 0;
				m4_state.stepCount = 0;
				CCP1IF = 0;
				return;
			}			
		}
		
		TMR3ON = 1;
		CCP1IF = 0;
	}
}