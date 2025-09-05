#ifndef CLOCK_GATE_H
#define CLOCK_GATE_H

#include <stdio.h>
#include <stdlib.h>

#include <drv/clkgate.h>
#include "clock_gate_driver.h"

extern uint32_t clkgate0_enable_table[];


uint32_t get_size_of_clkgate0_enable_table(void);

void init_clockgate(struct clkgate_priv ** clkgate_dev_p, uint32_t * table, uint32_t len, uint8_t dev_number);

#endif // CLOCK_GATE_H
