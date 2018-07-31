#include "communication_code.h"

lens_info_A Lens_8517_info;

print_index_data_s print_data;
print_pare_s print_pare;  	

static void print_75_cmd_comment(u8 row_num, u8 data);

static aperture_info_s aperture_info_d[] =                                      //镜头直径和数据对照表
{
	{"F22", 0x1900},
	{"F20", 0x18AA},	
	{"F18", 0x1855},
	{"F16", 0x1800},
	{"F14", 0x17AA},	
	{"F13", 0x1755},
	{"F11", 0x1700},
	{"F10", 0x16AA},	
	{"F9.0", 0x1655},
	{"F8.0", 0x1600},
	{"F7.1", 0x15AA},	
	{"F6.3", 0x1555},
	{"F5.6", 0x1500},
  {"F5.0", 0x14AA},
	{"F4.5", 0x1455},	
	{"F4.0", 0x1400},
	{"F3.5", 0x13AA},
	{"F3.2", 0x1355},	
	{"F2.8", 0x1300},
	{"F2.5", 0x12AA},
	{"F2.2", 0x1255},	
	{"F2.0", 0x1200},
	{"F1.8", 0x11BC},
};

static const int MAX_APERTURE_NUM = (sizeof(aperture_info_d)/sizeof(aperture_info_d[0]));

/* 测试打印镜头直径和数据对照表 */
void aperture_data_print(void)                            
{
	u8 i;

	printf("aperture data:\r\n");
	for(i=0; i<MAX_APERTURE_NUM; i++)
	{
		printf("%s	%04X	%d		", 	aperture_info_d[i].aperture_info, 
																		aperture_info_d[i].data, 
																		aperture_info_d[i].data);
		if(i>0)
		{
			printf("%d	", aperture_info_d[i-1].data-aperture_info_d[i].data);			
		}
		printf("\r\n");
	
	}
}

/* 获取相机状态 */
void get_camera_state(camera_key key, u8 data, u8 *out_string)
{
	switch(key)
	{
		case MF_AF:
			if(data == 0x01)
			{
				sprintf((char *)out_string, "AF");
			}
			if(data == 0x03)
			{
				sprintf((char *)out_string, "MF");
			}
			break;

		case AE:
			if(!data)
			{
				sprintf((char *)out_string, "AE_NO");
			}
			if(data == 0x08)
			{
				sprintf((char *)out_string, "AE_YES");
			}
			break;

		default:
			sprintf((char *)out_string, "error");
			break;
	}

}

/* 获取镜头数据 */
u8* get_aperture_data(u8 *line)
{
	u16 aperture_data = 0;
	u16 i;
	
	aperture_data = line[8-1] << 8;
	aperture_data = aperture_data | line[7-1];

	for(i=0; i<MAX_APERTURE_NUM; i++)                                             //查询镜头对照表
	{
		if(aperture_info_d[i].data == aperture_data)
		{
			return aperture_info_d[i].aperture_info;
		}
	}
	
  return "error";
}

/* 解析头数据类型 */
void type_A_parse(u8 *line, u16 len, lens_type type, u8 print_switch)
{
  u8 i;
	u16 check_sum;

	len = len-3-2;																													      //去首尾类型和两位校验位
	check_sum = type;																														  //计数校验和
  
	for(i=0; i<len; i++)													                                //解析一行
	{
//		Lens_8517_info.data[i] = line[i+2];																					//数据有效位开始赋值
		
		if(print_switch&PRINT_DATA)
		{
			printf("%02x ", line[i+2]);
		}
		
		check_sum = check_sum + line[i+2]; 
	}
	
	if(print_switch&PRINT_DATA)
	{
		printf("\r\n");
	}

	if(print_switch&PRINT_INFO)
	{	
		printf("A类型:%02X 校验和:%02X %02X\r\n", type, check_sum%256, check_sum/256);
		printf("\r\n");
	}	

}

