#include <msp430.h>
#include <stdio.h>
#include <stdint.h>

#define DATA16_ADDR(addr)   ((uint16_t)(((uintptr_t)addr) & 0xffff))

#define DIM_HIDDEN         10 //128
#define DIM_OUTPUT         10 //5

//int8_t a[DIM_HIDDEN] = {3,8,-1,7,9,12,3,10,13,11,4,10,2,12,10,2,-3,7,11,13,4,7,8,7,9,6,9,7,2,7,6,-2,9,0,13,3,5,11,-6,12,5,8,3,11,11,10,1,9,11,1,9,4,7,1,7,-2,7,11,14,11,3,9,5,8,9,9,-3,7,8,12,9,11,10,9,9,13,10,7,3,-5,11,12,11,7,7,4,2,9,2,6,12,9,7,9,9,7,8,4,9,6,7,6,7,11,9,9,3,12,0,11,1,9,8,10,8,2,9,9,1,5,3,13,5,8,-1,9,12,10};

//int8_t beta[DIM_HIDDEN*DIM_OUTPUT]={-9,-4,-8,4,5,8,8,5,-9,-9,-9,-8,7,5,7,1,-4,2,1,4,8,8,8,-6,-8,8,-2,-2,8,3,-6,-9,-5,2,2,-3,-3,-1,7,3,7,7,-9,4,1,2,-1,-2,-3,-8,-8,-6,3,0,-9,2,3,0,-5,9,8,-6,-9,3,4,9,-8,9,-8,-9,2,-2,-8,-9,2,4,6,0,9,-2,-6,7,2,-9,-4,-6,-7,-3,1,-8,-1,1,5,-1,3,4,5,9,4,-1,-1,-8,-9,5,6,5,-3,7,9,-9,6,3,-6,-6,-2,6,-4,2,9,-7,5,9,0,-3,-2,-1,-5,6,8,6,-5,3,9,6,-4,8,-3,7,-5,1,4,-6,0,3,-3,-7,3,1,-5,-9,7,-6,4,8,-7,-1,-8,-9,2,8,6,4,-3,5,9,-9,-7,8,-9,7,2,7,-8,-9,-2,4,0,7,9,7,-2,8,5,9,6,0,-6,-3,-4,0,5,-6,8,9,6,-3,-9,1,-6,-2,9,1,6,6,2,-7,-3,-5,9,2,-5,-4,-4,6,-4,-2,-6,-8,8,1,-7,0,-2,7,7,-9,0,0,0,-8,8,1,-6,1,-1,-4,-6,-8,-6,2,-6,8,0,5,9,1,6,4,4,2,4,5,-9,8,-7,-7,-5,8,6,4,3,0,-4,-7,4,4,1,-5,7,6,-4,-5,-7,9,-9,-2,7,9,1,8,-1,8,0,-5,9,1,-4,7,-8,3,9,-2,-7,-1,9,6,-2,-8,-8,2,9,-7,-5,9,0,3,-4,-3,-8,-2,3,3,7,0,-4,-2,-1,9,-7,8,-3,0,1,7,0,-2,0,-8,4,-6,8,7,7,-5,-1,-3,-3,-2,5,9,-4,-4,6,9,5,4,-9,1,-4,0,-7,0,4,-3,0,2,-5,9,5,2,5,5,1,-6,0,-8,-2,7,-1,-9,-5,8,-6,4,4,-5,-1,4,7,5,0,0,3,6,6,8,-1,2,6,3,0,-5,5,8,-5,6,0,-4,2,2,5,-6,5,2,0,2,-9,-7,7,-8,2,-5,-6,7,-4,-8,-8,-2,-9,-2,5,-1,-2,4,1,3,3,8,2,0,3,-4,4,-6,2,4,-3,-7,3,5,-2,5,-8,3,-6,0,2,3,5,6,9,-8,4,-4,-9,2,-8,-3,1,-6,-9,-4,-3,-1,-6,-1,3,-7,-6,-7,-2,2,-5,-1,-4,9,-5,-3,-3,4,8,9,3,-1,4,-1,4,2,5,2,-8,-9,-5,7,4,3,-9,-8,-8,-4,0,0,6,1,4,-9,8,-5,4,-4,6,-7,-5,-3,0,-8,4,-5,-5,-9,3,2,-1,-1,0,-1,0,9,-2,-5,6,-9,4,0,-7,2,6,-8,6,8,-8,-3,1,3,-9,-5,1,-5,8,-1,5,-6,-4,8,0,-1,-2,-6,-9,-2,0,7,-2,3,9,5,-8,-5,5,-6,0,6,7,-9,-1,4,-1,2,7,1,-5,9,9,5,-9,5,-6,4,2,1,-6,-8,-3,-8,-2,5,-4,-4,-2,-4,8,-7,-3,7,0,-8,4,9,-2,9,2,7,-3,0,2,-1,-8,-7,-9,-1,-1,-6,-5,1,-7,-9,-9,-5,7,1,7,1,8,-6,1,-5,4,-4,-7,-2};


