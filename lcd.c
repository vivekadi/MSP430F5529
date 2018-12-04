#include <msp430f5529.h>
//#include <LCD.h>

void LCD_init(void);
void DelayMs(int Ms);
void LCD_cmd4(unsigned char cmd);
void LCD_dat4(unsigned char byte);

unsigned char i;
const unsigned char Msg1[] = " 16x2 LCD ";
const unsigned char Msg2[] = " F2812 ";

void main()

{

    WDTCTL = WDTPW + WDTHOLD;   //Stop watchdog timer
    P1DIR = 0x3C;   // Set P7.4-P7.7 to Output direction
    P2DIR = 0xC0;
    P4DIR = 0x08;

    DelayMs(100);

    LCD_init();
    DelayMs(50);

        while(1)

        {

            LCD_cmd4(0x80);

            for(i=0;i<16;i++)

            {

                LCD_dat4(Msg1[i]);
                DelayMs(5);

            }

            LCD_cmd4(0xc0);
            for(i=0;i<16;i++)

            {

                LCD_dat4(Msg2[i]);
                DelayMs(5);

            }

        }

}

void LCD_init(void)

{

    LCD_cmd4(0x33);
    LCD_cmd4(0x22);
    LCD_cmd4(0x22);
    LCD_cmd4(0x22);
    LCD_cmd4(0x28);

    // 28 for four bit mode
    LCD_cmd4(0x0c);
    LCD_cmd4(0x06);
    LCD_cmd4(0x01);

}

void LCD_cmd4(unsigned char cmd)

{

    P2OUT = 0x00;   // RW=0,RS=0
    P1OUT = cmd;

    P4OUT = 0x08;   // En = 1;
    P4OUT = 0x00;   // En = 0;

    cmd = (cmd<<4) & 0xF0;

    P1OUT = cmd;

    P4OUT = 0x08;// En = 1;
    P4OUT = 0x00; // En = 0;

    DelayMs(3);

}

void LCD_dat4(unsigned char byte)

{

    P2OUT = 0x80;   // RW=0,RS=0
    P1OUT = byte;

    P4OUT = 0x08;   // En = 1;
    P4OUT = 0x00;   // En = 0;

    byte = (byte<<4) & 0xF0;

    P1OUT = byte;

    P4OUT = 0x08;   // En = 1;
    P4OUT = 0x00;   // En = 0;

    DelayMs(3);

}

void DelayMs(int Ms)

{

    int i;
    while(Ms>0)
    {
        for(i=0;i<104;i++);
        Ms--;
    }

}
