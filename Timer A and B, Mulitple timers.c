#include <msp430.h>
#define delay 1000
#define delay1 1500
unsigned int x=0,y=0;

void main(void)
{
    while(1)
    {
WDTCTL = WDTPW + WDTHOLD; // Stop WDT
P1DIR =0x01; // P1.0 output
P4DIR=0x80;

TA0CCTL0 = CCIE; // CCR0 interrupt enabled
TA0CCR0 = 1000-1;
TA0CTL = TASSEL_2 + MC_1; // SMCLK, contmode

TB0CCTL0 = CCIE; // CCR0 interrupt enabled
TB0CCR0 = 2000-1;
TB0CTL = TBSSEL_2 + MC_1; // SMCLK, contmode

_BIS_SR(LPM0_bits + GIE); // Enter LPM0 w/ interrupt


}
}

// Timer A0 interrupt service routine

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
    x++;
    if(x>delay)
    {
P1OUT ^= 0x01;

x=0;
}
}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B0 (void)
{
    y++;
    if(y>delay1)
    {
P4OUT ^= 0x80;

y=0;
}
}

