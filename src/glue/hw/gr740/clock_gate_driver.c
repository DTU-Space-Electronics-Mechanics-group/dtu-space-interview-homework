#include <stddef.h>
#include "clock_gate_driver.h"
#include "gr740_pnp.h"
#include <drv/ambapp_ids.h>

struct clkgate_devcfg *GR740_CLKGATE_DRV_ALL[] = {
        & (struct clkgate_devcfg) {
                .regs = {
                        .addr       = GAISLER_CLKGATE_PNP_APB,
                        .device_id  = GAISLER_CLKGATE,
                        .version    = GAISLER_CLKGATE_PNP_VERSION,
                },
        },
        NULL
};