/* 75开头类型解析 */
void type_E_parse(u8 *line, u16 len, lens_type type, u8 print_switch)
{
	u8 i;
	u16 check_sum;
	u8 out_string[10];

	len = len-3-2;																																//去首尾类型和两位校验位
	check_sum = type; 																														//计数校验和
	
	for(i=0; i<len; i++)																													//解析一行
	{
//		Lens_8517_info.data[i] = line[i+2]; 																						//数据有效位开始赋值
		if(print_switch&PRINT_DATA)
		{
			printf("%02x ", line[i+2]);
		}

		check_sum = check_sum + line[i+2]; 
	}
	
	if(print_switch&PRINT_DATA)
	{
		printf("\r\n");
	}

	if(print_switch&PRINT_INFO)
	{
		printf("E类型:%02X	", type);
		//	printf("校验和:%02X %02X ", check_sum%256, check_sum/256);
		//	printf("流水号:%02X ", line[2+2]);
		printf("%s	", get_aperture_data(line));                                    //打印镜头模式
		
		get_camera_state(MF_AF, line[69-1], out_string);
		printf("%s	", out_string); 

		get_camera_state(AE, line[71-1], out_string);
		printf("%s	", out_string);       																					//打印手动自动模式
		i = 24;
		//	printf("未知1:%02X %02X %02X %02X ", line[2+i++], line[2+i++], line[2+i++], line[2+i++]);
		printf("\r\n\r\n");
	}
}

/* 30开头类型解析 */
void type_F_parse(u8 *line, u16 len, lens_type type, u8 print_switch)
{
	u8 i;
	u16 check_sum;

	len = len-3-2;																																//去首尾类型和两位校验位
	check_sum = type; 																														//计数校验和
	
	
	for(i=0; i<len; i++)																													//解析一行
	{
		//Lens_8517_info.data[i] = line[i+2]; 																				//数据有效位开始赋值

		if(print_switch&PRINT_DATA)
		{
			printf("%02x ", line[i+2]);
		}		

		check_sum = check_sum + line[i+2]; 
	}
	
	if(print_switch&PRINT_DATA)
	{
		printf("\r\n");
	}


if(print_switch&PRINT_INFO)
{
	printf("F类型:%02X 校验和:%02X %02X\r\n", type, check_sum%256, check_sum/256);
	printf("\r\n");
}

}

/* 执行一行数据解析 */
void communication_code_execute_line(u8 package_line, print_format_e cmd, u8 para_a, u8 para_b)
{
//	u16 i,j;
	u8 *line;
	word data_head;                                                               //在数据缓存中此行头索引
	word data_tail;                                                               //在数据缓存中此行尾索引
	u8 len;
	lens_type type;

	data_head = get_package_index(package_line, HEAD);
	data_tail = get_package_index(package_line, TAIL);
	len = data_tail -  data_head;

	if(len >= 255)
	{
		error_print(U8_DATA_OUT);
		return;
	}

	if(len == 0)
	{
		error_print(DATA_ERROR);
		return;
	}

	if(DMA_rev_package_num == 0)
	{
		error_print(DATA_ERROR);
		return;
	}

	line = get_communication_data_buf_address(data_head);                         //获取数据缓存去
 
	/* 首先判断是否有包头 */	
	if(line[0] != HEAD_DATA)										                                  //没有头退出并报错
	{
		error_print(NO_Communication_HEAD);
		return;
	}
	
	/* 判断是否有包尾 */
	if(line[len-1] != TAIL_DATA)										                              //没有尾退出并报错
	{
		error_print(NO_Communication_TAIL);
		return;
	}	

	/* 获取类型 */
//	Lens_8517_info.type = line[1];	
	type = (lens_type)line[1];
	
	switch(type)
	{
		case type_A:																												        //0x0b类型
		case type_B:																											       		//0x14类型	
		case type_C:																															  //0x0a类型
		case type_D:																															  //0x19类型
			if(cmd == column_print_head_CMD)                                         		//需要打印时设置打印索引
			{
				set_print_column_data_index(data_head, data_tail); 						  
			}
			if(cmd == row_print_head_CMD) 
			{			
				type_A_parse(line, len, type, para_a);	
			}
			break;
      
		case type_E:																	       			       			      //0x75类型	
			if(cmd == column_print_75_CMD)                                         		//需要打印时设置打印索引
			{
				set_print_column_data_index(data_head, data_tail); 						  
			}
			if(cmd == row_print_75_CMD) 
			{
				type_E_parse(line, len, type, para_a);                                  //解析类型
			}
			break;
			
		case type_F:																	       			       			      //0x30类型
			if(cmd == column_print_30_CMD)                                         		//需要打印时设置打印索引
			{
				set_print_column_data_index(data_head, data_tail); 						  
			}
			if(cmd == row_print_30_CMD) 
			{
				type_F_parse(line, len, type, para_a);  
			}
			
			break;

		default:
			error_print(NO_Communication_TYPE);
      return;
	}
  
}

