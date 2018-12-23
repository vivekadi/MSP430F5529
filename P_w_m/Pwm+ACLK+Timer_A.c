#include <msp430f5529.h>

int i = 0,d=0;

void main(void)
{     WDTCTL = WDTPW|WDTHOLD;

     P1DIR |= BIT2;
     P1SEL |= BIT2;

     TA0CCR0 = 128; // PWM period
     TA0CCR1 = 0; // PWM duty cycle
     TA0CCTL1 = OUTMOD_3; // TA0CCR1 reset/set-high voltage OR set / reset choose accordingly
     TA0CTL = TASSEL_1 + MC_1 +ID_1+TAIE;// Timer A control set to SMCLK, 1MHz and count up mode MC_1
     _bis_SR_register(LPM0_bits + GIE); // Enter Low power mode 0

}


#pragma vector= TIMER0_A1_VECTOR
 __interrupt void timer(void)
 {
     TA0CTL &= ~TAIFG;
     if(d==0)
     {
         if(i<128)
             TA0CCR1=++i;
         else
             d=1;
     }

     else if(d==1)
     {
          if(i>1)
              TA0CCR1=--i;
          else
              d=0;
     }

}
