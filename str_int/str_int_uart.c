#include <msp430f5529.h>
#include <stdio.h>

char g[12],c;
unsigned int tmp2=0,tmp=0,w=0,x=0,y=0,z=0;
unsigned int array_mult = 1;
int i = 0;
unsigned int k=0,j=0;
unsigned int m=0;


void px(char g[])
{

    printf("w,x,y,z:%d,%d,%d,%d\n",w,x,y,z);
    printf("%s\n",g);

    for(i = 11, tmp2 = 0; i>-1 ; i--)
        {
          tmp2 = g[i]-'0';
          tmp2 *= array_mult;
          tmp += tmp2;
          array_mult *= 10;
          k++;

          //printf("%d",tmp);
          if (k==3)
          {
            switch(j)
            {
              case 0 : w=tmp; break;
              case 1 : x=tmp; break;
              case 2 : y=tmp; break;
              case 3 : z=tmp; break;
              default: x=y=x=100; break;
            }
            j++;

            //printf("count value is:   %d \n" ,tmp);

            tmp=0;
            k=0;
            array_mult=1;
          }
        }
        j=0;

/*     if(x>0)
     {
         P4OUT &= ~BIT7;
         P1OUT |= BIT0;
     }

     else if(z>0)
     {
         P1OUT &= ~BIT0;
         P4OUT |= BIT7;
     }
*/
}


void receive()
{
        UCA0CTL1|= UCSWRST;
        UCA0CTL1|= UCSSEL_2;
        UCA0BR0 = 109;
        UCA0BR1 = 0;
        UCA0MCTL|= UCBRS_1 + UCBRF_0;
        UCA0CTL1&= ~UCSWRST;
        UCA0IE|=UCRXIE;

        __bis_SR_register(LPM0_bits+GIE);
        __no_operation();
}


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR|= BIT0;
    P4DIR|= BIT7;
    P3SEL|= BIT3+BIT4;

    while(1)
    {
        receive();
    }

}


#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    UCA0IFG &= ~UCRXIFG;
    while((UCA0IFG)&(UCRXIFG));

    c=UCA0RXBUF;
    g[m]=c;
    m++;

    if(m>12)
   {
        px(g);
        m=0;
   }
}
