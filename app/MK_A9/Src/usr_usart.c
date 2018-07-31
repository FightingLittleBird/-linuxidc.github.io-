#include "usr_usart.h"

u8 USART_RX_BUF[USART_REC_LEN];                                                 //����1���ջ���     
u16 USART_RX_STA=0;     
u8 aRxBuffer[RXBUFFERSIZE];
u8 usart1_rev_flg = 0;

u8 USART2_RX_BUF[USART_REC_LEN];                                                //����2���ջ���     
u16 USART2_RX_STA=0;     
u8 aRxBuffer2[RXBUFFERSIZE];
u8 usart2_rev_flg = 0;

u8 DMA_rx_len=0;                                                               //DMA���յ����ݳ���
u8 DMA_recv_end_flag=0;                                                        //DMA������ɱ�־
u8 DMA_rcv_buffer[128];                                                         //DMA���ջ������128�ֽ�

///* ���ڻص����� */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart->Instance==USART2)								//����Ǵ���1
//	{
//		if((USART2_RX_STA&0x8000)==0)						//����δ���
//		{
//			if(USART2_RX_STA&0x4000)							//���յ���0x0d
//			{
//				if(aRxBuffer2[0]!=0x0a)USART2_RX_STA=0;		//���մ���,���¿�ʼ
//				else USART2_RX_STA|=0x8000;					//��������� 		
//				
//			}
//			else 											//��û�յ�0X0D
//			{	
//				if(aRxBuffer2[0]==0x0d)USART2_RX_STA|=0x4000;
//				else
//				{
//					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=aRxBuffer2[0] ;
//					USART2_RX_STA++;
//					if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//				}		 
//			}
//		}
//	}
//}

///* �����ַ��� */
//void Usart_SendString(uint8_t *str)
//{
//	unsigned int k=0;
//	
//	do 
//	{
//		HAL_UART_Transmit(&huart2, str + k, 1, 1000);
//		k++;
//	} while(*(str + k)!='\0');
//}


/* �ض���c�⺯�� */
int fputc(int ch, FILE *f)
{
  LL_USART_TransmitData8 (USART2, ch);
  while(LL_USART_IsActiveFlag_TC(USART2) == 0);
  
//  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0x0001);
  return ch;
}

int fgetc(FILE * f)
{
//  uint8_t ch = 0;
//  HAL_UART_Receive(&huart2, &ch, 1, 0xffff);
//  return ch;
	return LL_USART_ReceiveData8(USART2);
}

/* ���ڽ������ݷ��͸����� */
void uart2_irq_handler(void)
{
  u8 tmp;
//    u8 len=0;
  
	if(LL_USART_IsActiveFlag_RXNE(USART2))					          //�ȴ�����
  { 
		tmp = LL_USART_ReceiveData8(USART2);
//		LL_USART_TransmitData8(USART2, tmp);

		if((USART2_RX_STA&0x8000)==0) 												//����δ���
		{
			if(USART2_RX_STA&0x4000)														//���յ���0x0d
			{
				if(tmp!=0x0a)
				{
					USART2_RX_STA=0; 																//���մ���,���¿�ʼ
				}
				else
				{
					USART2_RX_STA|=0x8000; 													//���������	
					usart2_rev_flg = 1;
					//printf("res:%s\r\n", USART_RX_BUF);  
				}
			}
			else																								//��û�յ�0X0D
			{ 
				if(tmp==0x0d)
				{
					USART2_RX_STA|=0x4000;
				}
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF] = tmp;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART_REC_LEN-1))
					{
						USART2_RX_STA=0;															//�������ݴ���,���¿�ʼ����	
					}
				} 	 
			}
		}
  }
}

///* ���ڽ������ݷ��͸����� */
//void uart2_irq_handler(void)
//{
//  u32 timeout=0;
//  u32 maxDelay=0x1FFFF;
////    u8 len=0;
//	
//  timeout=0;
//  while (HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY)					          //�ȴ�����
//  { 
//	  timeout++;																                                  //��ʱ����
//	  if(timeout>maxDelay) break;	  
//  }
//   
//  timeout=0;
//  while(HAL_UART_Receive_IT(&huart2, (u8 *)aRxBuffer2, RXBUFFERSIZE) != HAL_OK)	//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
//  {
//   timeout++;																	                                  //��ʱ����
//   if(timeout>maxDelay) break;	  
//  }
//  
//  if(USART2_RX_STA&0x8000)								                                      //���յ����ݣ����ҽ�������֪ͨ��������Ч
//  { 
////		len=USART_RX_STA&0x3fff;											                            //�õ��˴ν��յ������ݳ���
//		//USART_RX_STA=0;
//		usart2_rev_flg = 1; 
//		//printf("res:%s\r\n", USART_RX_BUF);  
//        
//  }
//
//}

/* ���ڽ������ݷ��͸����� */
void uart1_irq_handler(void)
{
//	if(LL_USART_IsActiveFlag_IDLE(USART1) != RESET)
//	{
//		LL_USART_ClearFlag_IDLE(USART1);
//		//HAL_UART_DMAStop(&huart1);
//		DMA_rx_len =  DMA_BUFFER_SIZE - hdma_usart1_rx.Instance->CNDTR; 
////		  printf("rx_len interrupt =%d\r\n",DMA_rx_len);
//		DMA_recv_end_flag = 1;
//			//HAL_UART_Receive_DMA(&huart1,DMA_rcv_buffer,DMA_BUFFER_SIZE);			
//	}
	
	if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
  { 
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
			
		HAL_UART_DMAStop(&huart1);
		DMA_rx_len =  DMA_BUFFER_SIZE - hdma_usart1_rx.Instance->CNDTR; 
//		  printf("rx_len interrupt =%d\r\n",DMA_rx_len);
		DMA_recv_end_flag = 1;
			//HAL_UART_Receive_DMA(&huart1,DMA_rcv_buffer,DMA_BUFFER_SIZE);	
  }
}