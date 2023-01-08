#pragma once

#include <stdint.h>
#include <algorithm>

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
        rgb inverted_rgb(val.r / 255, val.g / 255, val.b / 255);

        k = 1 - std::max(inverted_rgb.r, std::max(inverted_rgb.g, inverted_rgb.b));
        c = (1 - inverted_rgb.r - k) / (1 - k);
        m = (1 - inverted_rgb.g - k) / (1 - k);
        y = (1 - inverted_rgb.b - k) / (1 - k);
    }
    
    cmyk(uint8_t c = 0, uint8_t m = 0, uint8_t y = 0, uint8_t k = 0)
        : c(c), m(m), y(y), k(k)
    {
    }
};