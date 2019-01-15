#include <msp430.h>
#include <stdio.h>



void delay(long int x)
{
    volatile int i,j;
    for(i=0;i<2*x;i++)
    {

    }

}

void dot(int n)
{
    volatile int y;
    for(y=0;y<n;y++)
    {
    delay(10000);
    P1OUT=0x04;
    delay(2000);
    P1OUT=0x00;
    }

}

void dash(int m)
{
    volatile int z;
    for(z=0;z<m;z++)
    {
    delay(10000);
    P1OUT=0x04;
    delay(16000);
    P1OUT=0x00;
    }
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR =0x04;

   // P2DIR =0x00;
   // P2REN =0x02;
   // P2OUT =0x02;
    printf("Enter character");
    //   char a[5]={'h','e','l','l','o'};
    volatile int i;

    while(1)
    {
        char c= getchar();
        switch(c)
        {
            case 'a':   dot(1);
                        dash(1);
                        delay(13000);
                        break;
            case 'b':   dash(1);
                        dot(3);
                        delay(13000);
                        break;
            case 'c':   dash(1);
                        dot(1);
                        dash(1);
                        dot(1);
                        delay(13000);
                        break;
            case 'd':   dash(1);
                        dot(2);
                        delay(13000);
                        break;
            case 'e':   dot(1);
                        delay(13000);
                        break;
            case 'f':   dot(2);
                        dash(1);
                        dot(1);
                        delay(13000);
                        break;
            case 'g':   dash(2);
                        dot(1);
                        delay(13000);
                        break;
            case 'h':   dot(4);
                        delay(13000);
                        break;
            case 'i':   dot(2);
                        delay(13000);
                        break;
            case 'j':   dot(1);
                        dash(3);
                        delay(13000);
                        break;
            case 'k':   dash(1);
                        dot(1);
                        dash(1);
                        delay(13000);
                        break;
            case 'l':   dot(1);
                        dash(1);
                        dot(2);
                        delay(13000);
                        break;
            case 'm':   dash(2);
                        delay(13000);
                        break;
            case 'n':   dash(1);
                        dot(1);
                        delay(13000);
                        break;
            case 'o':   dash(3);
                        delay(13000);
                        break;
            case 'p':   dot(1);
                        dash(2);
                        dot(1);
                        delay(13000);
                        break;
            case 'q':   dash(2);
                        dot(1);
                        dash(1);
                        delay(13000);
                        break;
            case 'r':   dot(1);
                        dash(1);
                        dot(1);
                        delay(13000);
                        break;
            case 's':   dot(3);
                        delay(13000);
                        break;
            case 't':   dash(1);
                        delay(13000);
                        break;
            case 'u':   dot(2);
                        dash(1);
                        delay(13000);
                        break;
            case 'v':   dot(3);
                        dash(1);
                        delay(13000);
                        break;
            case 'w':   dot(1);
                        dash(2);
                        delay(13000);
                        break;
            case 'x':   dash(1);
                        dot(2);
                        dash(1);
                        delay(13000);
                        break;
            case 'y':   dash(1);
                        dot(1);
                        dash(2);
                        delay(13000);
                        break;
            case 'z':   dash(2);
                        dot(2);
                        delay(13000);
                        break;

            case '1':   dot(1);
                        dash(4);
                        delay(13000);
                        break;
            case '2':   dot(2);
                        dash(3);
                        delay(13000);
                        break;
            case '3':   dot(3);
                        dash(2);
                        delay(13000);
                        break;
            case '4':   dot(4);
                        dash(1);
                        delay(13000);
                        break;
            case '5':   dot(5);
                        delay(13000);
                        break;
            case '6':   dash(1);
                        dot(4);
                        delay(13000);
                        break;
            case '7':   dash(2);
                        dot(3);
                        delay(13000);
                        break;
            case '8':   dash(3);
                        dot(1);
                        delay(13000);
                        break;
            case '9':   dash(4);
                        dot(1);
                        delay(13000);
                        break;
            case '0':   dash(5);
                        delay(13000);
                        break;
            default:    delay(15000);
        }
    }
}
