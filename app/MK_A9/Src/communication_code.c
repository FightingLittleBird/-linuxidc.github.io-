#include "communication_code.h"

lens_info_A Lens_8517_info;

print_index_data_s print_data;
print_pare_s print_pare;  	

static void print_75_cmd_comment(u8 row_num, u8 data);

static aperture_info_s aperture_info_d[] =                                      //��ͷֱ�������ݶ��ձ�
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

/* ���Դ�ӡ��ͷֱ�������ݶ��ձ� */
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

/* ��ȡ���״̬ */
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

/* ��ȡ��ͷ���� */
u8* get_aperture_data(u8 *line)
{
	u16 aperture_data = 0;
	u16 i;
	
	aperture_data = line[8-1] << 8;
	aperture_data = aperture_data | line[7-1];

	for(i=0; i<MAX_APERTURE_NUM; i++)                                             //��ѯ��ͷ���ձ�
	{
		if(aperture_info_d[i].data == aperture_data)
		{
			return aperture_info_d[i].aperture_info;
		}
	}
	
  return "error";
}

/* ����ͷ�������� */
void type_A_parse(u8 *line, u16 len, lens_type type, u8 print_switch)
{
  u8 i;
	u16 check_sum;

	len = len-3-2;																													      //ȥ��β���ͺ���λУ��λ
	check_sum = type;																														  //����У���
  
	for(i=0; i<len; i++)													                                //����һ��
	{
//		Lens_8517_info.data[i] = line[i+2];																					//������Чλ��ʼ��ֵ
		
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
		printf("A����:%02X У���:%02X %02X\r\n", type, check_sum%256, check_sum/256);
		printf("\r\n");
	}	

}

/* 75��ͷ���ͽ��� */
void type_E_parse(u8 *line, u16 len, lens_type type, u8 print_switch)
{
	u8 i;
	u16 check_sum;
	u8 out_string[10];

	len = len-3-2;																																//ȥ��β���ͺ���λУ��λ
	check_sum = type; 																														//����У���
	
	for(i=0; i<len; i++)																													//����һ��
	{
//		Lens_8517_info.data[i] = line[i+2]; 																						//������Чλ��ʼ��ֵ
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
		printf("E����:%02X	", type);
		//	printf("У���:%02X %02X ", check_sum%256, check_sum/256);
		//	printf("��ˮ��:%02X ", line[2+2]);
		printf("%s	", get_aperture_data(line));                                    //��ӡ��ͷģʽ
		
		get_camera_state(MF_AF, line[69-1], out_string);
		printf("%s	", out_string); 

		get_camera_state(AE, line[71-1], out_string);
		printf("%s	", out_string);       																					//��ӡ�ֶ��Զ�ģʽ
		i = 24;
		//	printf("δ֪1:%02X %02X %02X %02X ", line[2+i++], line[2+i++], line[2+i++], line[2+i++]);
		printf("\r\n\r\n");
	}
}

/* 30��ͷ���ͽ��� */
void type_F_parse(u8 *line, u16 len, lens_type type, u8 print_switch)
{
	u8 i;
	u16 check_sum;

	len = len-3-2;																																//ȥ��β���ͺ���λУ��λ
	check_sum = type; 																														//����У���
	
	
	for(i=0; i<len; i++)																													//����һ��
	{
		//Lens_8517_info.data[i] = line[i+2]; 																				//������Чλ��ʼ��ֵ

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
	printf("F����:%02X У���:%02X %02X\r\n", type, check_sum%256, check_sum/256);
	printf("\r\n");
}

}

