#include <msp430f5529.h>


/**
 * main.c
 */
void delay(long int n)
{
    volatile long int i=0;
    for(i=0;i<n;i++)
    {

    }
}

void main()
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P3DIR=0XFF;
	
	while(1)
	{
	    P3OUT=0XFC;     //0
	    delay(20000);
	    P3OUT=0X60;     //1
	    delay(20000);
	    P3OUT=0XDA;     //2
	    delay(20000);
	    P3OUT=0XF2;     //3
	    delay(20000);
	    P3OUT=0X66;     //4
	    delay(20000);
	    P3OUT=0XB6;     //5
	    delay(20000);
	    P3OUT=0XBE;     //6
	    delay(20000);
	    P3OUT=0XE0;     //7
	    delay(20000);
	    P3OUT=0XFE;     //8
	    delay(20000);
	    P3OUT=0XE6;     //9
	    delay(20000);
	    P3OUT=0XEE;     //A
	    delay(20000);
	    P3OUT=0X3E;     //B
	    delay(20000);
	    P3OUT=0X9C;     //C
	    delay(20000);
	    P3OUT=0X7A;     //D
	    delay(20000);
	    P3OUT=0X9E;     //E
	    delay(20000);
	    P3OUT=0X8E;     //F
	    delay(20000);


	}

}