/* 错误打印 */
void error_print(ERROR_CMD error_code)
{
	printf("ERROR:");
	switch(error_code)
	{
		case NO_Communication_HEAD:
			printf("[通讯数据无头]\r\n");
			break;
			
		case NO_Communication_TAIL:
			printf("[通讯数据无尾]\r\n");
      break;

		case NO_Communication_TYPE:
			printf("[通讯数据无类型]\r\n");
			break;  

		case U8_DATA_OUT:                                                           //u8数据类型将要越界
			printf("[U8_DATA_OUT]\r\n");
			break; 

		case DATA_ERROR:                                    
			printf("[DATA_ERROR]\r\n");
			break; 			

		default:
			break;
	}
}

/* 75开头数据行注释 */
void print_75_cmd_comment(u8 row_num, u8 data)
{
	u8 out_string[10];
	switch(row_num+1)
	{
    case 1:
			printf("包头	");
			break;
			
    case 2:
			printf("字节数	");			
			break;
      
    case 3:
			printf("命令类型	");			
			break;      
    case 4:
			printf("命令类型	");			
			break;      

    case 7:
			printf("光圈	");			
			break;
    case 8:
			printf("光圈	");			
			break;			

    case 5:
			printf("流水号	");			
			break;

    case 27:
			printf("未知1	");			
			break;
    case 28:
			printf("未知1	");			
			break;
    case 29:
			printf("未知1	");			
			break;
    case 30:
			printf("未知1	");	
			break;	


    case 40:
			printf("位置1	");	
    case 41:
			printf("位置1	");			
			break;
    case 42:
			printf("位置1	");			
			break;
    case 43:
			printf("位置1	");			
			break;
    case 44:
			printf("位置1	");	
			break;	
			

    case 45:
			printf("变化1	");			
			break;
    case 46:
			printf("变化1	");			
			break;
    case 47:
			printf("变化1	");			
			break;
    case 48:
			printf("变化1	");	
			break;	
		case 49:
			printf("变化1 "); 		
			break;
		case 50:
			printf("变化1 "); 
			break;	


    case 69:
    	get_camera_state(MF_AF, data, out_string);                                //打印对焦模式信息
			printf("AF/MF	%s	", out_string);	
			break;

    case 71:	
    	get_camera_state(AE, data, out_string);                                   //打印对焦是否锁定
			printf("AE	%s	", out_string);	
			break;			

		case 96:
			printf("变化2 "); 
			break;	


    case 97:
			printf("位置2	");			
			break;
    case 98:
			printf("位置2	");			
			break;
    case 99:
			printf("位置2	");			
			break;
    case 100:
			printf("位置2	");	
			break;	
			
		case 101:
			printf("变化3 "); 
			break;	

		case 106:
			printf("变化4 "); 
			break;		
		case 107:
			printf("变化4 "); 
			break;	
		case 108:
			printf("变化4 "); 
			break;				

		case 112:
			printf("变化5 "); 
			break;		
		case 113:
			printf("变化5 "); 
			break;	
		case 114:
			printf("变化5 "); 
			break;	
			

    case 115:
			printf("校验和	");			
			break;
    case 116:
			printf("校验和	");	
			break;
			
    case 117:
			printf("包尾	");	
			break;			
			
		default:
			break;
	}
}

/* 30开头数据行注释 */
void print_30_cmd_comment(u8 row_num, u8 data)
{
	switch(row_num+1)
	{
    case 1:
			printf("包头	");
			break;
			
    case 2:
			printf("字节数	");			
			break;
      
    case 3:
			printf("命令类型	");			
			break;      
    case 4:
			printf("命令类型	");			
			break;     		

    case 5:
			printf("流水号	");			
			break;

    case 7:		
			break;
    case 8:		
			break;	
			

    case 27:
		
			break;
    case 28:
	
			break;
    case 29:
	
			break;
    case 30:

			break;	


    case 40:

    case 41:

			break;
    case 42:
	
			break;
    case 43:
	
			break;
    case 44:

			break;	
			

    case 45:

			break;
			
    case 46:
			printf("校验	");		
			break;
    case 47:
			printf("校验	");			
			break;
    case 48:
			printf("包尾	");
			break;	
	
		default:
			break;
	}
}

/* 初始化打印格式 */
void init_print(void)
{
	print_pare.pare1	= 3;                                                        //默认从0行开始打印
	print_pare.pare2 = 1;                                                         //默认打印到最后行
	print_pare.pare3 = 0;                                                         //默认HEX输出
	print_pare.pare4 = 0;
	print_pare.cmd = row_print_75_CMD;                                            //默认竖列打印75开头命令
	
	memset(&print_data, 0, sizeof(print_data));	
}

