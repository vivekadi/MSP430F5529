#include <msp430f5529.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    //P1DIR |= BIT0;  // Set P1.0to output direction
    //P2REN |= BIT2;
    //P2OUT |= BIT2;
    P3DIR=0xFF;
    P2DIR |=0x00;
    P2REN |=0xFF;
    P2OUT |= 0xFF;
    unsigned int r=0,s=0,x=0;
    char code[]={0xFC,0x60,0xDA,0xF2};
    while(1) {

            if (!(P2IN & 0x04)==0)   // If button is open(P2.1 HIGH)
               r=0;
            if (!(P2IN & 0x04)==1)
                r=1;
           if (!(P2IN & 0x10)==0)
               s=0;
          if(!(P2IN & 0x10)==1)
                s=2;
           x=r+s;
            P3OUT=code[x];



        }
    }
