#include <msp430f5529.h>
#include <stdio.h>

char c;


/**
 * main.c
*/


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR|= BIT0;
    P4DIR|= BIT7;
    P3SEL|= BIT3+BIT4;
    UCA0CTL1|= UCSWRST;
    UCA0CTL1|= UCSSEL_2;
    UCA0BR0 = 109;
    UCA0BR1 = 0;
    UCA0MCTL|= UCBRS_1 + UCBRF_0;
    UCA0CTL1&= ~UCSWRST;

    UCA0IE|=UCRXIE;



    __bis_SR_register(LPM0_bits+GIE);
    __no_operation();
    return 0;
}
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    UCA0IFG &= ~UCRXIFG;
    while((UCA0IFG)&(UCRXIFG));

    c=UCA0RXBUF;
    if(c=='a')
           {
               P4OUT &= ~BIT7;
               P1OUT |= BIT0;


           }
    else if(c == 'b')
           {
               P1OUT &= ~BIT0;
               P4OUT |= BIT7;

           }


}