/* 设置打印格式 */
void set_print_format(print_pare_s *print_pare_p)
{
	print_pare.pare1 = print_pare_p->pare1;
	print_pare.pare2 = print_pare_p->pare2;
	print_pare.pare3 = print_pare_p->pare3;
	print_pare.pare4 = print_pare_p->pare4;	
	print_pare.cmd = print_pare_p->cmd;
}

/* 获取打印格式 */
void get_print_format(print_pare_s *print_pare_p)
{
	print_pare_p->pare1 = print_pare.pare1;
	print_pare_p->pare2 = print_pare.pare2;	
	print_pare_p->pare3 = print_pare.pare3;
	print_pare_p->pare4 = print_pare.pare4;		
	print_pare_p->cmd = print_pare.cmd;
}

/* 设置打印数据索引 */
void set_print_column_data_index(word head, word tail)
{
	print_data.head[print_data.num] = head;
	print_data.tail[print_data.num] = tail;
	print_data.num++;	
}

/* 获取打印数据索引 */
word* get_print_column_data_index(u8 *column_num, u8 *row_num)
{
	*column_num = print_data.num;
	*row_num = print_data.tail[0] - print_data.head[0];
	return print_data.head; 
}


/* 打印采集的通讯数据 */
void print_column_data(u8 line_start, u8 line_end, u8 num_sys)
{
	u8 i,j;
  u8 *line[PACKAGE_REV_NUM];
//  word head[120];

  u8 column_num;																							                  //列数
  u8 row_num;	

	get_print_column_data_index(&column_num, &row_num);
	
	if(line_end)
	{
		row_num = line_end;
	}
//	else
//	{
//		row_num = print_data.tail[0] - print_data.head[0];												  				//计算打印行数		
//	}
	
//	column_num = print_data.num;																								  //列数赋值
	
	printf("行数%d	列数%d	命令类型%d\r\n", row_num, column_num, print_pare.cmd);
  
	printf("LINE	"); 																													  //打印列信息并赋值打印指针
	for(i=0; i< column_num; i++)																								  
	{
		printf("%d	", i+1);
		line[i] = get_communication_data_buf_address(print_data.head[i]); 
//		line[i] = get_communication_data_buf_address(head[i]);           
	}
	printf("fun	");
	printf("state	");
	printf("\r\n");

	for(i=line_start; i<row_num; i++)																							//打印数据
	{ 
		printf("[ %d ]	", i+1);																								    //打印行信息
		for(j=0; j<column_num; j++)
		{
			if(num_sys)
			{
				printf("%d	", line[j][i]);	
			}
			else
			{
				printf("%02X	", line[j][i]);			
			}
		}

		if(print_pare.cmd == column_print_75_CMD)                                   //打印75开头命令备注信息
		{
			print_75_cmd_comment(i, line[column_num-1][i]); 												
		}	
		if(print_pare.cmd == column_print_30_CMD)                                   //打印30开头命令备注信息
		{
			print_30_cmd_comment(i, line[column_num-1][i]); 													
		}		
		
		printf("\r\n");
	}

	memset(&print_data, 0, sizeof(print_data));                                   //清除打印索引准备下一次打印

}

void print_communication_parse(void)
{
	u8 i;
  print_pare_s print_pare;

	get_print_format(&print_pare);
//	printf("%d %d %d\r\n", print_pare.cmd, print_pare.pare1, print_pare.pare2);
	switch(print_pare.cmd)
	{
		case column_print_head_CMD:
		case column_print_30_CMD:
		case column_print_75_CMD:
			printf("打印竖行信息	起始行%d	结束行%d 打印进制%s\r\n", 
								print_pare.pare1, print_pare.pare2, print_pare.pare3?"DEC":"HEX");				
			/* 如果打印索引没有赋值执行解析代码赋值索引 */
			if(!print_data.num)
			{
				for(i=0; i<DMA_rev_package_num; i++)																    //解析每组数据
				{
					communication_code_execute_line(i, 
                     print_pare.cmd, print_pare.pare1, print_pare.pare2);				//参数1:打印数据还是信息
				}
					HAL_Delay(10);
			}
			print_column_data(print_pare.pare1, print_pare.pare2, print_pare.pare3);	//打印数据
			break;

		case row_print_head_CMD:	
		case row_print_30_CMD:
		case row_print_75_CMD:
			printf("打印横向信息	打印方式%02X\r\n", print_pare.pare1);
			for(i=0; i<DMA_rev_package_num; i++)																		  //解析每组数据
			{
				communication_code_execute_line(i, print_pare.cmd, print_pare.pare1, print_pare.pare2);
			} 
			break;
			
	}

	
}




































