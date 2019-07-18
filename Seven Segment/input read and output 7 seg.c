#include <msp430f5529.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    P3DIR=0xFF;
    P6DIR=0xFF;

    P4DIR |=0x00;
    P4REN |=0xFF;
    P4OUT |=0xFF;

    P2DIR |=0x00;
    P2REN |=0xFF;
    P2OUT |= 0xFF;

    unsigned int r=0,s=0,t=0,u=0,x=0;
    unsigned int k=0,l=0,m=0,n=0,y=0;
    char code[]={0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xE6,0xEE,0x3E,0x9C,0x7A,0x9E,0x8E};
    char code1[]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x73,0x77,0x1F,0x4E,0x3D,0x4F,0x47};

    while(1)
    {
          if(!(P2IN & 0x04)==0)
              r=0;
          if(!(P2IN & 0x04)==1)
              r=1;
          if(!(P2IN & 0x10)==0)
              s=0;
          if(!(P2IN & 0x10)==1)
              s=2;
          if(!(P2IN & 0x20)==0)
              t=0;
          if(!(P2IN & 0x20)==1)
              t=4;
          if(!(P2IN & 0x40)==0)
              u=0;
          if(!(P2IN & 0x40)==1)
              u=8;
          x=r+s+t+u;
          P3OUT=code[x];            //7-Segment--I

          if(!(P4IN & 0X01)==0)
              k=0;
          if(!(P4IN & 0X01)==1)
              k=1;
          if((!P4IN & 0x02)==0)
              l=0;
          if(!(P4IN & 0X02)==1)
              l=2;
          if(!(P4IN & 0X04)==0)
              m=0;
          if(!(P4IN & 0X04)==1)
              m=4;
          if(!(P4IN & 0x08)==0)
              n=0;
          if(!(P4IN & 0x08)==1)
              n=8;
          y=k+l+m+n;
          P6OUT=code1[y];           //7-Segment--II
        }
    }
