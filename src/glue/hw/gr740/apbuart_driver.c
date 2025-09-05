#include <stddef.h>
#include "apbuart_driver.h"
#include "gr740_pnp.h"

static struct apbuart_devcfg GR740_DEV_CFG_0 = {
  .regs = {
    .addr   = GAISLER_APBUART_0_PNP_APB,
    .interrupt  = GAISLER_APBUART_0_PNP_APB_IRQ
  },
};

static struct apbuart_devcfg GR740_DEV_CFG_1 = {
  .regs = {
    .addr   = GAISLER_APBUART_1_PNP_APB,
    .interrupt  = GAISLER_APBUART_1_PNP_APB_IRQ
  },
};

struct apbuart_devcfg *GR740_APBUART_DRV_ALL[] = {
    &GR740_DEV_CFG_0,
    &GR740_DEV_CFG_1,
    NULL
};