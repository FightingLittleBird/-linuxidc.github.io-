#include "usr_uart_dma.h"

static word communication_data_index = 0;                                        //串口数据索引 
static u8 communication_data_buf[PACKAGE_DATA_SIZE];                                   //包存储数据

u8 DMA_rev_package_num = 0;
word package_index_head[PACKAGE_REV_NUM];
word package_index_tail[PACKAGE_REV_NUM];

/* 获取通讯数据缓存区数据 */
u8 get_communication_data_buf(word index)
{
	return communication_data_buf[index];
}

/* 获取通讯数据缓存区地址 */
u8* get_communication_data_buf_address(word index)
{
	return &communication_data_buf[index];
}


/* 清除通讯数据缓存区地址 */
void clear_communication_data_buf(void)
{
	memset(communication_data_buf, 0, sizeof(communication_data_buf));
}


/* 设置串口缓存数据索引数据 */
void set_package_index(u8 index, u8 len, word tail)
{
//  printf("index=%d head=%d tail=%d\r\n", index, head, tail);
	package_index_head[index] = tail-len;
	package_index_tail[index] = tail;

	DMA_rev_package_num++;                                                    //更新接收包变量
}

/* 获取串口缓存数据索引数据 */
word get_package_index(u8 index, Package_Index_CMD cmd)
{
	word value;
	
	switch(cmd)
	{
		case HEAD:
			value = package_index_head[index];
			break;
		case TAIL:
			value = package_index_tail[index]; 
			break;
	}

	return value;
}

/* 获取通讯缓存区索引 */
word get_communication_data_index(void)
{
	return communication_data_index;
}

/* 数据存入通讯缓存器 */
void set_communication_data(word index, u8 *data, u8 len)
{
  u8 i;
  
	for(i=0; i<len; i++)
	{
		communication_data_buf[index + i]	= data[i];	
	} 

  communication_data_index = index + len;         //更新通讯数据索引变量
}

/* 清除通讯缓存区索引 */
void clear_communication_data_index(void)
{
	communication_data_index = 0;	
}

Rev_State_E Uart_Receive_DMA(void)
{
  /* 串口2DMA方式接收高速数据 */  
  if(get_communication_data_index()> PACKAGE_DATA_SIZE)                         //通讯数据缓存器满报错
  {
    clear_communication_data_index();
    return OUT;
  }

  if(DMA_rev_package_num >= PACKAGE_REV_NUM)
  {
		return END;
  }

  
  HAL_UART_Receive_DMA(&huart1, DMA_rcv_buffer, DMA_BUFFER_SIZE);						    //DMA接收
	
  if(DMA_recv_end_flag ==1)																					            //接收完成标志	
	{
    if(DMA_rev_package_num < PACKAGE_REV_NUM)                                   //接收多少包数据
    {   
      set_communication_data(get_communication_data_index(), 									  //存储通讯数据
      												DMA_rcv_buffer, DMA_rx_len);

      set_package_index(  DMA_rev_package_num,                                  //存储每包数据头尾索引数据
                          DMA_rx_len,
                          get_communication_data_index());    
      DMA_rx_len = 0;
    }    
    
		DMA_recv_end_flag = 0; 
	} 
	return START;
}
