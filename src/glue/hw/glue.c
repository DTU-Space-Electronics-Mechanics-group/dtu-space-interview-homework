#include <stddef.h>

#include "glue.h"
#include "board.h"

#include "dbg.h" // REMOVE IN FINAL RELEASE

board_architecture_t * board_architecture = NULL;

void glue_main_init(uint32_t * sys_1ms_tick_p)
{
    board_architecture = open_board();
	if(board_architecture == NULL)
	{
		exit(1);
	}
	board_architecture->sys_1ms_tick_p = sys_1ms_tick_p;
	init_board_architecture(board_architecture);

	dbg_init(); // REMOVE IN FINAL RELEASE
}