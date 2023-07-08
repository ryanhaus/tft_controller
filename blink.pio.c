#include "blink.pio.h"

void pio_test_init(PIO pio, uint sm, uint offset, uint pin0, uint pin_count, uint bit_count, uint sideset, float div) {
    pio_sm_config c = blink_program_get_default_config(offset);

    for (uint i = 0; i < pin_count; i++)
        pio_gpio_init(pio, pin0 + i);

    pio_sm_set_consecutive_pindirs(pio, sm, pin0, pin_count, true);
    
    sm_config_set_out_shift(&c, false, true, 32);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    sm_config_set_out_pins(&c, pin0, bit_count);
    sm_config_set_sideset_pins(&c, sideset);

    sm_config_set_clkdiv(&c, div);

    pio_sm_init(pio, sm, offset, &c);
}

void pio_test_putc_blocking(PIO pio, uint sm, uint8_t byte) {
    pio_sm_put_blocking(pio, sm, byte);
}

void pio_test_puts_blocking(PIO pio, uint sm, uint8_t* first_byte, size_t n) {
    for (size_t i = 0; i < n; i++) 
        pio_test_putc_blocking(pio, sm, first_byte[i]);
}