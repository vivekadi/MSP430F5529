#include <msp430.h> 
#include <stdio.h>
#include <math.h>


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	double f[3][3]={{0,0,0},{0,1,0},{0,0,0}};
	double psum;
	unsigned int i,j;
	
	for(i=1;i<3;i++)
	    {
	        for(j=1;j<3;j++)
	        {
	            psum+=f[i][j];
	        }
	    }
	printf("%f\n",psum);
	f[1][1]=psum/9;

	for(i=0;i<3;i++)
	{
	    for(j=0;j<3;j++)
	    {
	        printf("%f\t",f[i][j]);
	    }
	    printf("\n");
	}
	return 0;
}
