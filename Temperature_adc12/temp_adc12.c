#include <msp430f5529.h>
#include<stdio.h>

unsigned int value_adc=0,i=0;
float temp;

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Sampling time, ADC12 enable
  ADC12CTL1 = ADC12SHP;                     // sampling timer
  ADC12IE = 0x01;                           // Enable interrupt
  ADC12CTL0 |= ADC12ENC;
  P6SEL |= 0x01;                            // P6.0 ADC
  P1DIR |= 0x01;                            // P1.0 output


  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start sampling
    value_adc=ADC12MEM0;
    temp=(value_adc-20)/10;
    printf("%0.2f\n",temp);

    /*if(value_adc>=4000)
      P1OUT |= BIT0;
    else
      P1OUT &= ~BIT0;
      */

    for(i=0;i<60000;i++);
  }

}
