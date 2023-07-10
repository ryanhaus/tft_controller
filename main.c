#include "pico/stdlib.h"
#include "hardware/clocks.h"

#include "pio.h"
#include "dma.h"
#include "tft/tft.h"
#include "tft/drawing.h"

uint16_t screen_data[240][320] = { 0 };

int main() {
    PIO pio = pio0;
    uint sm = pio_claim_unused_sm(pio, true);
    uint offset = pio_add_program(pio, &blink_program);

    pio_test_init(pio, sm, offset, TFT_D_LSB, TFT_RD);
    pio_sm_set_enabled(pio, sm, true);

    config_dma_for_pio(pio, sm);

    tft_setup();

    sleep_ms(100);
    gpio_put(TFT_RST, 0);

    sleep_ms(100);
    gpio_put(TFT_RST, 1);

    sleep_ms(100);

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    tft_startup_sequence(pio, sm);

    int sq_x = 0, sq_y = 0;
    int t = 0;

    gpio_init(TFT_TE);
    gpio_set_dir(TFT_TE, GPIO_IN);

    while (true) {
        sq_x = (int)(sin(t / 20.0) * 50);
        sq_y = (int)(cos(t / 20.0) * 50);
        t++;

        for (int y = 0; y < 240; y++)
            for (int x = 0; x < 320; x++) {
                screen_data[y][x] = 
                    (   y >= 100 + sq_y
                    &&  y <= 140 + sq_y
                    &&  x >= 140 + sq_x
                    &&  x <= 180 + sq_x)
                        ? 0b1111100000000000
                        : 0xFFFF;
            }

        while (gpio_get(TFT_TE))
            asm("NOP");

        while(!gpio_get(TFT_TE))
            asm("NOP");

        draw_full_screen(pio, sm, &screen_data[0][0]);
    }
}