int8_t a[DIM_HIDDEN] = {1,2,3,4,5,6,7,8,9,10};
int8_t beta[DIM_HIDDEN*DIM_OUTPUT] = {1,2,3,4,5,6,7,8,9,10};
int16_t g[DIM_OUTPUT];
int16_t g_ref[DIM_OUTPUT];

int x;

extern void REF_MACS(int8_t *srcA, int8_t *srcB, int16_t *dst, uint16_t srcALen, uint8_t dstLen);
extern void DMA_MACS(int8_t *srcA, int8_t *srcB, int16_t *dst, uint16_t srcALen, uint8_t dstLen);

int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Calculate result
    DMA_MACS(a, beta, g, DIM_HIDDEN, DIM_OUTPUT);

    // Calculate reference result
    REF_MACS(a, beta, g_ref, DIM_HIDDEN, DIM_OUTPUT);

    return 0;
}

void REF_MACS(int8_t *srcA, int8_t *srcB, int16_t *dst, uint16_t srcALen, uint8_t dstLen)
{
    uint16_t i;
    uint16_t j;

    for (i = 0; i < dstLen; i++) {
        dst[i] = 0;
        for (j = 0; j < srcALen; j++) {
            dst[i] += (int16_t)srcA[j] * (int16_t)srcB[i*srcALen + j];

            printf("%d \t",dst[i]);
            x+=dst[i];
        }
    }



    return;
}

void DMA_MACS(int8_t *srcA, int8_t *srcB, int16_t *dst, uint16_t srcALen, uint8_t dstLen)
{
    uint16_t i;

    // Configure DMA channel 0 to transfer srcA to MACS
    DMACTL0 = DMA0TSEL_29;
    DMA0CTL = DMADT_0+DMASRCINCR_3+DMADSTBYTE+DMASRCBYTE+DMAIE;
    DMA0SZ = srcALen;
    __data16_write_addr(DATA16_ADDR(&DMA0SA), (uintptr_t)srcA);
    __data16_write_addr(DATA16_ADDR(&DMA0DA),(uintptr_t)&MACS);

    // Configure DMA channel 1 to transfer srcB to OP2
    DMACTL0 |= DMA1TSEL_29;
    DMA1CTL = DMADT_0+DMASRCINCR_3+DMADSTBYTE+DMASRCBYTE;
    DMA1SZ = srcALen;
    __data16_write_addr(DATA16_ADDR(&DMA1DA),(uintptr_t)&OP2);

    for (i = 0; i < dstLen; i++)
    {
        // Setup DMA to copy srcB and increment pointer
        __data16_write_addr(DATA16_ADDR(&DMA1SA), (uintptr_t)srcB);
        srcB += srcALen;

        // Enable DMA and start DMA trigger with zero multiply
        // Using MPYS resets result registers to zero
        DMA1CTL &= ~DMAIFG;
        DMA0CTL |= DMAEN;
        DMA1CTL |= DMAEN;
        MPYS = a[i];
        OP2 = beta[i];

        // Enter LPM0 while waiting for result to complete
        __bis_SR_register(GIE+LPM0_bits);

        // Save result to dst
        *dst++ = RESHI;

        printf("%d t\t",dst);
    }

    return;
}

// DMA interrupt service routine
#pragma vector = DMA_VECTOR
__interrupt void DmaIsr(void)
{
    switch(__even_in_range(DMAIV, DMAIV_DMA0IFG)) {
    case DMAIV_NONE: break;
    case DMAIV_DMA0IFG:
        // Exit from LPM0
        __bic_SR_register_on_exit(LPM0_bits);
        break;
    default: break;
    }
}
