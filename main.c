/*****************************************************************************
 * @file    main.c
 * @brief   Simple LED dim
 * @version 1.0
******************************************************************************/

#include <stdint.h>
/*
 * Including this file, it is possible to define which processor using command line
 * E.g. -DEFM32GG995F1024
 * The alternative is to include the processor specific file directly
 * #include "efm32gg995f1024.h"
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_device.h"
#include "led.h"
#include "pwm.h"
#include "gpio.h"
#include "clock_efm32gg2.h"

/*****************************************************************************
 * @brief  Main function
 *
 * @note   Using default clock configuration
 *         HFCLK = HFRCO
 *         HFCORECLK = HFCLK
 *         HFPERCLK  = HFCLK
 */

#include "uart2.h"

int main(void) {
    unsigned val;
    unsigned int switches;
    
    GPIO_Init(GPIOD, 0b1111, 0);
    /* Configure LEDs */
    LED_Init(LED1);

    // Configure LED PWM
    PWM_Init(TIMER3, PWM_LOC1, PWM_PARAMS_ENABLECHANNEL2|PWM_PARAMS_ENABLEPIN1);
   
    while (1) {
        val = (unsigned)0x0000;
        switches = GPIO_ReadPins(GPIOD);

        if(switches & BIT(0))   val += 0xFFFF/16;
        if(switches & BIT(1))   val += 0xFFFF/8;
        if(switches & BIT(2))   val += 0xFFFF/4;
        if(switches & BIT(3))   val += 0xFFFF/2;
        if(switches == 0b1111) val = 0xFFFF;

        PWM_Write(TIMER3,2,val);
    }

}