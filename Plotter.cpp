#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/dma.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

#include "disp.h"

int main()
{
    stdio_init_all();

    gpio_init(8);
    gpio_set_dir(8, true);
    gpio_put(8, true);
    gpio_init(9);
    gpio_set_dir(9, true);
    gpio_put(9, true);
    gpio_init(14);
    gpio_set_dir(14, true);
    gpio_put(14, true);
    lcd_init(26, 27);
    while (1) {
        lcd_print("Hai");
        sleep_ms(300);
    }

    return 0;
}
