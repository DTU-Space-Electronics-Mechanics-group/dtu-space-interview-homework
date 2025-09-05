#include "board.h"

static board_architecture_t board_architecture;

board_architecture_t * open_board(void)
{
	return &board_architecture;
}

void init_board_architecture(board_architecture_t * board_architecture)
{
	// Initialize clock gating for all needed peripherals
	init_clockgate(board_architecture->clkgate_dev_p, clkgate0_enable_table, get_size_of_clkgate0_enable_table(), 0);

	// Initialize the APBUART
	init_apbuart(&(board_architecture->apbuart_dev_p));
}

int board_uart_read(uint8_t * byte_buf)
{
	return apbuart_read(board_architecture.apbuart_dev_p, byte_buf, 1);
}