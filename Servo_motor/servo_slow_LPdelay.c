#include <msp430f5529.h>

#define MCU_CLOCK           125000
#define PWM_FREQUENCY       50      //ideally 50Hz.

#define SERVO_DEG          180     // degrees 180
#define MIN_DUTY           650     // The min duty cycle                  **** Change according to the value reqired for speed of operation
#define MAX_DUTY           2500   // The max duty cycle

const int  PWM_Period     = (MCU_CLOCK / PWM_FREQUENCY);  // PWM Period
const int PWM_Duty       = 0;                            // %

const int servo_stepval   = ( (MAX_DUTY - MIN_DUTY) / SERVO_DEG );
unsigned int servo_stepnow   = MIN_DUTY;

unsigned int servo_lut[ SERVO_DEG+1 ];


float temp;
unsigned int force=0;
int i,j = 0,d=0,delay_grab=0,angle_w=90;

void delay(long int x)
{
    volatile long int i=0;
    for (i=0;i<x;i++)
    {
    }
    return;
}

/*void delay(int x)
 {
   TB0CCR0 =x;               //capture compare reg value
   TB0CTL = TBSSEL_1 + MC_2;     // mode-2 , ACLK

   TB0R = 0;                        // TAR register update
   TB0CCTL0 = CCIE;
   while(TB0R <3600)
   {
       __bis_SR_register(LPM0_bits|GIE);  // enter LPM
       __no_operation();
   }

   TB0CTL = 0;                      // reset timer A0 control register
 }
*/

void main(void){
 WDTCTL = WDTPW|WDTHOLD; // Stop WDT

for (i=0; i<SERVO_DEG;i++)
    {
        servo_stepnow += servo_stepval;
        servo_lut[i] = servo_stepnow;
    }

 P1DIR |= BIT2; //  LED for output
 P1SEL |= BIT2; //
 TA0CCR0 = MAX_DUTY; // PWM period                                     **** this is for continuous rotation
 TA0CCR1 = PWM_Duty; // PWM duty cycle
 TA0CCTL1 = OUTMOD_7; // TA0CCR1 reset/set-high voltage

 TA0CTL = TASSEL_2 + MC_1 + TAIE ;
 // Timer A control set to SMCLK, 1MHz
 // and count up mode MC_1
 __bis_SR_register(LPM0_bits + GIE); // Enter Low power mode 0

}


#pragma vector= TIMER0_A1_VECTOR
 __interrupt void timer(void)
{
     TA0CTL &= ~TAIFG;
     if(delay_grab>4)
     {
	     if(j>angle_w)
		{
		//j=0;
		__bic_SR_register_on_exit(LPM0_bits|GIE);
		}
	     j+=1;
	     TA0CCR1 = servo_lut[j];
	     //delay(600);
	     delay_grab=0;
     }
	delay_grab+=1;
     
}
 
#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B (void)
{
  // wake on CCR0 count match

  TB0CCTL0 = 0;
  __bic_SR_register_on_exit(LPM0_bits|GIE);
}


