#include "msp430f5529.h"

#define MCU_CLOCK           1000000
#define PWM_FREQUENCY       46      //ideally 50Hz.

#define SERVO_DEG         180     // degrees 180
#define MIN_DUTY           650     // The min duty cycle
#define MAX_DUTY           2700    // The max duty cycle

const int  PWM_Period     = (MCU_CLOCK / PWM_FREQUENCY);  // PWM Period
const int PWM_Duty       = 0;                            // %

float temp;


void delay(int x)
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


void main (void)
{

        P7DIR |= 0xFF;
        P7OUT |= 0x00;

        P8DIR |= 0xFF;
        P8OUT |= 0x00;

        P4DIR |= 0xFF;
        P4OUT |= 0x00;

        P5DIR |= 0xFF;
        P5OUT |= 0x00;

        P2DIR |= 0xFF;
        P2OUT |= 0x00;

        P6DIR |= 0xFF;
        P6OUT |= 0x00;

        P3DIR |= 0xFF;
        P3OUT |= 0x00;


    //unsigned int servo_lut[ SERVO_DEG+1 ];
   // unsigned int i;

    // Calculate the step value
    const int servo_stepval   = ( (MAX_DUTY - MIN_DUTY) / SERVO_DEG );
    const int servo_stepnow   = MIN_DUTY;

    /* Fill up the LUT
    for (i=0; i<SERVO_DEG;i++)
    {
        servo_stepnow += servo_stepval;
        servo_lut[i] = servo_stepnow;
    }*/

    // Setup the PWM, etc.
    WDTCTL  = WDTPW + WDTHOLD;     // Kill watchdog timer
    TA0CCTL1 = OUTMOD_7;            // TACCR1 reset/set
    TA0CTL   = TASSEL_2 + MC_1;     // SMCLK, upmode
    TA0CCR0  = PWM_Period-1;        // PWM Period
    TA0CCR1  = PWM_Duty;            // TACCR1 PWM Duty Cycle
    P1DIR   |= BIT2;               // P1.2 = output
    P1SEL   |= BIT2;               // P1.2 = TA1 output

  ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Sampling time, ADC12 enable
  ADC12CTL1 = ADC12SHP;                     // sampling timer
  ADC12IE = 0x01;                           // Enable interrupt
  ADC12CTL0 |= ADC12ENC;
  P6SEL |= 0x01;                            // P6.0 ADC

    // Main loop
    while (1)
    {

	ADC12CTL0 |= ADC12SC;                   // Start sampling
    	temp=ADC12MEM0;
    	

        //0°
        TA0CCR1 = servo_stepnow+servo_stepval*1;
        delay(24000);

        //45°
        TA0CCR1 = servo_stepnow+servo_stepval*45;
        delay(24000);

        //90°
        TA0CCR1 = servo_stepnow+servo_stepval*90;
        delay(24000);

        //180°
        TA0CCR1 = servo_stepnow+servo_stepval*179;
        delay(24000);

   }

}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B (void)
{
  // wake on CCR0 count match

  TB0CCTL0 = 0;
  __bic_SR_register_on_exit(LPM0_bits|GIE);
}

