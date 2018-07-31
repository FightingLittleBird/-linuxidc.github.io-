#ifndef __KEY_PROCESS_H
#define __KEY_PROCESS_H

#include "mk_a9.h"

#define F_KEY_C1 		1																			
#define F_KEY_C2 		2

#define D_KEY_TOP 		1
#define D_KEY_DOWN 		2
#define D_KEY_LEFT 		3
#define D_KEY_RIGHT 	4
#define KEY2 			5
#define KEY3 			6

#define	F_KEY_C1_PRESS		0xBC		//功能键组C1键按下键码
#define	F_KEY_C1_UPLIFT		0xBD		//功能键组C1键松开键码

#define	F_KEY_C2_PRESS		0xDC
#define	F_KEY_C2_UPLIFT		0xDD

#define	D_KEY_TOP_PRESS		0xFC		//方向键组上键按下键码
#define	D_KEY_TOP_UPLIFT	0xFD

#define	D_KEY_DOWN_PRESS	0xFA		//方向键组下键按下键码
#define	D_KEY_DOWN_UPLIFT	0xFB

#define	D_KEY_LEFT_PRESS	0xF6		//方向键组左键按下键码
#define	D_KEY_LEFT_UPLIFT	0xF7

#define	D_KEY_RIGHT_PRESS	0xEE		//方向键组右键按下键码
#define	D_KEY_RIGHT_UPLIFT	0xEF


typedef struct {
    uint8_t function_key_code;
    uint8_t wheel_key_code;
    uint8_t wheel2_key_code;
    uint8_t direction_key_code;
} message_package;

typedef struct {
	volatile uint8_t Key_press_flag;
	volatile uint8_t Key_uplift_flag;
	volatile uint8_t fun_key_press_state;
	volatile uint8_t fun_key_uplift_state;
	volatile uint8_t dir_key_press_state;
	volatile uint8_t dir_key_uplift_state;
	volatile uint8_t wheel_key_state;
	volatile uint8_t wheel2_key_state;
	volatile uint16_t key_pin;
} key_state;

extern key_state key;
extern message_package package;
extern u8 key_IRQHandler_flag;


void gpio_exti_processing(uint16_t GPIO_Pin);
void Key_uplift_processing(key_state key_stat);
void Key_press_processing(key_state key_stat);

void usr_key_process(void);



#endif 
