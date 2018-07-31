#include "MK_A9.h"

//static u8 time_count = 0;
unsigned long ulIdleCycleCount = 0UL;

void usr_init(void)
{
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);                                  //串口1空闲中断
	HAL_UART_Receive_DMA(&huart1, (u8 *)aRxBuffer, RXBUFFERSIZE);                 //串口1 DMA接收	

//	HAL_UART_Receive_IT(&huart2, (u8 *)aRxBuffer2, RXBUFFERSIZE);

//	if(HAL_TIM_Base_Start_IT(&htim1) != HAL_OK)
//	{
//		/* Starting Error */
//		while(1);
//	}
	
//	flash_test();  

//	LL_USART_EnableIT_IDLE(USART1);
//	LL_USART_EnableDMAReq_RX(USART1);
//	LL_USART_EnableIT_PE(USART1);
	
	LL_USART_EnableIT_RXNE(USART2);
	LL_USART_EnableIT_PE(USART2);
	
	printf("DATA2017.12.22  sys start!\r\n");
	spi_init();
	
	init_print();
		
//	HAL_Delay(500);
}

void usr_loop(void)
{

  LL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);  
  LL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin); 
	protocol_process(); 	
//	usr_key_process();
}

void uIdeHook(void)
{
	ulIdleCycleCount++;
}

