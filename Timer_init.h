/*
 * Timer_init.h
 *
 *  Created on: 12-Jun-2024
 *      Author: Ahmad Muazam
 *
 *  This header is to initialize the Timer0_A
 *
 *  Here is the IRQ Handler of the Timer for testing you can Define your ISR
 *
 *  Go to Startup file --> extren the custom Interrupt Handler

       extern void Timer_interrupt_Handler(void);

 *  Replace the DefaultHandler with custom one in vector table i.e

       (line:105) Timer_interrupt_Handler

 *  Define the ISR in main code of any other header/source file and include it into the main i.e.
        bool flag = 0;
        void Timer_interrupt_Handler(void){

            flag = flag ^ 1;                // Toggle the flag to Blink Led
            TIMER0_ICR_R        |=  0x01;   // Clear the Interrupt Flag
        }
 *
 *
 */

#ifndef TIMER_INIT_H_
#define TIMER_INIT_H_

#include<stdint.h>
#include"inc/tm4c123gh6pm.h"

void Timer_init(){

    // Enable the Clock for Timer0_A
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0;

    TIMER0_CTL_R    &=  0;  /* Initially disable the Timers*/
    TIMER0_CFG_R    &=  0;  // Selection of 32-bit timer out of 16/32 bit option.
    TIMER0_TAMR_R   |=  (TIMER_TAMR_TAMR_PERIOD | (1<<4));  // Selection of Periodic Mode of Timer A  and Select the Direction of Timer is Increment
    TIMER0_TAILR_R  =   0x00F42400;    //  Time to count N Second = Frequency * N = 16MHz * 1 = F42400 = 16000000
    TIMER0_IMR_R    |=  TIMER_IMR_TATOIM;   // Enable interrupt on time-up
    TIMER0_CTL_R    |=  1;  // Enable the Timer to Start Counting
    NVIC_EN0_R      |=  (1<<19);    // Enable 19th interrupt i.e. for Timer0_A 16/32bit.


}





#endif /* TIMER_INIT_H_ */
