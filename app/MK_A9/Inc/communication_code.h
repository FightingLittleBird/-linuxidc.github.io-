/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COM_CODE_H
#define __COM_CODE_H

#include "MK_A9.h"

#define PACKAGE_REV_NUM		20

#define PRINT_INFO					0x01
#define PRINT_DATA					0x02

typedef enum
{
	NO_Communication_HEAD = 1,	
	NO_Communication_TAIL = 2,	
	NO_Communication_TYPE = 3,	
	U8_DATA_OUT	= 4,
	DATA_ERROR	= 5,
	
}ERROR_CMD;


typedef enum
{
	HEAD_DATA = 0xf0,
	TAIL_DATA = 0x55,
	
	
}DATA_CODE;

typedef enum
{
  type_A = 0x0b,
  type_B = 0x14,
  type_C = 0x0a,
  type_D = 0x19,
  type_E = 0x75,
  type_F = 0x30,
}lens_type;

typedef enum
{
	MF_AF	= 1,
	AE
	
}camera_key;

typedef enum
{
	AF	= 1,
	MF	= 2,
}camera_value;

typedef enum{
	column_print_head_CMD	= 1,
	row_print_head_CMD		= 2,	
	column_print_30_CMD		= 3,
	row_print_30_CMD			= 4,	
	column_print_75_CMD		= 5,
	row_print_75_CMD			= 6,	
}print_format_e;


typedef struct{
  u8 type;
  u8 data[50];
  
}lens_info_A;

typedef struct{
	u8 pare1;
	u8 pare2;
	u8 pare3;
	u8 pare4;	
	print_format_e cmd;
}print_pare_s;

typedef struct{
	u8 num;
	print_format_e cmd;
	word head[PACKAGE_REV_NUM];
	word tail[PACKAGE_REV_NUM];
}print_index_data_s;

typedef struct{
	u8 * aperture_info;
	u16 data;
}aperture_info_s;


extern print_index_data_s print_data;

void aperture_data_print(void);
void communication_code_execute_line(u8 package_line, print_format_e cmd, u8 para_a, u8 para_b);
void error_print(ERROR_CMD error_code);

void init_print(void);
void set_print_format(print_pare_s *print_pare_p);
void get_print_format(print_pare_s *print_pare_p);
void set_print_column_data_index(word head, word tail);
void print_column_data(u8 line_start, u8 line_end, u8 num_sys);
void print_communication_parse(void);

#endif /*__COM_CODE_H*/
