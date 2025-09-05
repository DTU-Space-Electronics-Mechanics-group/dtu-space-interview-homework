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
* @brief   This is the header file for the debug interface
*
*******************************************************************************/

#ifndef DBG_H
#define DBG_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

#include "dbg_types.h"
#include "circular_hist_buffer.h"

/*******************************************************************************
 *    Function prototypes
 ******************************************************************************/
uint32_t  dbg_parm_length(void);
int32_t   dbg_parm_get_hex(uint32_t paramno, int32_t default_val);
int32_t   dbg_parm_get_int(uint32_t parmno, int32_t default_val);
int32_t   dbg_parm_get_int_silent(uint32_t parmno, int32_t default_val);
float32_t dbg_parm_get_flt(uint32_t parmno, float32_t default_val);
char_t *  dbg_parm_get_str(uint32_t parmno, char_t * default_val);

/**
 * Specify the debug output handler. This sets a function which is called every
 * time a line of text is to be printed to the debug output. This function must
 * accept a string pointer and send it to the relevant output medium.
 * @param new_output Pointer to output handling function.
 * @returns Pointer to previous debug output handler. This could be used to chain
 * different handlers, sending the output to several destinations.
 */
dbg_putchar_t dbg_output_define(dbg_putchar_t new_output);

/**
 * Write a text string to the debug output.
 * @param text Pointer to 0-terminated string.
 */
void dbg_write(const char_t *text);

/**
 * Write a formatted string to the debug output.
 * @param format The formatting string in usual printf format.
 * @returns The number of characters in the formatted output.
 */
int_t dbg_print(const char_t *format, ...);

/**
 * Input handler for debug console input.
 * This function must be called from the relevant debug input source (e.g. serial
 * interrupt handler) whenever a character is received from the user.
 * @param ch The single character.
 */
void dbg_handle_input(uint8_t ch);

/**
 * Initialise the debugging module.
 * This function must be called before any other DBG macro/function.
 */
void dbg_init(void);

/*******************************************************************************
 *    Global variables
 ******************************************************************************/

extern char_t const validChars[];
extern circ_hist_t dbg_cmd_hist[];

/******************************************************************************/

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* DBG_H */

