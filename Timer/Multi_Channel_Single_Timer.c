#include <msp430.h>

void main(void)
{

WDTCTL = WDTPW |WDTHOLD; // Stop WDT

P1DIR =0x0C; // P1.0 output
P1SEL=0x0C;


TA0CCR0= 65534;
TA0CCR1 = 25000;    //1sec (0.5+0.5)
TA0CCR2 = 64000;    //

TA0CCTL1 = OUTMOD_7; // CCR0 interrupt enabled
TA0CCTL2 = OUTMOD_7; // CCR0 interrupt enabled
TA0CTL = TASSEL_2 + MC_3+ID_3+TAIE+TACLR; // SMCLK, countmode

_BIS_SR(LPM0_bits+GIE); // Enter LPM0 w/ interrupt

}

