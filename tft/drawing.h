#ifndef DRAWING_H
#define DRAWING_H

#include "tft.h"

void set_addr_window(PIO pio, uint sm, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    send_command_blocking(
        pio, sm,
        0x2A, // PASET
        (uint16_t[]){
            x0 >> 8,
            x0 & 0xFF,
            x1 >> 8,
            x1 & 0xFF,
        },
        4
    );

    send_command_blocking(
        pio, sm,
        0x2B, // CASET
        (uint16_t[]){
            y0 >> 8,
            y0 & 0xFF,
            y1 >> 8,
            y1 & 0xFF,
        },
        4
    );
}



void draw_frame_buffer(PIO pio, uint sm, uint16_t* frame_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    set_addr_window(pio, sm, x0, y0, x1, y1);

    send_command_blocking(
        pio, sm,
        0x2C, // RAMWR
        frame_buffer,
        (x1 - x0) * (y1 - y0)
    );
}


void draw_full_screen(PIO pio, uint sm, uint16_t* frame_buffer) {
    draw_frame_buffer(pio, sm, frame_buffer, 0, 0, 320, 120);
    draw_frame_buffer(pio, sm, &frame_buffer[320 * 120], 0, 120, 320, 240);
}

#endif