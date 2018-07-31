/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CODING_SWITCH2_H
#define __CODING_SWITCH2_H

#include "mk_a9.h"

#define WMMG1_A_new		1
#define WMMG1_A_old		2
#define WMMG1_B_new		3
#define WMMG1_B_old		4

#define WMMG1_A_new_BIT	0x01
#define WMMG1_B_new_BIT	0x02
#define WMMG1_A_old_BIT	0x04
#define WMMG1_B_old_BIT	0x08	

#define WMMG_L          0 
#define WMMG_H          1
#define WMMG_ERROR      2

#define KEY_ADD2 HAL_GPIO_ReadPin(WMMG2_A_GPIO_Port, WMMG2_A_Pin)
#define KEY_SUB2 HAL_GPIO_ReadPin(WMMG2_B_GPIO_Port, WMMG2_B_Pin)

extern u8 Shift_Add_FG2;								                        //正转标志
extern u8 Shift_Sub_FG2;								                        //反转标志

void set_WMMG1_state(u8 key, u8 value);
u8 get_WMMG1_state(u8 key);
void Scan_Shift2_Prog(void);

#endif
