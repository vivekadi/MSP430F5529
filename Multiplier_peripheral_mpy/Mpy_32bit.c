#include <msp430.h> 
#include <stdint.h>
#include <stdio.h>

uint16_t Q16mpy(uint16_t q16arg1, uint16_t q16arg2);
uint32_t IQ32mpy(uint32_t iq32arg1, uint32_t iq32arg2);

uint16_t x,y,z;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	y=100;
	z=15;
	x=Q16mpy(y,z);
	printf("%d",x);


	return 0;
}

uint16_t Q16mpy(uint16_t q15Arg1, uint16_t q15Arg2)
{
    uint16_t ui16Result;
    uint16_t ui16IntState;
    uint16_t ui16MPYState;

    ui16IntState = __get_interrupt_state();   // Disable interrupt and save multiplier mode
    __disable_interrupt();
    ui16MPYState = MPY32CTL0;

    //MPY32CTL0 = MPYFRAC;  fractional mode.

    MPY = q16arg1; //Perform multiplication and result
    OP2 = q16arg2;
   // __delay_cycles(3); //Delay for the result to be ready

    ui16Result = RESLO; //result

    MPY32CTL0 = ui16MPYState; //Restore multiplier mode and interrupts
    __set_interrupt_state(ui16IntState);
    return (uint16_t)ui16Result;
}


uint32_t  IQ32mpy(uint32_t iq32arg1, uint32_t iq32arg2)
{
    uint32_t ui32Result;
    uint16_t ui16IntState;
    uint16_t ui16MPYState;
    /* Disable interrupts and save multiplier mode. [optional] */
    ui16IntState = __get_interrupt_state();
    __disable_interrupt();
    ui16MPYState = MPY32CTL0;
    /* Set the multiplier to fractional mode. */
    MPY32CTL0 = MPYFRAC;
    /* Perform multiplication and save result. */
    MPYS32L = iq32arg1;
    MPYS32H = iq32arg1 >> 16;
    OP2L = iq31Arg2;
    OP2H = iq31Arg2 >> 16;
    __delay_cycles(5); //Delay for the result to be ready
    ui32Result = RES2;
    ui32Result |= (uint32_t)RES3 << 16;


    /* Restore multiplier mode and interrupts. [optional] */
    MPY32CTL0 = ui16MPYState;
    __set_interrupt_state(ui16IntState);
    return (uint32_t)ui32Result;
}
