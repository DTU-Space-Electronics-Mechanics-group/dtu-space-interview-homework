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

#ifndef DBG_CFG_H
#define DBG_CFG_H

#define DEBUG_ENABLE
#ifdef DEBUG_ENABLE

#include "dbg_types.h"

#define DBG_CFG_FULL         (1)   /**< Set to non zero for full user interface functionality */
#define DBG_CFG_TEST_LEVEL   (5)   /**< Maximum number of levels in debugging command hierarchy. */
#define DBG_CFG_HIST_SIZE    (5)   /**< History depth of previous commands issued from the console. */
#define DBG_CFG_LINE_LENGTH  (30)  /**< Maximum length of an input line from the debug console. */

extern char const header0[];
extern char const header1[];

extern dbg_table_t const dbg_root[];

#endif /* DEBUG_ENABLE */

#endif /* DBG_CFG_H */
