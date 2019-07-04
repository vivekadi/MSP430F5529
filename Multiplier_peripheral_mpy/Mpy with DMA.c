#include <msp430.h> 
#include<stdint.h>
#include<stdio.h>


//#include "driverlib.h"

int8_t a[128] = {3,8,-1,7,9,12,3,10,13,11,4,10,2,12,10,2,-3,7,11,13,4,7,8,7,9,6,9,7,2,7,6,-2,9,0,13,3,5,11,-6,12,5,8,3,11,11,10,1,9,11,1,9,4,7,1,7,-2,7,11,14,11,3,9,5,8,9,9,-3,7,8,12,9,11,10,9,9,13,10,7,3,-5,11,12,11,7,7,4,2,9,2,6,12,9,7,9,9,7,8,4,9,6,7,6,7,11,9,9,3,12,0,11,1,9,8,10,8,2,9,9,1,5,3,13,5,8,-1,9,12,10};

int8_t beta[640]={-9,-4,-8,4,5,8,8,5,-9,-9,-9,-8,7,5,7,1,-4,2,1,4,8,8,8,-6,-8,8,-2,-2,8,3,-6,-9,-5,2,2,-3,-3,-1,7,3,7,7,-9,4,1,2,-1,-2,-3,-8,-8,-6,3,0,-9,2,3,0,-5,9,8,-6,-9,3,4,9,-8,9,-8,-9,2,-2,-8,-9,2,4,6,0,9,-2,-6,7,2,-9,-4,-6,-7,-3,1,-8,-1,1,5,-1,3,4,5,9,4,-1,-1,-8,-9,5,6,5,-3,7,9,-9,6,3,-6,-6,-2,6,-4,2,9,-7,5,9,0,-3,-2,-1,-5,6,8,6,-5,3,9,6,-4,8,-3,7,-5,1,4,-6,0,3,-3,-7,3,1,-5,-9,7,-6,4,8,-7,-1,-8,-9,2,8,6,4,-3,5,9,-9,-7,8,-9,7,2,7,-8,-9,-2,4,0,7,9,7,-2,8,5,9,6,0,-6,-3,-4,0,5,-6,8,9,6,-3,-9,1,-6,-2,9,1,6,6,2,-7,-3,-5,9,2,-5,-4,-4,6,-4,-2,-6,-8,8,1,-7,0,-2,7,7,-9,0,0,0,-8,8,1,-6,1,-1,-4,-6,-8,-6,2,-6,8,0,5,9,1,6,4,4,2,4,5,-9,8,-7,-7,-5,8,6,4,3,0,-4,-7,4,4,1,-5,7,6,-4,-5,-7,9,-9,-2,7,9,1,8,-1,8,0,-5,9,1,-4,7,-8,3,9,-2,-7,-1,9,6,-2,-8,-8,2,9,-7,-5,9,0,3,-4,-3,-8,-2,3,3,7,0,-4,-2,-1,9,-7,8,-3,0,1,7,0,-2,0,-8,4,-6,8,7,7,-5,-1,-3,-3,-2,5,9,-4,-4,6,9,5,4,-9,1,-4,0,-7,0,4,-3,0,2,-5,9,5,2,5,5,1,-6,0,-8,-2,7,-1,-9,-5,8,-6,4,4,-5,-1,4,7,5,0,0,3,6,6,8,-1,2,6,3,0,-5,5,8,-5,6,0,-4,2,2,5,-6,5,2,0,2,-9,-7,7,-8,2,-5,-6,7,-4,-8,-8,-2,-9,-2,5,-1,-2,4,1,3,3,8,2,0,3,-4,4,-6,2,4,-3,-7,3,5,-2,5,-8,3,-6,0,2,3,5,6,9,-8,4,-4,-9,2,-8,-3,1,-6,-9,-4,-3,-1,-6,-1,3,-7,-6,-7,-2,2,-5,-1,-4,9,-5,-3,-3,4,8,9,3,-1,4,-1,4,2,5,2,-8,-9,-5,7,4,3,-9,-8,-8,-4,0,0,6,1,4,-9,8,-5,4,-4,6,-7,-5,-3,0,-8,4,-5,-5,-9,3,2,-1,-1,0,-1,0,9,-2,-5,6,-9,4,0,-7,2,6,-8,6,8,-8,-3,1,3,-9,-5,1,-5,8,-1,5,-6,-4,8,0,-1,-2,-6,-9,-2,0,7,-2,3,9,5,-8,-5,5,-6,0,6,7,-9,-1,4,-1,2,7,1,-5,9,9,5,-9,5,-6,4,2,1,-6,-8,-3,-8,-2,5,-4,-4,-2,-4,8,-7,-3,7,0,-8,4,9,-2,9,2,7,-3,0,2,-1,-8,-7,-9,-1,-1,-6,-5,1,-7,-9,-9,-5,7,1,7,1,8,-6,1,-5,4,-4,-7,-2};


uint16_t hid_dim = 128;

uint8_t outputDim = 5;