/* ִ��һ�����ݽ��� */
void communication_code_execute_line(u8 package_line, print_format_e cmd, u8 para_a, u8 para_b)
{
//	u16 i,j;
	u8 *line;
	word data_head;                                                               //�����ݻ����д���ͷ����
	word data_tail;                                                               //�����ݻ����д���β����
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

	line = get_communication_data_buf_address(data_head);                         //��ȡ���ݻ���ȥ
 
	/* �����ж��Ƿ��а�ͷ */	
	if(line[0] != HEAD_DATA)										                                  //û��ͷ�˳�������
	{
		error_print(NO_Communication_HEAD);
		return;
	}
	
	/* �ж��Ƿ��а�β */
	if(line[len-1] != TAIL_DATA)										                              //û��β�˳�������
	{
		error_print(NO_Communication_TAIL);
		return;
	}	

	/* ��ȡ���� */
//	Lens_8517_info.type = line[1];	
	type = (lens_type)line[1];
	
	switch(type)
	{
		case type_A:																												        //0x0b����
		case type_B:																											       		//0x14����	
		case type_C:																															  //0x0a����
		case type_D:																															  //0x19����
			if(cmd == column_print_head_CMD)                                         		//��Ҫ��ӡʱ���ô�ӡ����
			{
				set_print_column_data_index(data_head, data_tail); 						  
			}
			if(cmd == row_print_head_CMD) 
			{			
				type_A_parse(line, len, type, para_a);	
			}
			break;
      
		case type_E:																	       			       			      //0x75����	
			if(cmd == column_print_75_CMD)                                         		//��Ҫ��ӡʱ���ô�ӡ����
			{
				set_print_column_data_index(data_head, data_tail); 						  
			}
			if(cmd == row_print_75_CMD) 
			{
				type_E_parse(line, len, type, para_a);                                  //��������
			}
			break;
			
		case type_F:																	       			       			      //0x30����
			if(cmd == column_print_30_CMD)                                         		//��Ҫ��ӡʱ���ô�ӡ����
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

/* �����ӡ */
void error_print(ERROR_CMD error_code)
{
	printf("ERROR:");
	switch(error_code)
	{
		case NO_Communication_HEAD:
			printf("[ͨѶ������ͷ]\r\n");
			break;
			
		case NO_Communication_TAIL:
			printf("[ͨѶ������β]\r\n");
      break;

		case NO_Communication_TYPE:
			printf("[ͨѶ����������]\r\n");
			break;  

		case U8_DATA_OUT:                                                           //u8�������ͽ�ҪԽ��
			printf("[U8_DATA_OUT]\r\n");
			break; 

		case DATA_ERROR:                                    
			printf("[DATA_ERROR]\r\n");
			break; 			

		default:
			break;
	}
}

/* 75��ͷ������ע�� */
void print_75_cmd_comment(u8 row_num, u8 data)
{
	u8 out_string[10];
	switch(row_num+1)
	{
    case 1:
			printf("��ͷ	");
			break;
			
    case 2:
			printf("�ֽ���	");			
			break;
      
    case 3:
			printf("��������	");			
			break;      
    case 4:
			printf("��������	");			
			break;      

    case 7:
			printf("��Ȧ	");			
			break;
    case 8:
			printf("��Ȧ	");			
			break;			

    case 5:
			printf("��ˮ��	");			
			break;

    case 27:
			printf("δ֪1	");			
			break;
    case 28:
			printf("δ֪1	");			
			break;
    case 29:
			printf("δ֪1	");			
			break;
    case 30:
			printf("δ֪1	");	
			break;	


    case 40:
			printf("λ��1	");	
    case 41:
			printf("λ��1	");			
			break;
    case 42:
			printf("λ��1	");			
			break;
    case 43:
			printf("λ��1	");			
			break;
    case 44:
			printf("λ��1	");	
			break;	
			

    case 45:
			printf("�仯1	");			
			break;
    case 46:
			printf("�仯1	");			
			break;
    case 47:
			printf("�仯1	");			
			break;
    case 48:
			printf("�仯1	");	
			break;	
		case 49:
			printf("�仯1 "); 		
			break;
		case 50:
			printf("�仯1 "); 
			break;	


    case 69:
    	get_camera_state(MF_AF, data, out_string);                                //��ӡ�Խ�ģʽ��Ϣ
			printf("AF/MF	%s	", out_string);	
			break;

    case 71:	
    	get_camera_state(AE, data, out_string);                                   //��ӡ�Խ��Ƿ�����
			printf("AE	%s	", out_string);	
			break;			

		case 96:
			printf("�仯2 "); 
			break;	


    case 97:
			printf("λ��2	");			
			break;
    case 98:
			printf("λ��2	");			
			break;
    case 99:
			printf("λ��2	");			
			break;
    case 100:
			printf("λ��2	");	
			break;	
			
		case 101:
			printf("�仯3 "); 
			break;	

		case 106:
			printf("�仯4 "); 
			break;		
		case 107:
			printf("�仯4 "); 
			break;	
		case 108:
			printf("�仯4 "); 
			break;				

		case 112:
			printf("�仯5 "); 
			break;		
		case 113:
			printf("�仯5 "); 
			break;	
		case 114:
			printf("�仯5 "); 
			break;	
			

    case 115:
			printf("У���	");			
			break;
    case 116:
			printf("У���	");	
			break;
			
    case 117:
			printf("��β	");	
			break;			
			
		default:
			break;
	}
}

/* 30��ͷ������ע�� */
void print_30_cmd_comment(u8 row_num, u8 data)
{
	switch(row_num+1)
	{
    case 1:
			printf("��ͷ	");
			break;
			
    case 2:
			printf("�ֽ���	");			
			break;
      
    case 3:
			printf("��������	");			
			break;      
    case 4:
			printf("��������	");			
			break;     		

    case 5:
			printf("��ˮ��	");			
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
			printf("У��	");		
			break;
    case 47:
			printf("У��	");			
			break;
    case 48:
			printf("��β	");
			break;	
	
		default:
			break;
	}
}

/* ��ʼ����ӡ��ʽ */
void init_print(void)
{
	print_pare.pare1	= 3;                                                        //Ĭ�ϴ�0�п�ʼ��ӡ
	print_pare.pare2 = 1;                                                         //Ĭ�ϴ�ӡ�������
	print_pare.pare3 = 0;                                                         //Ĭ��HEX���
	print_pare.pare4 = 0;
	print_pare.cmd = row_print_75_CMD;                                            //Ĭ�����д�ӡ75��ͷ����
	
	memset(&print_data, 0, sizeof(print_data));	
}

/* ���ô�ӡ��ʽ */
void set_print_format(print_pare_s *print_pare_p)
{
	print_pare.pare1 = print_pare_p->pare1;
	print_pare.pare2 = print_pare_p->pare2;
	print_pare.pare3 = print_pare_p->pare3;
	print_pare.pare4 = print_pare_p->pare4;	
	print_pare.cmd = print_pare_p->cmd;
}

/* ��ȡ��ӡ��ʽ */
void get_print_format(print_pare_s *print_pare_p)
{
	print_pare_p->pare1 = print_pare.pare1;
	print_pare_p->pare2 = print_pare.pare2;	
	print_pare_p->pare3 = print_pare.pare3;
	print_pare_p->pare4 = print_pare.pare4;		
	print_pare_p->cmd = print_pare.cmd;
}

/* ���ô�ӡ�������� */
void set_print_column_data_index(word head, word tail)
{
	print_data.head[print_data.num] = head;
	print_data.tail[print_data.num] = tail;
	print_data.num++;	
}

/* ��ȡ��ӡ�������� */
word* get_print_column_data_index(u8 *column_num, u8 *row_num)
{
	*column_num = print_data.num;
	*row_num = print_data.tail[0] - print_data.head[0];
	return print_data.head; 
}


/* ��ӡ�ɼ���ͨѶ���� */
void print_column_data(u8 line_start, u8 line_end, u8 num_sys)
{
	u8 i,j;
  u8 *line[PACKAGE_REV_NUM];
//  word head[120];

  u8 column_num;																							                  //����
  u8 row_num;	

	get_print_column_data_index(&column_num, &row_num);
	
	if(line_end)
	{
		row_num = line_end;
	}
//	else
//	{
//		row_num = print_data.tail[0] - print_data.head[0];												  				//�����ӡ����		
//	}
	
//	column_num = print_data.num;																								  //������ֵ
	
	printf("����%d	����%d	��������%d\r\n", row_num, column_num, print_pare.cmd);
  
	printf("LINE	"); 																													  //��ӡ����Ϣ����ֵ��ӡָ��
	for(i=0; i< column_num; i++)																								  
	{
		printf("%d	", i+1);
		line[i] = get_communication_data_buf_address(print_data.head[i]); 
//		line[i] = get_communication_data_buf_address(head[i]);           
	}
	printf("fun	");
	printf("state	");
	printf("\r\n");

	for(i=line_start; i<row_num; i++)																							//��ӡ����
	{ 
		printf("[ %d ]	", i+1);																								    //��ӡ����Ϣ
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

		if(print_pare.cmd == column_print_75_CMD)                                   //��ӡ75��ͷ���ע��Ϣ
		{
			print_75_cmd_comment(i, line[column_num-1][i]); 												
		}	
		if(print_pare.cmd == column_print_30_CMD)                                   //��ӡ30��ͷ���ע��Ϣ
		{
			print_30_cmd_comment(i, line[column_num-1][i]); 													
		}		
		
		printf("\r\n");
	}

	memset(&print_data, 0, sizeof(print_data));                                   //�����ӡ����׼����һ�δ�ӡ

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
			printf("��ӡ������Ϣ	��ʼ��%d	������%d ��ӡ����%s\r\n", 
								print_pare.pare1, print_pare.pare2, print_pare.pare3?"DEC":"HEX");				
			/* �����ӡ����û�и�ִֵ�н������븳ֵ���� */
			if(!print_data.num)
			{
				for(i=0; i<DMA_rev_package_num; i++)																    //����ÿ������
				{
					communication_code_execute_line(i, 
                     print_pare.cmd, print_pare.pare1, print_pare.pare2);				//����1:��ӡ���ݻ�����Ϣ
				}
					HAL_Delay(10);
			}
			print_column_data(print_pare.pare1, print_pare.pare2, print_pare.pare3);	//��ӡ����
			break;

		case row_print_head_CMD:	
		case row_print_30_CMD:
		case row_print_75_CMD:
			printf("��ӡ������Ϣ	��ӡ��ʽ%02X\r\n", print_pare.pare1);
			for(i=0; i<DMA_rev_package_num; i++)																		  //����ÿ������
			{
				communication_code_execute_line(i, print_pare.cmd, print_pare.pare1, print_pare.pare2);
			} 
			break;
			
	}

	
}




































