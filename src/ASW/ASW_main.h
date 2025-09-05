/* Make sure to include this header file only once */
#ifndef ASW_MAIN_H_
#define ASW_MAIN_H_

#include <stdio.h>
#include <stdlib.h>

#include "operational_sm.h"

/**
 * Structure holding all system modules.
 * 
 * This structure is the parent of all system modules. Each member of this structure is a pointer to a module object.
 * 
 * The purpose of this structure is to provide a fully controlled flow of data between modules.
 * 
 * This structure and all its members are statically defined in their respective source files. The values of the pointers used to link to the statically defined structures in an object oriented fashion are then set by the init_sys_desc() function, which calls the initialization functions of all child modules recursively.
*/
typedef struct SYS_DESC_t 
{   
    __uint32_t sys_1ms_tick;    /*!< System 1ms tick counter*/
    FwSmDesc_t operational_sm;  /*!< Pointer to operational state machine object*/
    int err_operational_sm;     /*!< Status of the module for error reporting*/

}SYS_DESC_t;

#endif /* ASW_MAIN_H_ */