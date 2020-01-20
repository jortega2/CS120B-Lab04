/*	Author: jorte057 - Juvenal Ortega
 *  Partner(s) Name: Duke Pham - dpham073@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab 4  Exercise 1
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
// init- start of sm
// on1 - turn on PB0, turn off PB1, stay in the state if user still has PBA held down to prevent unwanted changes
// wait1 - no changes to pins, stay in state until user presses PA0 to switch lights
// on2 - turn off PB0, turn on PB1, stay in the state if user still has PBA held down to prevent unwanted changes
// wait2 - no changes to pins, stay in state until user presses PA0 to switch lights
enum sm_states { init, on1, wait1, on2, wait2 } sm;

void sm_tick(){
	//transitions
	switch(sm) {
		case init:
			sm = on1;
			break;
		case on1:
			if (PINA == 0x01){
				sm = on1;
			}
			else if (PINA == 0x00){
				sm = wait1;
			}
			break;
		case wait1:;
                        if (PINA == 0x01){
                                sm = on2;
			}
                        else if (PINA == 0x00){
                                sm = wait1;
			}
			break;
		case on2:
                        if (PINA == 0x01){
                                sm = on2;
			}
                        else if (PINA == 0x00){
                                sm = wait2;
			}
			break;
		case wait2:
                        if (PINA == 0x01){
                                sm = on1;;
			}
                        else if (PINA == 0x00){
                                sm = wait2;
			}
			break;
		default:
			sm = init;
			break;
	}//transitions
	
	//state actions
	switch(sm) {
                case init:
                        break;
                case on1:
                        PORTB = 0x01;
			break;
                case wait1:
                        break;
                case on2:
                        PORTB = 0x02;
                        break;
                case wait2:
                        break;
                default:
                        break;
        }//state actins
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	PORTB = 0x01;
	sm  = init;
    /* Insert your solution below */
    while (1) {
	sm_tick();
    }
    return 1;
}
