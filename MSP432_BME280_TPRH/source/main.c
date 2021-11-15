/*
 * File brief  : main.c
 *
 *      Author : Mehul Patel
 * University of Colorado Boulder
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <string.h>  
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp432.h>



#include "app_mode.h"
#include "bme280_support.h"
#include "cli.h"
#include "demo_sysctl.h"
#include "i2c_driver.h"
#include "RTC.h"
#include "stdio.h"
#include "system_clock.h"
#include "systick.h"
#include "UART0.h"
#include "UART2.h"

#define CPU_FREQ                    (48000000)


/*
 *  BME Sensor connection
 *      I2C_SCL(P6.5)
 *      I2C_SDA(P6.4)
*/


/*
 * Function :   main function for calling initialization routines
 *					and switching to application mode
 * 
 * Parameters : None
 *
 * Returns  : None
 *
 */

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     //  // Stop WDT and
	
    MAP_Interrupt_disableMaster();  //disabling master interrupts

    // Configure clocks
    startCrystalOscillator();
    setSystemClock(CPU_FREQ);
	
	
    Init_UART0();		// Initialize UART 0 
    Init_UART2();		// Initialize UART 2
    Init_RTC();			// Initialize RTC 
	Init_SysTick();		// Initialize Systick timer 
	
    // Wake up on exit from ISR
    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
	
    volatile uint32_t index;
	
    // Enabling SRAM Bank Retention
    SYSCTL->SRAM_BANKRET |= SYSCTL_SRAM_BANKEN_BNK7_EN;
	
    for (index = 0;index < 100;index++);
	
	Init_I2C();    			// Initialize i2c
	
    MAP_Interrupt_enableMaster();
	
    Application_mode();
}



