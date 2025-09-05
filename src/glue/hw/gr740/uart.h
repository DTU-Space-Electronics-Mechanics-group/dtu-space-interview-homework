#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdlib.h>

#include <drv/apbuart.h>
#include "apbuart_driver.h"

uint32_t init_apbuart(struct apbuart_priv ** apbuart_dev_p);

#endif // UART_H