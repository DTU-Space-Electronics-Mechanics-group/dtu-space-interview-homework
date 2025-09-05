/*******************************************************************************
*                  COPYRIGHT (C) 2016  -  All Rights Reserved
*                        Powersense A/S
********************************************************************************
*
* Original author: Karsten Sjørslev
* 
* Modifications Copyright (C) 2025 Technical University of Denmark
* Author: Denis Tcherniak
* Author: Luca Victoria Bune Jensen
* 
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include "dbg_cfg.h"

// Test function
void dbg_test(void)
{
	int i = dbg_parm_get_int(1,0);
	dbg_print("Hello world %d!\n", i);
}

void dbg_dump_history(void)
{
	char data[DBG_CFG_LINE_LENGTH+1];

	uint8_t num = circ_hist_length(dbg_cmd_hist);
	for (uint8_t line = 0; line < num; line++)
	{
		memset(data, 0, DBG_CFG_LINE_LENGTH+1);
		/*int8_t res =*/ circ_hist_read(dbg_cmd_hist, data, line);

		for (uint8_t cha = 0; cha < DBG_CFG_LINE_LENGTH; cha++)
		{
			if(data[cha]==0)
			{
				data[cha] = '_';
				continue;
			}
			else if(strchr( validChars, data[cha] ))
			{
				continue;
			}
			else
			{
				data[cha] = '*';
			}
		}
		
		//dbg_print("%d res: %d\n", line, res);
		//if(res != -1)
		{
			dbg_print("%s\n", data);
		}
	}
}