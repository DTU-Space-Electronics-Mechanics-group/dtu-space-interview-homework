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
********************************************************************************
*
* @brief   This module is used for debug and test.
*
***********************************************************************************/

/********************************* INCLUDE FILES **********************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "dbg.h"
#include "dbg_cfg.h"
#include "circular_hist_buffer.h"

/***********************************************************************************
*    Defines
***********************************************************************************/

#define CHAR_TAB		'\t'
#define CHAR_BACKSP		'\b'
#define CHAR_BS			0x7F
#define CHAR_CTRLC		'\003'
#define CHAR_CR			'\r'
#define CHAR_LF			'\n'
#define CHAR_BELL		'\007'
#define CHAR_CTRLR		'\022'

#define CHAR_ESC		0x1B
#define CHAR_LSQB		0x5B
#define CHAR_UP			0x41
#define CHAR_DOWN		0x42
#define CHAR_RIGHT		0x43
#define CHAR_LEFT		0x44

#define MAX_TOKEN      (5)

/***********************************************************************************
*    Local variables
***********************************************************************************/

static char_t * token[MAX_TOKEN];
static dbg_table_t *  dbg_stack[DBG_CFG_TEST_LEVEL];
static char_t dbg_cmd_line[DBG_CFG_LINE_LENGTH];
static uint8_t chIdx, noToken;
static int8_t dbg_stack_ptr;

static char_t data00[DBG_CFG_LINE_LENGTH];
static char_t data01[DBG_CFG_LINE_LENGTH];
static char_t data02[DBG_CFG_LINE_LENGTH];
static char_t data03[DBG_CFG_LINE_LENGTH];
static char_t data04[DBG_CFG_LINE_LENGTH];
static char_t data05[DBG_CFG_LINE_LENGTH];
static char_t data06[DBG_CFG_LINE_LENGTH];
static char_t data07[DBG_CFG_LINE_LENGTH];
static char_t data08[DBG_CFG_LINE_LENGTH];
static char_t data09[DBG_CFG_LINE_LENGTH];
static char_t data10[DBG_CFG_LINE_LENGTH];
static line_t lines[11] = {	{.data = data00, .length = 0},
							{.data = data01, .length = 0},
							{.data = data02, .length = 0},
							{.data = data03, .length = 0},
							{.data = data04, .length = 0},
							{.data = data05, .length = 0},
							{.data = data06, .length = 0},
							{.data = data07, .length = 0},
							{.data = data08, .length = 0},
							{.data = data09, .length = 0},
							{.data = data10, .length = 0} };
/*static*/ int8_t histIdx;

/***********************************************************************************
*    Global variables
***********************************************************************************/

char_t const validChars[] =
	"1234567890"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"-+./?_ ";

circ_hist_t dbg_cmd_hist[] = {{.buffer = lines, .head = 0, .tail = 0, .maxlen = 11}};

/***********************************************************************************
*    System "interrupts" & commands
***********************************************************************************/

static void dbg_sys_cmd_ls(void);
static void dbg_sys_cmd_la(void);
static void dbg_sys_cmd_help(void);
static void dbg_syscmd_to_root(void);
static void dbg_syscmd_to_parent(void);

static dbg_table_t const sys_int[] = {
	{ "Ctrl-r", "Refresh console", 0, 0 },
	{ "Ctrl-c", "Clear current command", 0, 0 },
	{ 0, 0, 0, 0 }
};

static dbg_table_t const sys_cmd[] = {
	{ "help", "List system commands", 0, dbg_sys_cmd_help },
	{ "ls", "List content of current directory", 0, dbg_sys_cmd_ls },
	{ "la", "List content of all directories", 0, dbg_sys_cmd_la },
	{ "/",  "Change to root directory", 0, dbg_syscmd_to_root },
	{ "..", "Change to parent directory", 0, dbg_syscmd_to_parent },
	{ 0, 0, 0, 0 }
};

static dbg_table_t const root[] = {
	{ "","", dbg_root, 0 },
	{ "","", sys_cmd,   0 },
};

/***************************************************************************
	Function Prototypes
****************************************************************************/

static void dbg_putchar( uint8_t ch );

static void dbg_push_stack(dbg_table_t const *const p)
{
	if ( dbg_stack_ptr < DBG_CFG_TEST_LEVEL - 1 ) {
		dbg_stack[++dbg_stack_ptr] = p;
	} else {
		dbg_write("Stack overflow\n");
	}
}

static void dbg_pop_stack(void)
{
	if ( dbg_stack_ptr > 0 ) {
		dbg_stack_ptr--;
	} else {
		dbg_write("Stack underflow\n");
	}
}

static dbg_table_t * top_stack(void)
{
	return dbg_stack[dbg_stack_ptr];
}

static void dbg_print_header(void)
{
	dbg_write(header0);
	dbg_write(header1);
}

static dbg_table_t * dbg_lookup(dbg_table_t const *const q, char_t *const p_name)
{
	dbg_table_t * p = q;
	int32_t not_found = 1;
	while ( p->x_name && not_found ) {
		not_found = strcmp( p_name, p->x_name );
		if ( not_found ) {
			p++;
		}
	}
	return not_found ? 0 : p;
}

