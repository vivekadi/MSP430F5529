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
    unsigned int r=0,s=0,t=0,u=0,x=0;
    char code[]={0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xE6,0xEE,0x3E,0x9C,0x7A,0x9E,0x8E};
    while(1)
    {

          if(!(P2IN & 0x04)==0)   //
              r=0;
          if(!(P2IN & 0x04)==1)
              r=1;
          if(!(P2IN & 0x10)==0)
              s=0;
          if(!(P2IN & 0x10)==1)
              s=2;
          if(!(P2IN & 0x20)==0)
              t=0;
          if(!(P2IN & 0x20)==1)
              t=4;
          if(!(P2IN & 0x40)==0)
              u=0;
          if(!(P2IN & 0x40)==1)
              u=8;
           x=r+s+t+u;
            P3OUT=code[x];



        }
    }
