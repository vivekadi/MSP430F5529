#include <msp430f5529.h>

int i =0,j=0,k=0,m=0,d=0,e=0,f=0,g=0;

void main(void)
{
     WDTCTL = WDTPW|WDTHOLD;

     P1DIR =0x0C; // pin P2.4 for timer output
     P1SEL =0x0C;   // to select timer from mux


     P2DIR =0x30; // pin P2.4 for timer output
     P2SEL =0x30;   // to select timer from mux

     TA0CCR0 = 128; // PWM period
     TA0CCR1 = 1; // PWM duty cycle
     TA0CCR2 = 0;
     TA0CCTL1 = OUTMOD_3; // TA0CCR1 reset/set-high voltage OR set / reset choose accordingly
     TA0CCTL2 = OUTMOD_3;
     TA0CTL = TASSEL_1 + MC_1 +ID_1+TAIE;// Timer A control set to SMCLK, 1MHz and count up mode MC_1

     TA2CCR0 = 384; // PWM period
     TA2CCR1 = 1; // PWM duty cycle
     TA2CCR2 = 0;
     TA2CCTL1 = OUTMOD_3; // TA0CCR1 reset/set-high voltage OR set / reset choose accordingly
     TA2CCTL2 = OUTMOD_3;
     TA2CTL = TASSEL_1 + MC_1 +ID_1+TAIE;// Timer A control set to SMCLK, 1MHz and count up mode MC_1

     _bis_SR_register(LPM0_bits + GIE); // Enter Low power mode 0

}



#pragma vector= TIMER0_A1_VECTOR // P1.2 connected to timer(0.1)
 __interrupt void timer_a1(void)
 {
     TA0CTL &= ~TAIFG;
     if(d==0)
     {
         if(i<128)
             TA0CCR1=++i;

         else
             d=1;
     }

     if(d==1)
     {
          if(i>1)
              TA0CCR1=--i;
          else
              d=0;
     }

     if(f==0)
     {
         if(k<256)
             TA0CCR2=++k;
         else
             f=1;

     }
     if(f==1)
     {
         if(k>1)
             TA0CCR2=--k;
         else
             f=0;
     }
}


#pragma vector= TIMER2_A1_VECTOR  // P2.4 connected to timer (2.1)
 __interrupt void timer_a2(void)
 {
     TA2CTL &= ~TAIFG;
     if(e==0)
     {
         if(j<384)
             TA2CCR1=++j;
         else
             e=1;
     }

     if(e==1)
     {
          if(j>128)
              TA2CCR1=--j;
          else
              e=0;
     }

     if(g==0)
     {
         if(m<512)
             TA2CCR2=++m;
         else
             g=1;
     }
     if(g==1)
     {
         if(m>1)
             TA2CCR2=--m;
         else
             g=0;
     }

}


