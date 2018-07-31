#ifndef __GPIO_SPI_H
#define __GPIO_SPI_H

#include "MK_A9.h"

void spi_init(void);
void spi_query_send_bit(void);
void spi_clk_scan(void);

#endif