void MACS_8X8(int8_t *pHidden, int8_t *pWeight, int16_t *pOutput, uint16_t hiddenDimenson, uint8_t outputDimenson);
void initDMAsforMPY8X8(uint16_t inputVectDimenson, int8_t *pInput, int8_t *pWeight, int16_t *pOutput);

int16_t g[5];

int main(void)

{

        WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

        MACS_8X8(a,beta,g,hid_dim,outputDim); //operand 1, operand 2, result,no.of.rows in operand 2, no.of.elements in result

}



void MACS_8X8(int8_t *pHidden, int8_t *pWeight, int16_t *pOutput, uint16_t hiddenDimenson, uint8_t outputDimenson)

{
    initDMAsforMPY8X8(hiddenDimenson, pHidden, pWeight, pOutput);

    uint16_t i;

    for (i=0; i<outputDimenson; i++)

    {

//        pOutput += 1;   // results is 16-bit, uint16_t type ptr needs to increase by 1


//        __data16_write_addr((unsigned short) &DMA2DA,(unsigned long) pOutput);

        __data16_write_addr((unsigned short) &DMA0SA, (unsigned long) pWeight);

        pWeight += hiddenDimenson;


        // restart DMA

        RESHI=0;

        RESLO=0;

        MACS_L=0x00;

        DMA1CTL &= ~DMAIFG;

        DMA0CTL |= DMAEN;   // enable DMA channel 0

        DMA1CTL |= DMAEN;   // enable DMA channel 1

//        DMA2CTL |= DMAEN;   // enable DMA channel 2

        OP2 = 0x00;     // start MACS to get first DMA trigger


        while(!(DMA1CTL & DMAIFG)); //could go into LPM0 and add DMA interrupt for ch 1 IFG.
        *pOutput++ = RESLO;

        printf("%d",pOutput);
        __no_operation();


    }




}


void initDMAsforMPY8X8(uint16_t inputVectDimenson, int8_t *pInput, int8_t *pWeight, int16_t *pOutput)

{

    // DMA channel 0: from pWeight (increment) to &MAC, single transfer per trigger, byte transfer

    // triggered by DMA_TRIGGERSOURCE_29 (MPY ready signal), totaly transfer inputVectDimenson times

    DMACTL0 = DMA0TSEL_29;                    // MPY ready signal triggered

    DMA0CTL = DMADT_0+DMASRCINCR_3+DMADSTBYTE+DMASRCBYTE; // Single tranfer (DMADT_0), inc src (DMASRCINCR_3), Interrupt disenabled

                                                // unchange dst (DMADSTINCR_0), byte to byte, rising edge trigger (default)

    DMA0SZ = inputVectDimenson;                 // transfer size

    __data16_write_addr((unsigned short) &DMA0SA, (unsigned long) pWeight); // Source address

    __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) &MACS);    // Destination address


    // DMA channel 1: from pInput (increment) to &OP2, single transfer per trigger

    // triggered by DMA_TRIGGERSOURCE_29 (MPY ready signal), totaly transfer inputVectDimenson times

    DMACTL0 |= DMA1TSEL_29;                    // MPY ready signal triggered for channel 1

    DMA1CTL = DMADT_0+DMASRCINCR_3+DMADSTBYTE+DMASRCBYTE; // Single tranfer (DMADT_0), inc src (DMASRCINCR_3), Interrupt disenabled

                                                // unchange dst (DMADSTINCR_0), byte to byte, rising edge trigger (default)

    DMA1SZ = inputVectDimenson;                 // transfer size

    __data16_write_addr((unsigned short) &DMA1SA, (unsigned long) pInput);  // Source address

    __data16_write_addr((unsigned short) &DMA1DA,(unsigned long) &OP2); // Destination address


    // DMA channel 2: from &RESLO (increment) to pOutput (increment), 2 transfers (DMA_TRANSFER_BLOCK, with size of 2)

    // triggered by DMA_TRIGGERSOURCE_30 (DMA1IFG signal)

//    DMACTL1 |= DMA2TSEL_30;                    // MPY ready signal triggered for channel 2

//    DMA2CTL = DMADT_1+DMASRCINCR_3+DMADSTINCR_3; // Block tranfer (DMADT_1), inc src (DMASRCINCR_3), Interrupt disenabled

                                                // inc dst (DMADSTINCR_0), word to word, rising edge trigger (default)

//    DMA2SZ = 1;                                 // transfer size

//    __data16_write_addr((unsigned short) &DMA2SA, (unsigned long) &RESLO);  // Source address

//    __data16_write_addr((unsigned short) &DMA2DA,(unsigned long) pOutput);  // Destination address


    // initiate MPY by setting output and OP1 registers to be 0x0000

//    RESLO=0;

//    RESHI=0;

//    MACS_L=0x00;


//    DMA2CTL |= DMAIE;

//    DMA0CTL |= DMAEN;   // enable DMA channel 0

//    DMA1CTL |= DMAEN;   // enable DMA channel 1

//    DMA2CTL |= DMAEN;   // enable DMA channel 2

//    OP2 = 0x00;     // start MACS to get first DMA trigger

}
