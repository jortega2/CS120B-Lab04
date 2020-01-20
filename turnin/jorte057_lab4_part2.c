/*	Author: jorte057 - Juvenal Ortega
 *  Partner(s) Name: Duke Pham dpham073@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//
//
// init- start of sm, set PORTC to 0x07
// interphase - state that leads to either increment, decrement or reset states depending on inputs PA0 and PA1
// inc - sets PORTC = PORTC + 1 if PORTC is less than 9. Leads to incWait state
// dec - sets PORTC = PORTC - 1 if PORTC is greater than 0. Leads to decWait state
// incWait/decWait - wait for user to release PA0 or PA1, then goes back to interphase. This is to prevent unwanted behavior
// reset - sets PORTC to 0x07, then unconditionally goes back to interphase state.
enum add_states { init, interphase, inc, incWait, dec, decWait, reset } addsm;

void add_states(){
	//transitions
	switch(addsm) {
		case init:
			addsm = interphase;
			break;
		case interphase:
			//PA0 & !PA1 go to inc
			if (PINA == 0x01){
				addsm = inc;
			}
			//PA1 & !PA0 go to dec
			else if (PINA == 0x02){
				addsm = dec;
			}
			//!PA0 and !PA1 go to reset
			else if (PINA == 0x00){
				addsm = reset;
			} else {// stay in interphase for anyrthing else
				addsm = interphase;
			}
			break;
		case inc:
			addsm = incWait;
			break;
		case incWait:
			//wait for button release 
			if (PINA == 0x01){
				addsm = incWait;
			}else{
				addsm = interphase;
			}
			break;
		case dec:
			addsm = decWait;
			break;
		case decWait:
			// wait for button release
                        if (PINA == 0x02){
                                addsm = decWait;
                        }else{
                                addsm = interphase;
                        }
			break;
		case reset:
			addsm = interphase;
			break;
		default:
			addsm = interphase;
			break;
	}//transitions
	
	//state actions
	switch(addsm) {
                case init:
			PORTC = 0x07;
                        break;
                case interphase:
			break;
                case inc:
			// Add 1 to PORTC but doesn't surpass 9
			if (PORTC < 0x09)
				PORTC = (PORTC + 0x01);
                        break;
		case incWait:
			break;
                case dec:
			//Subtract 1 to PORTC but doesn't go below 0
			if (PORTC > 0x00)
                        	PORTC = (PORTC - 0x01);
                        break;
		case decWait:
			break;
                case reset:
			PORTC = 0x07;
                        break;
                default:
                        break;
        }//state actins
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	PORTC = 0x07;
	addsm  = init;
    /* Insert your solution below */
    while (1) {
	add_states();
    }
    return 1;
}
