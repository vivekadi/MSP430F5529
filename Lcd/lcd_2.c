

/* uC and LCD Connections
    TP1 - Vcc (+5v)
    TP3 - Vss (Gnd)
    P1.0 - D4
    P1.1 - D5
    P1.2 - D6
    P1.3 - D7
    P1.4 - EN
    P1.5 - RS
    Gnd  - RW
    Gnd  - Vee through 1K Resistor  - this value determines contrast - i.e. direct connection to Gnd means all dots displayed
    Gnd  - K (LED-)
    Vcc  - A (LED+) +5V
    Clock: 1MHz             */

#include <msp430f5529.h>


#define lcd_port        P1OUT
#define lcd_enable      P2OUT
#define lcd_port_dir    P1DIR
#define lcd_enable_dir  P2DIR

#define LCD_EN      BIT4
#define LCD_RS      BIT5

void lcd_reset()
{
    lcd_port_dir = 0xff;
    lcd_enable_dir = 0xff;    // output mode
    lcd_port = 0xff;
    lcd_enable=0xff;
    __delay_cycles(20000);
    lcd_enable = 0x00+LCD_EN;
    lcd_port = 0x0C;
    __delay_cycles(10000);
    lcd_enable = 0x00+LCD_EN;
    lcd_port = 0x0C;
    __delay_cycles(1000);
    lcd_enable = 0x00+LCD_EN;
    lcd_port = 0x0C;
    __delay_cycles(1000);
    lcd_enable = 0x00+LCD_EN;
    lcd_port = 0x08;
    __delay_cycles(1000);
}

void lcd_cmd (char cmd)
{
    // Send upper nibble
    lcd_enable |= LCD_EN;
    lcd_port = ((cmd >> 4) & 0x3C);

    // Send lower nibble
    lcd_enable |= LCD_EN;
    lcd_port = (cmd & 0x3C);

    __delay_cycles(4000);
}

void lcd_init ()
{
    lcd_reset();         // Call LCD reset
    lcd_cmd(0x28);       // 4-bit mode - 2 line - 5x7 font.
    lcd_cmd(0x0C);       // Display no cursor - no blink.
    lcd_cmd(0x06);       // Automatic Increment - No Display shift.
    lcd_cmd(0x80);       // Address DDRAM with 0 offset 80h.
    lcd_cmd(0x01);       // Clear screen
}


void lcd_data (unsigned char dat)
{
    // Send upper nibble
    lcd_port = ((dat >> 4) & 0x3C);
    lcd_enable |= LCD_EN|LCD_RS;
    lcd_port = ((dat >> 4) & 0x3C);
    lcd_enable |=LCD_RS;

    // Send lower nibble
    lcd_port = (dat & 0x3C);
    lcd_enable |= LCD_EN|LCD_RS;
    lcd_port = (dat & 0x3C);
    lcd_enable |=LCD_RS;

    __delay_cycles(4000); // a small delay may result in missing char display
}

void display_line(char *line)
{
    while (*line)
        lcd_data(*line++);
}

int main()
{
    // Stop Watch Dog Timer
    WDTCTL = WDTPW + WDTHOLD;

    // Initialize LCD
    lcd_init();

    lcd_cmd(0x80); // select 1st line (0x80 + addr) - here addr = 0x00
    display_line("Black God");
    lcd_cmd(0xc0); // select 2nd line (0x80 + addr) - here addr = 0x40
    display_line("Bits & Bytes");

    while (1);
}
