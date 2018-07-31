#ifndef __PROTOCOL_H
#define __PROTOCOL_H

/* Includes ------------------------------------------------------------------*/
#include "MK_A9.h"

#define	GC_EXECUTE_LINE														    //执行G代码解析	
#define PROTOCOL_EXECUTE_LINE			

extern u8 get_data_flg;

typedef struct 
{
	u8  *cmd;
	int (*cmd_handler)(u8 *str, u8 *out);
}CMD_T;

void send_package(void);
uint8_t protocol_execute_line(uint8_t *line);									                  //执行一行协议命令
void protocol_process(void);													                          
	
#endif
