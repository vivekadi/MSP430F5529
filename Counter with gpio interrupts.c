#include <msp430f5529.h>
#include<msp430.h>
void delay(long int n)
{
    volatile long int k;
    for(k=0;k<n;k++)
    {
    }
}
int i ;
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR=0XFF;
    P4DIR |=BIT7 ;
    P2DIR=0x00;
    P2REN=0x02;
    P2OUT=0x02;
    P2IE |=BIT1 ;
    P2IES |=BIT1 ;
    P2IFG &= ~BIT1 ;
    _BIS_SR(GIE) ;

    while(1)
    {


           P1OUT=0X00;
           delay(25000);
           P1OUT=0X04;
           delay(25000);
           P1OUT=0X20 ;
           delay(25000);
           P1OUT=0X24 ;
           delay(25000);
           P1OUT=0X10 ;
           delay(25000);
           P1OUT=0X14 ;
           delay(25000);
           P1OUT=0x30 ;
           delay(25000);
           P1OUT=0X34 ;
           delay(25000);
           P1OUT=0X08 ;
           delay(25000);
           P1OUT=0X0C ;
           delay(25000);
                     P1OUT=0X0C;
                     delay(25000);
                     P1OUT=0X08;
                     delay(25000);
                     P1OUT=0X34 ;
                     delay(25000);
                     P1OUT=0X30 ;
                     delay(25000);
                     P1OUT=0X14 ;
                     delay(25000);
                     P1OUT=0X10 ;
                     delay(25000);
                     P1OUT=0x24 ;
                     delay(25000);
                     P1OUT=0X20 ;
                     delay(25000);
                     P1OUT=0X04 ;
                     delay(25000);
                     P1OUT=0X00 ;
                     delay(25000);
    }
}
#pragma vector=PORT2_VECTOR
__interrupt void port_2(void)
{
    P4OUT &=~BIT7 ;
    P2IFG &=~BIT1 ;

    for(i=0;i<3;i++)
        {
            P4OUT |=BIT7 ;
            __delay_cycles(1048576);
            P4OUT &=~BIT7 ;
            __delay_cycles(1048476) ;
        }
}

********************************************* updowncounter with interrupt**************************************




#include <msp430f5529.h>
#include<msp430.h>
void delay(long int n)
{
    volatile long int k;
    for(k=0;k<n;k++)
    {
    }
}
int i ;
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR=0XFF;
    P4DIR |=BIT7 ;
    P2DIR=0x00;
    P2REN=0x02;
    P2OUT=0x02;
    P2IE |=BIT1 ;
    P2IES |=BIT1 ;
    P2IFG &= ~BIT1 ;
    _BIS_SR(GIE) ;

    while(1)
    {

           P1OUT=0X00;
           delay(25000);
           P1OUT=0X04;
           delay(25000);
           P1OUT=0X20 ;
           delay(25000);
           P1OUT=0X24 ;
           delay(25000);
           P1OUT=0X10 ;
           delay(25000);
           P1OUT=0X14 ;
           delay(25000);
           P1OUT=0x30 ;
           delay(25000);
           P1OUT=0X34 ;
           delay(25000);
           P1OUT=0X08 ;
           delay(25000);
           P1OUT=0X0C ;
           delay(25000);

    }
}
#pragma vector=PORT2_VECTOR
__interrupt void port_2(void)
{
    P4OUT &=~BIT7 ;
    P2IFG &=~BIT1 ;

    for(i=0;i<3;i++)
        {
            P4OUT |=BIT7 ;
            __delay_cycles(1048576);
            P4OUT &=~BIT7 ;
            __delay_cycles(1048476) ;
        }
}
***********************************************counter with interrupt*********************************

