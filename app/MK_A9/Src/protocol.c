#include "protocol.h"

uint8_t line[250]={0};			
uint8_t char_counter = 0;
u8 get_data_flg = 0;

typedef void (*CallBack)(u8 *);			



/* 用户程序 */
void print_text(u8* s)
{
	printf((char *)s);
}

/* 第三方程序 */
void call_print_text(CallBack function, u8* s)
{
	function(s);
}

void send_package(void)
{
  uint8_t len = 4;                                                            //发送包长度
  uint8_t *buf;                                                               //发送包缓存区
  uint8_t i;
  buf =(u8*)&package;                                                         //强转

// 	u8 rx_data[4];
//    u8 key_value;
    
	for(i = 0; i<len; i++)
	{
		printf("0x%02X ", buf[i]);	
		
	}
    printf("\r\n");	    

//	key_value = HAL_GPIO_ReadPin(SPI1_CS_GPIO_Port, SPI1_CS_Pin);
//	printf("key_value%d\r\n", key_value);
     		
//	SPI1_write_buf(buf, len); 
}

int cmd_a_fun(u8 *str, u8 *out)
{
//	printf((char *)str);
	str = str+2;																															    //过滤第一个数据
	gc_execute_line(str);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
//	LL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//	LED1_GPIO_Port->BSRR = LED1_Pin;//GPIOA->ODR |= StepMotor_IN1_Pin;

	printf((char *)out);
  return 0;
}

int cmd_b_fun(u8 *str, u8 *out)
{
	printf((char *)str);

//	LED1_GPIO_Port->BRR  = LED1_Pin;	
	
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	aperture_data_print();
	printf((char *)out);
	return 0;
}


int cmd_c_fun(u8 *str, u8 *out)
{
//	printf((char *)str);
//	printf("开始采集"); 
	printf(">"); 
	DISABLE_INTERRUPTS();
	clear_communication_data_index(); 									                          //清除通讯缓存器数据索引
	DMA_rev_package_num = 0;
	ENABLE_INTERRUPTS();
	get_data_flg ++;
	if(get_data_flg > 10)
	{
		get_data_flg = 0;
		printf("wait\r\n");
		
	}
//	printf((char *)out);
	return 0;
}

int cmd_d_fun(u8 *str, u8 *out)
{
  u16 i;
  u8 *p;

  printf((char *)str);
  printf("打印采集缓存区数据:");

  p = get_communication_data_buf_address(0);
  
	for(i=0; i<PACKAGE_DATA_SIZE; i++)
	{
		printf("%02x ", p[i]); 
	}
	printf("\r\n\r\n"); 
	printf((char *)out);
  return 0;
}

int cmd_e_fun(u8 *str, u8 *out)
{
//  u16 i;
  
	printf((char *)str);

	printf("清除缓存器:"); 
	
	clear_communication_data_buf();
	
//	for(i=0; i<PACKAGE_DATA_SIZE; i++)
//	{
//		printf("%02x ", get_communication_data_buf(i)); 	
//	} 
	clear_communication_data_index(); 														//清除通讯缓存器数据索引
	DMA_rev_package_num = 0;
	printf("\r\n\r\n"); 

	printf((char *)out);

  return 0;
}

int cmd_f_fun(u8 *str, u8 *out)
{
  u16 i,j;
  
	printf((char *)str);
	for(i=0; i<DMA_rev_package_num; i++)
	{
		for(j=package_index_head[i]; j<package_index_tail[i]; j++)
		{
			printf("%02x ", get_communication_data_buf(j));  
		}
		printf("\r\n\r\n");
	} 
	printf((char *)out);
  return 0;
}

int cmd_h_fun(u8 *str, u8 *out)
{
  u16 i;
  
	printf((char *)str);
	printf("解析串口数据");
	
	for(i=0; i<DMA_rev_package_num; i++)
	{
		communication_code_execute_line(i, row_print_75_CMD, PRINT_INFO, 0);
	}  
	HAL_Delay(10);

	//clear_communication_data_buf();
	//clear_communication_data_index(); 
  
	printf((char *)out);
  return 0;
}

int cmd_i_fun(u8 *str, u8 *out)
{
	printf((char *)str);
	printf((char *)out);
  return 0;
}

int cmd_help_fun(u8 *str, u8 *out)
{
	printf("hellp:\r\n");
	printf("A 设置打印格式\r\n");
	printf("B 对焦环位置打印\r\n");
	printf("C 开始采集数据\r\n");
	printf("D 打印采集数据\r\n");
	printf("E 清除缓存器\r\n");
	printf("F 分组打印采集数据\r\n");
	printf("H 横排打印解析数据\r\n");
	printf("I NULL\r\n");
  return 0;
}


static CMD_T cmd_proc[] =
{
	{"A",	cmd_a_fun},			
	{"B",	cmd_b_fun},			
	{"C",	cmd_c_fun},	
	{"D",	cmd_d_fun},			
	{"E",	cmd_e_fun},			
	{"F",	cmd_f_fun},	
	{"H",	cmd_h_fun},			
	{"I",	cmd_i_fun},		
	{"?",	cmd_help_fun},		
};

static const int MAX_CMD_NUM = (sizeof(cmd_proc)/sizeof(cmd_proc[0]));

/*执行一行协议命令*/
uint8_t protocol_execute_line(u8 *line) 
{
	u16 i;
  //printf("data:%s\r\n", line);
	for(i=0; i<MAX_CMD_NUM; i++)																									//执行命令函数
	{		
		if(line[0]==*cmd_proc[i].cmd)
		{
			cmd_proc[i].cmd_handler(line, "end\r\n");
			return 0;
		}	
	}
	
  if (line[0] == 0)					        		        		        		        	      //第一个字节等于0表示空行或者注释行
	{
  }

	else if (line[0] == '$') 		      		        		        		        	      
	{
		call_print_text(print_text, cmd_proc[0].cmd);
  }    
	
	return 0;
}

/* 串口命令和数据采集处理 */
void protocol_process(void)
{
	Rev_State_E	state;
  
  /* 串口2接收命令 */
  if(usart2_rev_flg)
  {
    usart2_rev_flg = 0;
  	protocol_execute_line(USART2_RX_BUF);																		    //执行命令解析
		USART2_RX_STA=0;
		memset(USART2_RX_BUF,0,USART_REC_LEN);  
  }	

	/* 串口DMA开始采集数据 */
	if(get_data_flg)																															
	{
		state = Uart_Receive_DMA(); 
		
		if(state == END)
		{
			get_data_flg --;
			if(get_data_flg <= 0)
			{
				get_data_flg = 0;
			}
			printf("采集结束\r\n");
			print_communication_parse();                                              //打印解析数据   
    }
		if(state == OUT)
		{
			printf("data out!\r\n");	
		}
		
	}
		
	
}

