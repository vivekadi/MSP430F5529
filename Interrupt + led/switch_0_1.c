#include <msp430f5529.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    //P1DIR |= BIT0;  // Set P1.0to output direction
    //P2REN |= BIT2;
    //P2OUT |= BIT2;
    P1DIR=0x01;
    P2DIR |=0x00;
    P2REN |=0xFF;
    P2OUT |= 0xFF;

    while(1) {

            if (!(P2IN & 0x02)) {   // If button is open(P2.1 HIGH)
                P1OUT = 0x01; //   ... turn on LED
            }               // or P1OUT |= BIT0;
             else {
                P1OUT = 0x00;//   ... else turn it off.
                                // or P1OUT &= ~BIT0
            }
        }
    }
