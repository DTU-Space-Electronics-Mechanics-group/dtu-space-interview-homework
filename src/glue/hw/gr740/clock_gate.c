#include "clock_gate.h"

#include <drv/regs/clkgate_bits.h>

// List of the peripherals which will have their clocks enabled.
uint32_t clkgate0_enable_table[] = 
{
	CLKGATE_GR740_MCTRL,
	CLKGATE_GR740_UART0
};

inline uint32_t get_size_of_clkgate0_enable_table(void)
{
	return sizeof(clkgate0_enable_table);
}

void init_clockgate(struct clkgate_priv ** clkgate_dev_p, uint32_t * table, uint32_t len, uint8_t dev_number)
{
	uint32_t mask = 0;
	//Configure the clock gate
	clkgate_init(GR740_CLKGATE_DRV_ALL);
	clkgate_dev_p[dev_number] = clkgate_open(dev_number);

	//Create mask for enabled divices
	for(uint32_t i = 0; i < len / sizeof(table[0]); i++)
	{
		mask |= table[i];
	}

	/* Enable the clock*/
	clkgate_enable(clkgate_dev_p[dev_number], mask);
}
