#ifndef PIO_H
#define PIO_H

#include "hardware/pio.h"
#include "blink.pio.h"

// flag for whether or not there is an active data transfer to the TFT 
bool tft_data_transfer_busy = false;

void pioIRQ() {
    if (pio_interrupt_get(pio0, 0)) {
        pio_interrupt_clear(pio0, 0);
        tft_data_transfer_busy = false;
        gpio_put(25, 0);
    }
}

void pio_test_init(PIO pio, uint sm, uint offset, uint pin_d0, uint rd_pin) {
    // default config
    pio_sm_config c = blink_program_get_default_config(offset);

    // initialize pins
    for (uint i = 0; i < 4; i++)
        pio_gpio_init(pio, rd_pin + i);
        
    for (uint i = 0; i < 16; i++)
        pio_gpio_init(pio, pin_d0 + i);

    // set pin directions
    pio_sm_set_consecutive_pindirs(pio, sm, pin_d0, 16, true);
    pio_sm_set_consecutive_pindirs(pio, sm, rd_pin, 4, true);

    // set pin pio roles
    sm_config_set_out_pins(&c, pin_d0, 16);
    sm_config_set_sideset_pins(&c, rd_pin);

    // setup output shift register    
    sm_config_set_out_shift(&c, false, false, 16);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    // clock div, 66ns required per write cycle
    sm_config_set_clkdiv(&c, 1.5f);

    // enable IRQ0
    pio_set_irq0_source_enabled(pio, pis_interrupt0, true);
    irq_set_exclusive_handler(PIO0_IRQ_0, pioIRQ);
    irq_set_enabled(PIO0_IRQ_0, true);

    // initialize state machine
    pio_sm_init(pio, sm, offset, &c);
}



void pio_test_putc_blocking(PIO pio, uint sm, uint16_t byte) {
    pio_sm_put_blocking(pio, sm, (uint32_t)byte);
}

#endif