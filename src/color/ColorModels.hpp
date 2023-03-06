#pragma once

#include <stdint.h>
#include <algorithm>

#include <pico/double.h>

struct rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    rgb(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
        : r(r), g(g), b(b)
    {
    }
};

struct cmyk {
    uint8_t c;
    uint8_t m;
    uint8_t y;
    uint8_t k;

    cmyk(const rgb &val)
    {
        double r_fill, g_fill, b_fill;
        r_fill = (double)val.r / 255.0;
        g_fill = (double)val.g / 255.0;
        b_fill = (double)val.b / 255.0;

        double inverted_black = std::max(r_fill, std::max(g_fill, b_fill));
        double black = 1.0 - inverted_black;
        if (inverted_black == 0.0) {
            c = 0;
            m = 0;
            y = 0;
        }
        else {
            c = std::round(100.0 * (inverted_black - r_fill) / inverted_black);
            m = std::round(100.0 * (inverted_black - g_fill) / inverted_black);
            y = std::round(100.0 * (inverted_black - b_fill) / inverted_black);
        }
        
        k = std::round(100.0 * black);
    }
    
    cmyk(uint8_t c = 0, uint8_t m = 0, uint8_t y = 0, uint8_t k = 0)
        : c(c), m(m), y(y), k(k)
    {
    }
};