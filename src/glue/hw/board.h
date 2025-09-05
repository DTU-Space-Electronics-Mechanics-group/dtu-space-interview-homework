#ifndef BOARD_H_
#define BOARD_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "clock_gate.h"
#include "uart.h"

typedef struct board_architecture
{   
	struct clkgate_priv * clkgate_dev_p[2];
	struct apbuart_priv * apbuart_dev_p;
	uint32_t * sys_1ms_tick_p;   /*!< Pointer to the system 1ms tick counter*/
}board_architecture_t;

board_architecture_t * open_board(void);
extern void init_board_architecture(board_architecture_t * board_architecture);

int board_uart_read(uint8_t * byte_buf);

#endif /* BOARD_H_ */