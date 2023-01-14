#pragma once

#include "ColorModels.hpp"

class ColorScaler {
public:
    enum class Sensitivity {
        R,
        G,
        B,
        C,
        M,
        Y,
        K,
        GRAYSCALE
    };
    
    ColorScaler(Sensitivity sensitivity, double coefficient, double constant);
    ~ColorScaler() = default;

    uint32_t process_color(const rgb &pixel) const;

private:
    const Sensitivity sensitivity;
    const double constant;
    const double coefficient;

    uint8_t to_grayscale(const rgb &pixel) const;
    uint32_t scale_color(const uint8_t color) const;
    uint8_t get_sensitive_color(const rgb& pixel) const;
};