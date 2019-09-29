#include "msp430f5529.h"
#include "stdio.h"



#define MCU_CLOCK           1000000
#define PWM_FREQUENCY       46      //ideally 50Hz.

#define SERVO_DEG         180     // degrees 180
#define MIN_DUTY           750     // The min duty cycle
#define MAX_DUTY           2550    // The max duty cycle

const int  PWM_Period     = (MCU_CLOCK / PWM_FREQUENCY);  // PWM Period
const int PWM_Duty       = 0;                            // %

unsigned int k,j,w,x,y,z;
unsigned int servo_lut[ SERVO_DEG+1 ];


void delay(int x)
 {
   TB0CCR0 =x;               //capture compare reg value
   TB0CTL = TBSSEL_1 + MC_2;     // mode-2 , ACLK

   TB0R = 0;                        // TAR register update
   TB0CCTL0 = CCIE;
   while(TB0R <5000)
   {
       __bis_SR_register(LPM0_bits|GIE);  // enter LPM
       __no_operation();
   }

   TB0CTL = 0;                      // reset timer A0 control register
 }

void deg_1(unsigned int x,unsigned int y)
{
    TA0CCR2=servo_lut[x+y/4];
    delay(5000);
    TA0CCR2=servo_lut[x+3*y/4];
    delay(5000);
    TA0CCR2=servo_lut[x+y];
    delay(5000);
}

void deg_2(unsigned int z,unsigned int w)
{
    TA0CCR1=servo_lut[z+w/4];
    delay(5000);
    TA0CCR1=servo_lut[z+3*w/4];
    delay(5000);
    TA0CCR1=servo_lut[z+w];
    delay(5000);
}



void main (void)
{
    unsigned int i;

    // Calculate the step value
    const int servo_stepval   = ( (MAX_DUTY - MIN_DUTY) / SERVO_DEG );
    unsigned int servo_stepnow   = MIN_DUTY;

    // Fill up the LUT
    for (i=0; i<SERVO_DEG;i++)
    {
        servo_stepnow += servo_stepval;
        servo_lut[i] = servo_stepnow;
    }


    WDTCTL  = WDTPW + WDTHOLD;     // Kill watchdog timer

    TA0CCTL1 = OUTMOD_7;            // TACCR1 reset/set
    TA0CCTL2 = OUTMOD_7;            // TACCR1 reset/set
    TA0CTL   = TASSEL_2 + MC_1;     // SMCLK, upmode
    TA0CCR0  = PWM_Period-1;        // PWM Period
    TA0CCR1  = PWM_Duty;            // TACCR1 PWM Duty Cycle
    TA0CCR2  = PWM_Duty;
    P1DIR   =0x0C;               // P1.2 = output
    P1SEL   =0x0C;               // P1.2 = TA1 output

    // Main loop
    while (1)
    {

       printf("Enter degree");
       scanf("%d,%d",&j,&k);
       y=j-x;
       w=k-z;

       if(j>120)
       {
           deg_1(x,y);
           x=j;

       }

       else
       {
           TA0CCR2=servo_lut[j];
           delay(24000);
           x=j;
       }



       if(k>120)
       {
           deg_2(z,w);
           z=k;
       }
       else
       {
           TA0CCR1=servo_lut[k];
           delay(24000);
           z=k;
       }



/*
        //0°
        TA0CCR1 = servo_lut[0];
        delay(27000);

        //45°
        TA0CCR1 = servo_lut[45];
        delay(27000);

        //90°
        TA0CCR1 = servo_lut[90];
        delay(27000);

        //180°
        TA0CCR1 = servo_lut[135];
        delay(27000);

        TA0CCR1 = servo_lut[179];
        delay(32000);
*/

   }

}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B (void)
{
  // wake on CCR0 count match

  TB0CCTL0 = 0;
  __bic_SR_register_on_exit(LPM0_bits|GIE);
}

