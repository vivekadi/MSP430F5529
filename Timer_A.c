#include <msp430.h>
#define delay 1000
unsigned int x=0;

void main(void)
{
    while(1)
    {
WDTCTL = WDTPW + WDTHOLD; // Stop WDT
P1DIR =0xFF; // P1.0 output
//P4DIR=0x80;
//P4OUT=0x80;
TA0CCTL0 = CCIE; // CCR0 interrupt enabled
TA0CCR0 = 1000-1;
TA0CTL = TASSEL_2 + MC_1; // SMCLK, contmode
_BIS_SR(LPM0_bits + GIE); // Enter LPM0 w/ interrupt
}
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    x++;
    if(x>delay)
    {
P1OUT ^= 0x01;
//P4OUT ^=0x80;
x=0;// Toggle P1.0
}
}
