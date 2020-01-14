#include <msp430f5529.h>
#include<stdio.h>

unsigned int force=0,i=0;

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
    force=ADC12MEM0;
    printf("%d\n",force);

   // for(i=0;i<60000;i++);


    if(force>=3880)    //This value depends on the input voltage and shunt resistance
      P1OUT |= BIT0;
    else
      P1OUT &= ~BIT0;

  }

}




