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
* @brief   This is the configuration file for the debug interface
*
********************************************************************************/

#include "dbg_types.h"
#include "dbg_tests.h"

char const header0[]  = "\n\nDTU Space - AIB EGSE custom simulator\n";
char const header1[]  = "Debug interface - Copyright(c) DTU Space 2020\n";

/********************** Main test table construction ***************************
 * In this section the folder structure of the debug command terminal is defined.
 * It needs to be changed on a project to project basis.
 *******************************************************************************
 * A folder is represented as a debug-table array.
 * The each table in the array is either a subfolder or a command/test function.
 * The last table in the array must contain NULL values.
 *******************************************************************************
 * The first element of a table is the name of the item.
 * The second element is the description of the item.
 * The third element is a pointer to the subfolder or NULL if it is a test.
 * The fourth element is a pointer to the test function or NULL if it is a folder.
 *******************************************************************************
 * OBS! Remember to declare the arrays and external functions before using them.
 *******************************************************************************/


// Root
dbg_table_t const dbg_app[]; // If you define your test tree from top to bottom
dbg_table_t const dbg_root[] = { // using them to define the current folder
	{ "app", "Application layer tests", dbg_app, 0 },
	{ 0, 0, 0, 0 },
};

// Root -> Application Layer
dbg_table_t const dbg_app[] = {
	{"hello_world", "Prints Hello World", 0, dbg_test},
	{"hist_dump", "Prints the contents of the terminal history", 0, dbg_dump_history},
	{0, 0, 0, 0}
};
