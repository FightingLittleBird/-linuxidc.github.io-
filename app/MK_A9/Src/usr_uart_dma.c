#include "usr_uart_dma.h"

static word communication_data_index = 0;                                        //������������ 
static u8 communication_data_buf[PACKAGE_DATA_SIZE];                                   //���洢����

u8 DMA_rev_package_num = 0;
word package_index_head[PACKAGE_REV_NUM];
word package_index_tail[PACKAGE_REV_NUM];

/* ��ȡͨѶ���ݻ��������� */
u8 get_communication_data_buf(word index)
{
	return communication_data_buf[index];
}

/* ��ȡͨѶ���ݻ�������ַ */
u8* get_communication_data_buf_address(word index)
{
	return &communication_data_buf[index];
}


/* ���ͨѶ���ݻ�������ַ */
void clear_communication_data_buf(void)
{
	memset(communication_data_buf, 0, sizeof(communication_data_buf));
}


/* ���ô��ڻ��������������� */
void set_package_index(u8 index, u8 len, word tail)
{
//  printf("index=%d head=%d tail=%d\r\n", index, head, tail);
	package_index_head[index] = tail-len;
	package_index_tail[index] = tail;

	DMA_rev_package_num++;                                                    //���½��հ�����
}

/* ��ȡ���ڻ��������������� */
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

/* ��ȡͨѶ���������� */
word get_communication_data_index(void)
{
	return communication_data_index;
}

/* ���ݴ���ͨѶ������ */
void set_communication_data(word index, u8 *data, u8 len)
{
  u8 i;
  
	for(i=0; i<len; i++)
	{
		communication_data_buf[index + i]	= data[i];	
	} 

  communication_data_index = index + len;         //����ͨѶ������������
}

/* ���ͨѶ���������� */
void clear_communication_data_index(void)
{
	communication_data_index = 0;	
}

Rev_State_E Uart_Receive_DMA(void)
{
  /* ����2DMA��ʽ���ո������� */  
  if(get_communication_data_index()> PACKAGE_DATA_SIZE)                         //ͨѶ���ݻ�����������
  {
    clear_communication_data_index();
    return OUT;
  }

  if(DMA_rev_package_num >= PACKAGE_REV_NUM)
  {
		return END;
  }

  
  HAL_UART_Receive_DMA(&huart1, DMA_rcv_buffer, DMA_BUFFER_SIZE);						    //DMA����
	
  if(DMA_recv_end_flag ==1)																					            //������ɱ�־	
	{
    if(DMA_rev_package_num < PACKAGE_REV_NUM)                                   //���ն��ٰ�����
    {   
      set_communication_data(get_communication_data_index(), 									  //�洢ͨѶ����
      												DMA_rcv_buffer, DMA_rx_len);

      set_package_index(  DMA_rev_package_num,                                  //�洢ÿ������ͷβ��������
                          DMA_rx_len,
                          get_communication_data_index());    
      DMA_rx_len = 0;
    }    
    
		DMA_recv_end_flag = 0; 
	} 
	return START;
}
