#include "gpio_spi.h"

//#define SPI_CPHA			1													//�����ؼ�⻹���½��ؼ��
//#define SPI_CPOL			1													//�����ؼ�⻹���½��ؼ��

//u8 spi_buf[4];                                                                  //spi���鷢�ͻ�������
//u8 spi_group = 0;                                                               //spi�ڼ���                                               
//u8 spi_bit = 0;                                                                 //spi�ڼ�λ
//u8 spi_clk_last = SPI_CPOL;


void spi_init(void)
{
//  spi_buf[0] = 0xfc;
//  spi_buf[1] = 0xc0;
//  spi_buf[2] = 0xc2;
//  spi_buf[3] = 0xff; 
//  
//  HAL_GPIO_WritePin(SPI1_DAT_GPIO_Port, SPI1_DAT_Pin, GPIO_PIN_SET);
  
}

/* С��200ns poll */
void spi_clk_scan(void)
{
//	u8 spi_clk_new;
//	
//	spi_clk_new = HAL_GPIO_ReadPin(SPI1_SCK_GPIO_Port, SPI1_SCK_Pin);			//������
//	;;		
//	if(spi_clk_new == HAL_GPIO_ReadPin(SPI1_SCK_GPIO_Port, SPI1_SCK_Pin))
//	{
//		if(spi_clk_last != spi_clk_new)											//�����ش���
//		{
//			if(spi_clk_new == SPI_CPHA) 										//������
//			{
//
//			}
//			else
//			{
//				spi_query_send_bit();				
//			}
//			
//			spi_clk_last = spi_clk_new;
//		}
//	}
}

/* SCK���������ػ����½��ز�ѯ�������� */
void spi_query_send_bit(void)
{
  
////    if (spi_buf[spi_group] & (0x80 >> spi_bit))
//	if (spi_buf[spi_group] & (0x01 << spi_bit))
//    {
//    	HAL_GPIO_WritePin(SPI1_DAT_GPIO_Port, SPI1_DAT_Pin, GPIO_PIN_SET);
//    	HAL_GPIO_WritePin(SPI1_DAT_GPIO_Port, SPI1_DAT_Pin, GPIO_PIN_SET);   
//    	HAL_GPIO_WritePin(SPI1_DAT_GPIO_Port, SPI1_DAT_Pin, GPIO_PIN_SET);
//    	HAL_GPIO_WritePin(SPI1_DAT_GPIO_Port, SPI1_DAT_Pin, GPIO_PIN_SET);         
//    }
//    else
//    {
//    	HAL_GPIO_WritePin(SPI1_DAT_GPIO_Port, SPI1_DAT_Pin, GPIO_PIN_RESET);
//    	HAL_GPIO_WritePin(SPI1_DAT_GPIO_Port, SPI1_DAT_Pin, GPIO_PIN_RESET); 
//    	HAL_GPIO_WritePin(SPI1_DAT_GPIO_Port, SPI1_DAT_Pin, GPIO_PIN_RESET);
//    	HAL_GPIO_WritePin(SPI1_DAT_GPIO_Port, SPI1_DAT_Pin, GPIO_PIN_RESET);         
//    }  
//
//	spi_bit++;
//
//	if(spi_bit >= 8)
//	{
//        HAL_GPIO_WritePin(SPI1_DAT_GPIO_Port, SPI1_DAT_Pin, GPIO_PIN_SET);
//		spi_bit = 0;
//		spi_group++;
//	}
//
//	if(spi_group >= 4)
//	{
//        HAL_GPIO_WritePin(SPI1_DAT_GPIO_Port, SPI1_DAT_Pin, GPIO_PIN_SET);
//		spi_group = 0;
//	}
  
}