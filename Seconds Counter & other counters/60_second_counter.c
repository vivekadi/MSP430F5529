#include <msp430.h> 


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
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P3DIR=0xFF;
    P6DIR=0xFF;

    unsigned int x,y;

     char code[]={0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xE6};
     char code1[]={0x7E,0x30,0x6D,0x79,0x33,0x5B};

     while(1)
     {
         for(x=0;x<6;x++)
         {
             P6OUT=code1[x];
             for(y=0;y<10;y++)
             {
                 P3OUT=code[y];
                 delay(53000);
             }
         }
     }

}
