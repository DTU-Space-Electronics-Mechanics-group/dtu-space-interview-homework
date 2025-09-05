#include "dbg.h"
#include "board.h"

void dbg_terminal_cyclic(void){
	uint8_t byte_buf;
	int byte_read;
	
	byte_read = board_uart_read(&byte_buf);

	if (byte_read != 0)
	{
		dbg_handle_input(byte_buf);
	}	
}
