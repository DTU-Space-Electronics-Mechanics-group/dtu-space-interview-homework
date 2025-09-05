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

#ifndef DBG_TESTS_H
#define DBG_TESTS_H

extern void dbg_test(void);
extern void dbg_dump_history(void);

extern void dbg_mem_readb(void);
extern void dbg_mem_readh(void);
extern void dbg_mem_readw(void);
extern void dbg_mem_readd(void);
extern void dbg_mem_writeb(void);
extern void dbg_mem_writeh(void);
extern void dbg_mem_writew(void);
extern void dbg_mem_writed(void);

#endif /* DBG_TESTS_H */
