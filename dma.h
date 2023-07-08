#ifndef DMA_H
#define DMA_H

#include "hardware/dma.h"
#include "hardware/irq.h"

dma_channel_config c;
uint dma_channel;
uint dma_mask;

void dma_handler() {
    if (dma_hw->ints0 & dma_mask)
        dma_hw->ints0 = dma_mask;
}



void config_dma_for_pio(PIO pio, uint sm) {
    // claim dma channel
    dma_channel = dma_claim_unused_channel(true);
    dma_mask = 1 << dma_channel;

    // configure dma channel
    c = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_16);

    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, false);

    channel_config_set_dreq(&c, pio_get_dreq(pio, sm, true));

    // enable irq0
    dma_channel_set_irq0_enabled(dma_channel, true);

    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);
}



void send_to_data_pins(PIO pio, uint sm, uint16_t* data, uint n) {
    dma_channel_configure(
        dma_channel,
        &c,
        &pio->txf[sm],
        data,
        n,
        true
    );
}


void send_to_data_pins_blocking(PIO pio, uint sm, uint16_t* data, uint n) {
    send_to_data_pins(pio, sm, data, n);

    do
        asm("NOP");
    while(!pio_sm_is_tx_fifo_empty(pio, sm));
}

#endif