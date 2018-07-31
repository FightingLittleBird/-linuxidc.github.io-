#ifndef __PROTOCOL_H
#define __PROTOCOL_H

/* Includes ------------------------------------------------------------------*/
#include "MK_A9.h"

#define	GC_EXECUTE_LINE														    //ִ��G�������	
#define PROTOCOL_EXECUTE_LINE			

extern u8 get_data_flg;

typedef struct 
{
	u8  *cmd;
	int (*cmd_handler)(u8 *str, u8 *out);
}CMD_T;

void send_package(void);
uint8_t protocol_execute_line(uint8_t *line);									                  //ִ��һ��Э������
void protocol_process(void);													                          
	
#endif
