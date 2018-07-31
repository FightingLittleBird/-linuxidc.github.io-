/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_DMA_H
#define __UART_DMA_H

#include "MK_A9.h"

#define PACKAGE_DATA_SIZE 4000
#define PACKAGE_REV_NUM		20              //×î´ó46

typedef enum
{
	HEAD					= 1,
	TAIL					= 2,
}Package_Index_CMD;

typedef enum
{
	START				= 1,
	END					= 2,
	OUT					= 3,
}Rev_State_E;

extern word package_index_head[PACKAGE_REV_NUM];
extern word package_index_tail[PACKAGE_REV_NUM];
extern u8  DMA_rev_package_num;

u8 get_communication_data_buf(word index);
u8* get_communication_data_buf_address(word index);
void clear_communication_data_buf(void);


void set_package_index(u8 index, u8 len, word tail);
word get_package_index(u8 index, Package_Index_CMD cmd);


word get_communication_data_index(void);
void set_communication_data(word index, u8 *data, u8 len);
void clear_communication_data_index(void);
Rev_State_E Uart_Receive_DMA(void);

#endif /* __UART_DMA_H */