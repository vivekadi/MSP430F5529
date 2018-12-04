#include <msp430f5529.h>


int i = 0;
void main(void){
 WDTCTL = WDTPW|WDTHOLD; // Stop WDT
 P1DIR |= BIT2; //  LED for output
 P1SEL |= BIT2; //
 TA0CCR0 = 512; // PWM period
 TA0CCR1 = 0; // PWM duty cycle
 TA0CCTL1 = OUTMOD_7; // TA0CCR1 reset/set-high voltage

 TA0CTL = TASSEL_2 + MC_1 + TAIE +ID_3;
 // Timer A control set to SMCLK, 1MHz
 // and count up mode MC_1
 _bis_SR_register(LPM0_bits + GIE); // Enter Low power mode 0

}
#pragma vector= TIMER0_A1_VECTOR //
 __interrupt void timer(void) {
 TA0CTL &= ~TAIFG;          //to keep track of timer count
 if(i<512)
 TA0CCR1 = ++i;
 else
 i=0;
}
