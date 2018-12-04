#include <msp430f5529.h>
int i;
int main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
P1DIR |= BIT0; // Set P1.0 to output direction
P4DIR |= BIT7;
P1REN |=BIT1;
P1OUT |=BIT1;
P1IE |= BIT1; // P1.1 interrupt enabled
P1IES |= BIT1; // P1.1 Hi/lo edge
P1IFG &= ~BIT1; // P1.1 IFG cleared
_BIS_SR(GIE); // Enter LPM4 w/interrupt
while(1)
{
 P4OUT |=BIT7;
 __delay_cycles(1045876);
 P4OUT &=~BIT7;
    __delay_cycles(1045876);
}


}
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
 P1OUT &=~BIT0; // P1.0 = toggle
 P1IFG &= ~BIT1; // P1.4 IFG cleared

 for(i=0;i<3;i++)
 {
P1OUT |= BIT0; // P1.0 = toggle
 __delay_cycles(1048576);
 P1OUT &=~BIT0; // P1.0 = toggle
  __delay_cycles(1048576);

 }
}
