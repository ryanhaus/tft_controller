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

    while (true) {
        for (int i = 0; i < 240; i++) {
            uint32_t extra_noise = rand();

            for (int j = 0; j < 10; j++) {
                uint32_t noise = rand();

                for (int k = 0; k < 31; k++)
                    screen_data[i][32 * j + k] = noise & (1 << k) ? 0xFFFF : 0x0000;

                screen_data[i][32 * j + 31] = extra_noise & (1 << j) ? 0xFFFF : 0x0000;
            }
        }

        draw_full_screen(pio, sm, &screen_data[0][0]);

        sleep_ms(15);
    }
}