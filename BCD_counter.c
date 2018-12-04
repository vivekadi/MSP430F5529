#include <msp430f5529.h>


/**
 * main.c
 */
void delay(long int n)
{
    volatile long int i=0;
    for (i=0;i<n;i++)
    {
    }
}

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR=0xFF;

	    P2DIR=P2DIR & ~BIT1;    // P2.1 AS INPUT
	    P2SEL=P2SEL & ~BIT1;

	    P2REN=P2REN | BIT1;     //PULLUP RESISTOR ENABLE
	    P2OUT=P2OUT |BIT1;



	while(1)
	{
	    if(P2IN & BIT1)
	    {
	    P1OUT=0X00;
	    delay(25000);
	    P1OUT=0X04;
	    delay(25000);
	    P1OUT=0X20;
	    delay(25000);
	    P1OUT=0X24;
	    delay(25000);
	    P1OUT=0x10;
	    delay(25000);
	    P1OUT=0x14;
	    delay(25000);
	    P1OUT=0x30;
	    delay(25000);
	    P1OUT=0x34;
	    delay(25000);
	    P1OUT=0x08;
	    delay(25000);
	    P1OUT=0x0C;
	    delay(25000);
	    }
	}
}
