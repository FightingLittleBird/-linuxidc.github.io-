#ifndef __CODING_SWITCH_H
#define __CODING_SWITCH_H

/* define ------------------------------------------------------------------*/
#define KEY_SUB HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10)
#define KEY_ADD HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12)

/* Includes ------------------------------------------------------------------*/
#include "mk_a9.h"

extern u8 Shift_Add_FG;
extern u8 Shift_Sub_FG;

/* Function prototypes -------------------------------------------------------*/
void Scan_Shift_Prog(void);
void wheel_add_processing(void);
void wheel_sub_processing(void);

#endif