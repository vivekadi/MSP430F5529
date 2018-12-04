#include <msp430.h> 
#define delay 1000

char code[]={0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xE6};
char code1[]={0x7E,0x30,0x6D,0x79,0x33,0x5B};
char code2[]={0X00,0X04,0X08,0X0C,0x10,0x14,0x18,0x1C,0x20,0x24,0x28,0x2C,0x30,0x34,0x38,0x3C};

volatile unsigned int x=0,y=0,z=0;
volatile unsigned int v=0;

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
{2
    P2IFG &=~BIT1 ;

    x=0;
    y=0;
    P3OUT=code[x];
    P6OUT=code1[y];
    v++;
    P1OUT=code2[v];

}

