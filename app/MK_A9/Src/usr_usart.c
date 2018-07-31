#include "usr_usart.h"

u8 USART_RX_BUF[USART_REC_LEN];                                                 //串口1接收缓存     
u16 USART_RX_STA=0;     
u8 aRxBuffer[RXBUFFERSIZE];
u8 usart1_rev_flg = 0;

u8 USART2_RX_BUF[USART_REC_LEN];                                                //串口2接收缓存     
u16 USART2_RX_STA=0;     
u8 aRxBuffer2[RXBUFFERSIZE];
u8 usart2_rev_flg = 0;

u8 DMA_rx_len=0;                                                               //DMA接收的数据长度
u8 DMA_recv_end_flag=0;                                                        //DMA接收完成标志
u8 DMA_rcv_buffer[128];                                                         //DMA接收缓存最大128字节

///* 串口回调函数 */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart->Instance==USART2)								//如果是串口1
//	{
//		if((USART2_RX_STA&0x8000)==0)						//接收未完成
//		{
//			if(USART2_RX_STA&0x4000)							//接收到了0x0d
//			{
//				if(aRxBuffer2[0]!=0x0a)USART2_RX_STA=0;		//接收错误,重新开始
//				else USART2_RX_STA|=0x8000;					//接收完成了 		
//				
//			}
//			else 											//还没收到0X0D
//			{	
//				if(aRxBuffer2[0]==0x0d)USART2_RX_STA|=0x4000;
//				else
//				{
//					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=aRxBuffer2[0] ;
//					USART2_RX_STA++;
//					if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
//				}		 
//			}
//		}
//	}
//}

///* 发送字符串 */
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


/* 重定向c库函数 */
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

/* 串口结束数据发送给任务 */
void uart2_irq_handler(void)
{
  u8 tmp;
//    u8 len=0;
  
	if(LL_USART_IsActiveFlag_RXNE(USART2))					          //等待就绪
  { 
		tmp = LL_USART_ReceiveData8(USART2);
//		LL_USART_TransmitData8(USART2, tmp);

		if((USART2_RX_STA&0x8000)==0) 												//接收未完成
		{
			if(USART2_RX_STA&0x4000)														//接收到了0x0d
			{
				if(tmp!=0x0a)
				{
					USART2_RX_STA=0; 																//接收错误,重新开始
				}
				else
				{
					USART2_RX_STA|=0x8000; 													//接收完成了	
					usart2_rev_flg = 1;
					//printf("res:%s\r\n", USART_RX_BUF);  
				}
			}
			else																								//还没收到0X0D
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
						USART2_RX_STA=0;															//接收数据错误,重新开始接收	
					}
				} 	 
			}
		}
  }
}

///* 串口结束数据发送给任务 */
//void uart2_irq_handler(void)
//{
//  u32 timeout=0;
//  u32 maxDelay=0x1FFFF;
////    u8 len=0;
//	
//  timeout=0;
//  while (HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY)					          //等待就绪
//  { 
//	  timeout++;																                                  //超时处理
//	  if(timeout>maxDelay) break;	  
//  }
//   
//  timeout=0;
//  while(HAL_UART_Receive_IT(&huart2, (u8 *)aRxBuffer2, RXBUFFERSIZE) != HAL_OK)	//一次处理完成之后，重新开启中断并设置RxXferCount为1
//  {
//   timeout++;																	                                  //超时处理
//   if(timeout>maxDelay) break;	  
//  }
//  
//  if(USART2_RX_STA&0x8000)								                                      //接收到数据，并且接收任务通知的任务有效
//  { 
////		len=USART_RX_STA&0x3fff;											                            //得到此次接收到的数据长度
//		//USART_RX_STA=0;
//		usart2_rev_flg = 1; 
//		//printf("res:%s\r\n", USART_RX_BUF);  
//        
//  }
//
//}

/* 串口结束数据发送给任务 */
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