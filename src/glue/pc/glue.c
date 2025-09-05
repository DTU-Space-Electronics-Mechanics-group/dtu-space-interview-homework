#include <stddef.h>

#include "glue.h"

#include "dbg.h" // REMOVE IN FINAL RELEASE
#include "dbg_glue.h" // REMOVE IN FINAL RELEASE


void glue_main_init(uint32_t * sys_1ms_tick_p)
{
	dbg_init(); // REMOVE IN FINAL RELEASE
	dbg_glue_init(); // REMOVE IN FINAL RELEASE
}