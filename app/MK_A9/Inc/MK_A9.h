#ifndef __MK_A9_H
#define __MK_A9_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "stm32f0xx_hal.h"
#include "main.h"

#include "sys.h"

//#include "tim.h"
//#include "spi.h"
#include "usart.h"
#include "flash.h"
#include "gpio.h"

#include "stm32f0xx_lp_modes.h"
#include "coding_switch.h"
#include "coding_switch2.h"
#include "key_process.h"
#include "protocol.h"
#include "gpio_spi.h"
#include "usr_usart.h"
#include "usr_uart_dma.h"
#include "communication_code.h"
#include "Gcode.h"
#include "usr_stdlib.h"

#define DISABLE_INTERRUPTS()				__asm volatile( "cpsid i" )
#define ENABLE_INTERRUPTS()					__asm volatile( "cpsie i" )                                      

/* Function prototypes -------------------------------------------------------*/
void usr_init(void);
void usr_loop(void);

void uIdeHook(void);

#endif