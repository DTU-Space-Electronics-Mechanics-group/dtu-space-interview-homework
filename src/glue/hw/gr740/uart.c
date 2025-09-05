#include "uart.h"

uint32_t init_apbuart(struct apbuart_priv ** apbuart_dev_p)
{
    uint32_t ret;
    uint8_t txfifobuf[32];
    uint8_t rxfifobuf[32];

    struct apbuart_config cfg;

    cfg.baud = 115200;
    cfg.parity = APBUART_PAR_NONE;
    cfg.flow = 0;
    cfg.mode = APBUART_MODE_NONINT;
    cfg.txfifobuflen = 32;
    cfg.txfifobuf = txfifobuf;
    cfg.rxfifobuflen = 32;
    cfg.rxfifobuf = rxfifobuf;

    apbuart_init(GR740_APBUART_DRV_ALL);
    *apbuart_dev_p = apbuart_open(0);

    ret = apbuart_config(*apbuart_dev_p, &cfg);
    return ret;
}