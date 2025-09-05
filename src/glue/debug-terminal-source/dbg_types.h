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

#ifndef DBG_TYPES_H
#define DBG_TYPES_H

#include <stdint.h>

/*******************************************************************************
 *    Type defintions
 ******************************************************************************/
//TODO: Fix these
typedef char char_t;
typedef float float32_t;   			 /**< 32-bit signed real number */
typedef signed int      int_t;       /**< 16/24/32-bit signed integer. */
typedef unsigned int    uint_t;      /**< 16/24/32-bit unsigned integer. */

typedef void (*dbg_func_t)(void);  	 /**< Function pointer for general debug command handler. */

typedef struct dbg_table_tag {
	char_t const * const x_name;
	char_t const * const xhelp;
	struct dbg_table_tag const * const table;
	dbg_func_t const func;
} const  dbg_table_t;

typedef  void (* dbg_putchar_t)(uint8_t const ch);

#endif /* DBG_TYPES_H */
