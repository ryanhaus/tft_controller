#ifndef TFT_H
#define TFT_H

#include "../pio.h"
#include "../dma.h"
#include "tft_constants.h"



void send_command_blocking(PIO pio, uint sm, uint16_t command, uint16_t* data, uint16_t data_n) {
    tft_data_transfer_busy = true;
    gpio_put(25, 1);

    // first packet is whether or not there are arguments (1 = yes, 0 = no)
    send_to_data_pins_blocking(pio, sm, &data_n, 1);

    // second packet is the command
    send_to_data_pins_blocking(pio, sm, &command, 1);

    // (optional) third packet is the arguments, must be sent if the first packet is 1 and must not be sent if it was 0
    if (data_n > 0)
        send_to_data_pins_blocking(pio, sm, data, data_n);
    
    do
        asm("NOP");
    while(tft_data_transfer_busy);
}



void tft_startup_sequence(PIO pio, uint sm) {
    uint i = 0;

    while (i < sizeof(STARTUP_SEQUENCE) / sizeof(uint16_t)) {
        bool add_delay      =  STARTUP_SEQUENCE[i]   & 0x100;
        uint16_t arg_count  =  STARTUP_SEQUENCE[i++] & 0xFF;
        uint16_t command    =  STARTUP_SEQUENCE[i++];

        send_command_blocking(
            pio, sm,
            command,
            (uint16_t*)&STARTUP_SEQUENCE[i],
            arg_count
        );

        i += arg_count;

        if (add_delay)
            sleep_ms(100);
    }
}



void tft_setup() {
    // setup GPIO pins, exclude WR b/c that gets set up w/ PIO
    gpio_init(TFT_RST);

    // set pin directions
    gpio_set_dir(TFT_RST, GPIO_OUT);

    // set all high
    gpio_put(TFT_RST, 1);
}

#endif