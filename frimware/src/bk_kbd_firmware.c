#include "bk_matrix.pio.h"

void bk_emulation_init(PIO pio, uint sm, uint offset, uint y_base, uint x_base) {
    pio_sm_config c = bk_matrix_program_get_default_config(offset);

    // 1. Setup Y-lines as Inputs
    sm_config_set_in_pins(&c, y_base); 
    for(int i=0; i<10; i++) pio_gpio_init(pio, y_base + i);

    // 2. Setup X-lines as "Direction Controlled" Outputs
    // We keep the GPIO levels at 0, and let PIO toggle Direction
    sm_config_set_out_pins(&c, x_base, 8);
    for(int i=0; i<8; i++) {
        pio_gpio_init(pio, x_base + i);
        gpio_set_dir(x_base + i, GPIO_IN); // Start as Input (High-Z)
        gpio_put(x_base + i, 0);           // When it becomes Output, it's Low
    }

    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);
}