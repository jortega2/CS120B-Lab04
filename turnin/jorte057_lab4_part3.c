/*	Author: jorte057
 *  Partner(s) Name: Duke Pham
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
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
enum door_states { init, interphase, wait, check, unlock, lock } locksm;

void lock_states(){
	//transitions
	switch(locksm) {
		case init:
			locksm = interphase;
			break;
		case interphase:
			//check for first correct input: # (PA2)
			//PA2 & !PA0 & !PA1 & !PA7
			if (PINA == 0x04){
				locksm = wait;
			}
			//Lock the door if inside button pressed (PA7)
			//PA7 & !PA0 & !PA1 & !PA2
			else if (PINA == 0x08){
				locksm = lock;
			}
			 else {// stay in interphase for anyrthing else
				locksm = interphase;
			}
			break;
		case wait:
			//check for relase of PA2
			if (PINA == 0x04){
				locksm = wait;
			} else {
				locksm = check;
			}
			break;
		case check:
			//check for right combination: # -> y (PA2 -> PA1)
			//PA1 & !PA0 & !PA2 & !PA7
			if (PINA == 0x02){
				locksm = unlock;
			}else{
				locksm = interphase;
			}
			break;
		case unlock:
			//unlock door then go back to interphase
			locksm = interphase;
			break;
		case lock:
			// lock door then go back to interphase
			locksm = interphase;
			break;
		default:
			locksm = interphase;
			break;
	}//transitions
	
	//state actions
	switch(locksm) {
                case init:
			PORTB = 0x00;
                        break;
                case interphase:
			break;
                case wait:
                        break;
		case check:
			break;
                case unlock:
			PORTB = 0x01;
                        break;
		case lock:
			PORTB = 0x00;
			break;
                default:
                        break;
        }//state actins
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	PORTB = 0x00;
	locksm  = init;
    /* Insert your solution below */
    while (1) {
	//reset to locked for each test case
	PORTB = 0x00;
	lock_states();
    }
    return 1;
}
