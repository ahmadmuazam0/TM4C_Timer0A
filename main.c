

/**
 * main.c
 */
#include<stdint.h>
#include<stdbool.h>
#include"inc/tm4c123gh6pm.h"
#include "Timer_init.h"

//static int data = 0x04;
bool flag = 0;
void Timer_interrupt_Handler(void){

    flag = flag ^ 1;
    TIMER0_ICR_R        |=  0x01;
}

int main(void)
{
    volatile unsigned long delay;
       SYSCTL_RCGC2_R |= 0X00000020;       //F Clock
       delay = SYSCTL_RCGC2_R;             // Delay
       GPIO_PORTF_LOCK_R = 0x4C4F434B;     // Unlock PortF
       GPIO_PORTF_CR_R     =   0X1F;       // Allow changes to PF4-0
       GPIO_PORTF_AMSEL_R  =   0X00;       // Disable analog Function
       GPIO_PORTF_PCTL_R   =   0X00000000; // GPIO Clear Bit PCTL
       GPIO_PORTF_DIR_R    =   0X0E;       //GPIO Direction: PF4,PF0 is OUTPUT & PF1,2,3 are INPUT
       GPIO_PORTF_AFSEL_R  =   0X00;       //Disable Alternate Functions
       GPIO_PORTF_PUR_R    =   0X11;       //Enable Pull-UP resistors to both buttons pin
       GPIO_PORTF_DEN_R    =   0X1F;       //Enable Digital Pins PF4-PF0

       /* Initialize the TimerA_0*/

       Timer_init();
    while(1){

        if(flag){
            GPIO_PORTF_DATA_R   =   0X04;
        }
        else{
            GPIO_PORTF_DATA_R   =   0X02;   // Turn on the led
        }
    }

}
