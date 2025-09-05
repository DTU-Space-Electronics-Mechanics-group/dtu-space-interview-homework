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
#include <drv/gpio.h>
#include "board.h"
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


// Help information for read functions
static void dbg_mem_read_help(const char *func_name, const char *bit_size)
{
	dbg_print(
		"\t%s <address> [length]\n"
		"\tDo a %s read and print the data\n"
		"\tParameters:\n"
		"\t\taddress: The address to read from\n"
		"\tOptions:\n"
		"\t\tlength: The number of %s values to read\n",
		func_name, bit_size, bit_size
	);
}

// Read functions
void dbg_mem_readb(void)
{
	if(dbg_parm_length()==0){
		dbg_write(
			"\treadb: missing parameter\n"
			"\tTry 'readb help' for more information\n"
		);
		return;
	}
	if(strcmp(dbg_parm_get_str(1,""),"help")){
		dbg_mem_read_help("readb", "8-bit");
		return;
	}	
	unsigned char *addr = (unsigned char *)dbg_parm_get_int(1, 0);
	unsigned int length = dbg_parm_get_int_silent(2, 1);
	for(unsigned int i = 0; i < length; i++){
		dbg_print("Read byte from address %p: %x\n", addr, *addr);
	}
}
void dbg_mem_readh(void){
	if(dbg_parm_length()==0){
		dbg_write(
			"\treadh: missing parameter\n"
			"\tTry 'readh help' for more information\n"
		);
		return;
	}
	if(strcmp(dbg_parm_get_str(1,""),"help")){
		dbg_mem_read_help("readh", "16-bit");
		return;
	}	
	unsigned short *addr = (unsigned short *)dbg_parm_get_int(1, 0);
	unsigned int length = dbg_parm_get_int_silent(2, 1);
	for(unsigned int i = 0; i < length; i++){
		dbg_print("Read halfword from address %p: %x\n", addr, *addr);
	}
}
void dbg_mem_readw(void){
	if(dbg_parm_length()==0){
		dbg_write(
			"\treadw: missing parameter\n"
			"\tTry 'readw help' for more information\n"
		);
		return;
	}
	if(strcmp(dbg_parm_get_str(1,""),"help")){
		dbg_mem_read_help("readw", "32-bit");
		return;
	}	
	unsigned int *addr = (unsigned int *)dbg_parm_get_int(1, 0);
	unsigned int length = dbg_parm_get_int_silent(2, 1);
	for(unsigned int i = 0; i < length; i++){
		dbg_print("Read word from address %p: %x\n", addr, *addr);
	}
}
void dbg_mem_readd(void){
	if(dbg_parm_length()==0){
		dbg_write(
			"\treadd: missing parameter\n"
			"\tTry 'readd help' for more information\n"
		);
		return;
	}
	if(strcmp(dbg_parm_get_str(1,""),"help")){
		dbg_mem_read_help("readd", "64-bit");
		return;
	}	
	unsigned long long *addr = (unsigned long long *)dbg_parm_get_int(1, 0);
	unsigned int length = dbg_parm_get_int_silent(2, 1);
	for(unsigned int i = 0; i < length; i++){
		dbg_print("Read double word from address %p: %x\n", addr, *addr);
	}
}

// Help information for write functions
static void dbg_mem_write_help(const char *func_name, const char *bit_size)
{
	dbg_print(
		"\t%s <address> <value>\n"
		"\tDo a %s write\n"
		"\tParameters:\n"
		"\t\taddress: The address to write to\n"
		"\t\tvalue: The value to write\n",
		func_name, bit_size
	);
}

// Write functions
void dbg_mem_writeb(void){
	if(dbg_parm_length()<2){
		dbg_write(
			"\twriteb: missing parameter\n"
			"\tTry 'writeb help' for more information\n"
		);
		return;
	}
	if(strcmp(dbg_parm_get_str(1,""),"help")){
		dbg_mem_write_help("writeb", "8-bit");
		return;
	}	
	unsigned char *addr = (unsigned char *)dbg_parm_get_int(1, 0);
	unsigned char value = (unsigned char)dbg_parm_get_int(2, 0);
	*addr = value;
	dbg_print("Wrote byte %x to address %p\n", value, addr);
}
void dbg_mem_writeh(void){
	if(dbg_parm_length()<2){
		dbg_write(
			"\twriteh: missing parameter\n"
			"\tTry 'writeh help' for more information\n"
		);
		return;
	}
	if(strcmp(dbg_parm_get_str(1,""),"help")){
		dbg_mem_write_help("writeh", "16-bit");
		return;
	}	
	unsigned short *addr = (unsigned short *)dbg_parm_get_int(1, 0);
	unsigned short value = (unsigned short)dbg_parm_get_int(2, 0);
	*addr = value;
	dbg_print("Wrote halfword %x to address %p\n", value, addr);
}
void dbg_mem_writew(void){
	if(dbg_parm_length()<2){
		dbg_write(
			"\twritew: missing parameter\n"
			"\tTry 'writew help' for more information\n"
		);
		return;
	}
	if(strcmp(dbg_parm_get_str(1,""),"help")){
		dbg_mem_write_help("writew", "32-bit");
		return;
	}	
	unsigned int *addr = (unsigned int *)dbg_parm_get_int(1, 0);
	unsigned int value = (unsigned int)dbg_parm_get_int(2, 0);
	*addr = value;
	dbg_print("Wrote word %x to address %p\n", value, addr);
}
void dbg_mem_writed(void){
	if(dbg_parm_length()<2){
		dbg_write(
			"\twrited: missing parameter\n"
			"\tTry 'writed help' for more information\n"
		);
		return;
	}
	if(strcmp(dbg_parm_get_str(1,""),"help")){
		dbg_mem_write_help("writed", "64-bit");
		return;
	}	
	unsigned long long *addr = (unsigned long long *)dbg_parm_get_int(1, 0);
	unsigned long long value = (unsigned long long)dbg_parm_get_int(2, 0);
	*addr = value;
	dbg_print("Wrote double word %x to address %p\n", value, addr);
}