static dbg_table_t * dbg_lookup_cmd(char_t *const pCmd)
{
	dbg_table_t * p = dbg_lookup(sys_cmd, pCmd);
	if ( !p ) {
		p = dbg_lookup(top_stack()->table, pCmd);
	}

	return p;
}

static void dbg_cmd_line_save()
{
	if(strcmp(dbg_cmd_line, circ_hist_access(dbg_cmd_hist, 0)->data)==0)
		return;

	if(circ_hist_is_full(dbg_cmd_hist))
		circ_hist_squash(dbg_cmd_hist);
	
	circ_hist_push(dbg_cmd_hist, dbg_cmd_line, chIdx);
}

static void dbg_cmd_line_reset(void)
{
	chIdx = 0;
	histIdx = -1;
	memset( dbg_cmd_line, 0, DBG_CFG_LINE_LENGTH );
}

static void dbg_output_prompt(void)
{
	dbg_table_t const * p = root;
	dbg_cmd_line_reset();
	int32_t i;
	for ( i = 0; i <= dbg_stack_ptr; i++ ) {
		if(i!=1)
			dbg_putchar( '/' );
		p = dbg_stack[i];
		dbg_write(p->x_name);
	}
	dbg_write(">");
}

static uint8_t dbg_tokennize(void)
{ 
	char_t * tk;
	int32_t i = 0;
	tk = strtok( dbg_cmd_line, " \r\n" );
	while( tk ) {
		if ( i < MAX_TOKEN ) {
			token[i++] = tk; 
			tk = strtok( 0, " \r\n" );
		} else {
			tk = 0;
		}
	}

	return (uint8_t)i;
}

static void dbg_execute_command(void)
{
	dbg_write("\n");
	noToken = dbg_tokennize();

	if ( noToken ) {
		dbg_table_t * cmd = dbg_lookup_cmd(token[0]);
		if ( cmd ) {
			if ( cmd->func ) {
				cmd->func();
			} else if ( cmd->table ) {
				dbg_push_stack(cmd);
			}
		} else {
			dbg_write("\tUnknown command, try help or ls\n");
		}
	}
}

static void dbg_line_erase()
{
	for ( uint8_t i = 0; i < chIdx; i++ ) {
		dbg_write("\b \b");
	}
}

static void dbg_backspace()
{
	/* back space - erase one char*/
	if ( chIdx ) {
		dbg_cmd_line[--chIdx] = 0;
		dbg_write("\b \b");
	}
}

static void dbg_line_populate(){
	

	for(uint8_t i = 0; i<chIdx; i++){
		dbg_putchar( dbg_cmd_line[i] );
	}
}

static void dbg_history_next()
{
	if(histIdx == -1){
		dbg_putchar( CHAR_BELL );
		return;
	}

	int8_t next = histIdx-1;

	if(next == -1){
		while(chIdx)
			dbg_backspace();
		histIdx = next;
	}
	else {
		int result = circ_hist_read(dbg_cmd_hist, dbg_cmd_line, next);
		if (result >= 0){
			dbg_line_erase();
			histIdx = next;
			chIdx = result;
			dbg_line_populate();
	}
	}
}

static void dbg_history_prev()
{
	uint8_t next = histIdx+1;
	if(next == dbg_cmd_hist->maxlen){
		dbg_putchar( CHAR_BELL );
		return;
	}

	int result = circ_hist_read(dbg_cmd_hist, dbg_cmd_line, next);
	if (result >= 0){
		dbg_line_erase();
		histIdx = next;
		chIdx = result;
		dbg_line_populate();
	}
}

static void dbg_move_cursor_right(){}
static void dbg_move_cursor_left(){}

static void dbg_execute_input(uint8_t const ch)
{
	switch (ch)
	{
	case CHAR_CTRLC:
		/* Skip input and output new prompt */
		dbg_write("^C\n");
		dbg_output_prompt();
		break;
	
	case CHAR_BACKSP:
	case CHAR_BS:
		dbg_backspace();
		break;
	
	case CHAR_CTRLR:
		dbg_write("^R\n");
		dbg_print_header();
		dbg_output_prompt();
		break;
	
	case CHAR_CR:
		dbg_cmd_line_save();
		dbg_execute_command();
		dbg_output_prompt();
		break;
	
	default:
		if ( strchr( validChars, ch ) && chIdx < DBG_CFG_LINE_LENGTH ){
			dbg_cmd_line[chIdx++] = ch;
			dbg_putchar( ch );
		}
		else
			dbg_putchar( CHAR_BELL );
		break;
	}
}

