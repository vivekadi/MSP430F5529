#include <msp430.h> 



/**
 * main.c
 */
void delay(long int x)
{
    volatile long int i=0;
    for (i=0;i<x;i++)
    {
    }
    return;
}


void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR=0x01;
	while(1)
	{
            P1OUT=0x00;
            delay(25000)
            P1OUT=0x01;
            delay(25000);
	}
}
	

