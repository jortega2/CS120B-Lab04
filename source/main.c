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
// init- start of sm
// on1 - turn on PB0, turn off PB1, stay in the state if user still has PBA held down to prevent unwanted changes
// wait1 - no changes to pins, stay in state until user presses PA0 to switch lights
// on2 - turn off PB0, turn on PB1, stay in the state if user still has PBA held down to prevent unwanted changes
// wait2 - no changes to pins, stay in state until user presses PA0 to switch lights
enum add_states { init, interphase, inc, dec, reset, wait } addsm;

void add_states(){
	//transitions
	switch(addsm) {
		case init:
			addsm = interphase;
			break;
		case interphase:
			if (PINA == 0x01){
				addsm = inc;
			}
			else if (PINA == 0x02){
				addsm = dec;
			}else if (PINA == 0x00){
				addsm = reset;
			} else {
				addsm = interphase;
			}
			break;
		case inc:
			addsm = wait;
			break;
		case dec:
			addsm = wait;
			break;
		case reset:
			addsm = wait;
			break;
		case wait:
			if ( PINA != 0x00){
				addsm = wait;
			}else{
				addsm = interphase;
			}
		default:
			addsm = interphase;
			break;
	}//transitions
	
	//state actions
	switch(addsm) {
                case init:
                        break;
                case interphase:
			break;
                case inc:
			if (PORTC < 0x09)
				PORTC = (PORTC + 0x01);
                        break;
                case dec:
			if (PORTC > 0x00)
                        	PORTC = (PORTC - 0x01);
                        break;
		case wait:
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
