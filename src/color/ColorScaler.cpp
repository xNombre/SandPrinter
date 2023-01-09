#include "ColorScaler.hpp"

#include <math.h>
#include "pico/double.h"

ColorScaler::ColorScaler(Sensitivity sensitivity, double constant, double coefficient)
    : sensitivity(sensitivity), constant(constant), coefficient(coefficient)
{
}

uint32_t ColorScaler::process_color(const rgb &pixel) const
{
    auto color = get_sensitive_color(pixel);
    return scale_color(color);
}

uint8_t ColorScaler::get_sensitive_color(const rgb& pixel) const {
    uint8_t color;

    switch (sensitivity) {
    case Sensitivity::R: {
        color = pixel.r;
        break;
    }
    case Sensitivity::G: {
        color = pixel.g;
        break;
    }
    case Sensitivity::B: {
        color = pixel.b;
        break;
    }
    case Sensitivity::GRAYSCALE:
    {
        color = to_grayscale(pixel);
        break;
    }
    case Sensitivity::C: {
        color = cmyk(pixel).c;
        break;
    }
    case Sensitivity::M: {
        color = cmyk(pixel).m;
        break;
    }
    case Sensitivity::Y: {
        color = cmyk(pixel).y;
        break;
    }
    case Sensitivity::K: {
        color = cmyk(pixel).k;
        break;
    }
    }

    return color;
}

uint8_t ColorScaler::to_grayscale(const rgb &pixel) const
{
    return (pixel.r + pixel.g + pixel.b) / 3;
}

uint32_t ColorScaler::scale_color(const uint8_t color) const
{
    auto value = double(color) * coefficient + constant;
    return double2int64_z(value);
}
