#ifndef __USR_USART_H
#define __USR_USART_H

#include "MK_A9.h"

#define RXBUFFERSIZE	1
#define USART_REC_LEN	200

#define DMA_BUFFER_SIZE 128

extern u8 aRxBuffer[RXBUFFERSIZE];  
extern u8 USART_RX_BUF[USART_REC_LEN];
extern u16 USART_RX_STA;
extern u8 usart1_rev_flg;

extern u8 aRxBuffer2[RXBUFFERSIZE];
extern u8 USART2_RX_BUF[USART_REC_LEN];
extern u16 USART2_RX_STA;
extern u8 usart2_rev_flg;

extern u8 DMA_rx_len;                                                          //DMA接收的数据长度
extern u8 DMA_recv_end_flag;                                                   //DMA接收完成标志
extern u8 DMA_rcv_buffer[DMA_BUFFER_SIZE]; 

void uart1_irq_handler(void);
void uart2_irq_handler(void);
#endif
