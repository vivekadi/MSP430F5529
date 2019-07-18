#include <msp430.h> 
#define delay 1000

char code[]={0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xE6};
char code1[]={0x7E,0x30,0x6D,0x79,0x33,0x5B};


volatile unsigned int x=0,y=0,z=0;
volatile unsigned int v=0,i=0;

/**
 * main.c
 */


void main()
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P7DIR |= 0xFF;
    P7OUT |= 0x00;

    P8DIR |= 0xFF;
    P8OUT |= 0x00;

    P4DIR |= 0xFF;
    P4OUT |= 0x00;

    P5DIR |= 0xFF;
    P5OUT |= 0x00;

    P1DIR=0xFF;
    P3DIR=0xFF;
    P6DIR=0xFF;

    P2DIR=0x00;
    P2REN=0x02;
    P2OUT=0x02;
    P2IE |=BIT1 ;
    P2IES |=BIT1 ;
    P2IFG &= ~BIT1 ;

    TA0CCTL0=CCIE;
    TA0CCR0=999;
    TA0CTL = TASSEL_2 + MC_1;
    _BIS_SR(LPM0_bits+GIE);

}
     // Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{

  z++;
  if(z>delay)
  {
      P3OUT=code[x];
      P6OUT=code1[y];
      x++;
      if(x==10)
      {
          x=0;
          y++;
      }

      if(y==6)
          y=0;
      z=0;
  }

}


#pragma vector=PORT2_VECTOR
__interrupt void port_2(void)
{
    P2IFG &=~BIT1 ;

    x=0;
    y=0;
    P3OUT=code[x];
    P6OUT=code1[y];
    v++;

   for(i=0;i<v;i++)
   {
   P1OUT |= BIT0; // P1.0 = toggle
    __delay_cycles(1048576);
    P1OUT &=~BIT0; // P1.0 = toggle
     __delay_cycles(1048576);
   }


}