static bool dbg_intercept_escape_code(uint8_t ch)
{
	static uint8_t state = 0;

	// Implemented escape codes
	//	ESC - LSQB - A		[ Arrow up ]
	//	ESC - LSQB - B		[ Arrow down ]

	switch (state)
	{
	case 2:
		switch (ch)
		{
		case CHAR_UP:
			dbg_history_prev();
			break;
		
		case CHAR_DOWN:
			dbg_history_next();
			break;
		
		case CHAR_RIGHT:
			dbg_move_cursor_right();
			break;
		
		case CHAR_LEFT:
			dbg_move_cursor_left();
			break;
		
		default:
			dbg_putchar( CHAR_BELL );
			break;
		}
		state = 0;
		return true;
	
	case 1:
		if(ch == CHAR_LSQB)
			state = 2;
		else{
			dbg_putchar( CHAR_BELL );
			state = 0;
		}
		return true;
	
	default:
		if(ch == CHAR_ESC)
		{
			state = 1;
			return true;
		}
		else
			return false;
	}
}

static void dbg_syscmd_to_root(void)
{
	if ( dbg_stack_ptr > 0 ) {
		dbg_stack_ptr = 0;
	}
}

static void dbg_syscmd_to_parent(void)
{
	if ( dbg_stack_ptr > 0 ) {
		dbg_pop_stack();
	}
}

static void dbg_list_dir(dbg_table_t const *const q, uint32_t level)
{
	dbg_table_t * p = q;
	while ( p->x_name ) {
		uint32_t i;
		for ( i = 0; i < level; i ++ ) {
			dbg_putchar( '\t' );
		}
		dbg_print("%s\t\t%s\n", p->x_name, p->xhelp);
		if ( p->table ) {
			dbg_list_dir(p->table, level + 1);
		} 
		p++;
	}
}

static void dbg_sys_cmd_la(void)
{
	dbg_list_dir(top_stack()->table, 1);
}

static void dbg_sys_cmd_help(void)
{
	dbg_list_dir(sys_int, 1);
	dbg_list_dir(sys_cmd, 1);
}

static void dbg_sys_cmd_ls(void)
{
	dbg_table_t * p = top_stack()->table;
	if ( dbg_stack_ptr > 0 ) {
		dbg_print("\t/\t\tRoot directory\n");
		dbg_print("\t..\t\tParent directory\n");
	}
	while ( p->x_name ) {
		dbg_print("\t%s\t\t%s\n", p->x_name, p->xhelp);
		p++;
	}
}

/***************************************************************************
	Interface functions
****************************************************************************/
void dbg_init(void)
{
	setbuf(stdout, NULL);

	dbg_stack_ptr = -1;
	dbg_push_stack(root);
	dbg_print_header();
	dbg_output_prompt();
}

void dbg_handle_input(uint8_t ch)
{
	if(!dbg_intercept_escape_code(ch))
		dbg_execute_input(ch);
}

uint32_t dbg_parm_length(void)
{
	return noToken;
}

int32_t dbg_parm_get_hex(uint32_t parmno, int32_t default_val)
{
	uint32_t token_i = parmno;
	int32_t res = default_val;
	if ( token_i < noToken ) {
		res = strtoul( token[token_i], 0, 16 );
	} else {
		dbg_print("Parameter #%d (hexadecimal integer) missing - value %d used\n", token_i, default_val);
	}
	return res;
}

int32_t dbg_parm_get_int(uint32_t parmno, int32_t default_val)
{
	uint32_t token_i = parmno;
	int32_t res = default_val;
	if ( token_i < noToken ) {
		res = strtol( token[token_i], 0, 10 );
	} else {
		dbg_print("Parameter #%d (decimal integer) missing - value %d used\n", token_i, default_val);
	}
	return res;
}

int32_t dbg_parm_get_int_silent(uint32_t parmno, int32_t default_val)
{
	uint32_t token_i = parmno;
	int32_t res = default_val;
	if ( token_i < noToken ) {
		res = strtol( token[token_i], 0, 10 );
	}
	return res;
}

char_t * dbg_parm_get_str(uint32_t parmno, char_t * default_val)
{
	uint32_t token_i = parmno;
	char_t * res = default_val;
	if ( token_i < noToken ) {
		res = token[token_i];
	} else {
		dbg_print("Parameter #%d (string) missing - value \"%s\" used\n", token_i, default_val);
	}
	return res;
}

float32_t dbg_parm_get_flt(uint32_t parmno, float32_t default_val)
{
	uint32_t token_i = parmno;
	float32_t res = default_val;
	if ( token_i < noToken ) {
		res = strtof( token[token_i], 0);
	} else {
		dbg_print("Parameter #%d (float) missing - value %f used\n", token_i, default_val);
	}
	return res;
}

int32_t dbg_parm_get_int32_silent(uint32_t parmno, int32_t default_val)
{
	uint32_t token_i = parmno;
	int32_t res = default_val;
	if ( token_i < noToken ) {
		res = strtol( token[token_i], 0, 10 );
	} // TODO: make it handle both dec and hex values
	return res;
}

void dbg_write(const char_t *text)
{
	 while ( *text ) {
		dbg_putchar( *text );
		text ++;
	}
}

int_t dbg_print(const char_t *format, ...)
{
	va_list ap;
	int_t nr_of_chars;

	va_start(ap, format);
	nr_of_chars =  vprintf( (char *)format, ap );
	va_end(ap);

	return nr_of_chars;        /* According to ANSI */
}

static void dbg_putchar( uint8_t ch )
{
	if ( ch == '\n' ) {
		putchar( '\r' );
	}
	putchar( ch );
}
