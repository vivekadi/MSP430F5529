#include <msp430f5529.h>
int count=0;

void delay(long int n)
{
    volatile long int i=0;
    for(i=0;i<n;i++)
    {

    }
    if (!(P2IN & 0x02)) {   // If button is open(P2.1 HIGH)
                   count=count+1;
                   while((count%2)==0){
                                    P3OUT=0XFC;     //0
                                    delay(40000);
                                    P3OUT=0XDA;     //2
                                    delay(40000);
                                    P3OUT=0X66;     //4
                                    delay(40000);
                                    P3OUT=0XBE;     //6
                                    delay(40000);
                                    P3OUT=0XFE;     //8
                                    delay(40000);
                                  }
    }
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    //P1DIR |= BIT0;  // Set P1.0to output direction
    //P2REN |= BIT2;
    //P2OUT |= BIT2;
    P3DIR=0xFF;
    P2DIR |=0x00;
    P2REN |=0xFF;
    P2OUT |= 0xFF;

    while(1) {

            if (!(P2IN & 0x02)) {   // If button is open(P2.1 HIGH)
                count=count+1;

                while((count%2)==1){
                 P3OUT=0X60;     //1
                 delay(40000);
                 P3OUT=0XF2;     //3
                 delay(40000);
                 P3OUT=0XB6;     //5
                 delay(40000);
                 P3OUT=0XE0;     //7
                 delay(40000);
                 P3OUT=0XE6;     //9
                 delay(40000);
               }
            }
        }
    }

