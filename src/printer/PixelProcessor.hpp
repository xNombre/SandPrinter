#pragma once

#include <vector>
#include <unordered_map>

#include "../config/DynamicConstants.hpp"
#include "../config/Constants.hpp"
#include "../plotter/BrushController.hpp"
#include "../color/ColorModels.hpp"
#include "../color/ColorScaler.hpp"

class PixelProcessor {
public:
    PixelProcessor() = default;
    ~PixelProcessor() = default;

    bool init_ok();

    void paint_pixel(const rgb &pixel);

private:
    BrushController brush_controller;
    std::vector<ColorScaler> brush_scalers;

    struct brush {
        uint8_t gpio;
        DynamicConstants::Option brush_color;
        DynamicConstants::Option brush_coefficient;
        DynamicConstants::Option brush_constant;
    };

    const std::vector<brush> brush_list = {
        {Constants::MOTOR_BRUSH1_GPIO,
        DynamicConstants::Option::BRUSH_1_COLOR,
        DynamicConstants::Option::BRUSH_1_COEFF,
        DynamicConstants::Option::BRUSH_1_CONST},
        {Constants::MOTOR_BRUSH2_GPIO,
        DynamicConstants::Option::BRUSH_2_COLOR,
        DynamicConstants::Option::BRUSH_2_COEFF,
        DynamicConstants::Option::BRUSH_2_CONST},
        {Constants::MOTOR_BRUSH3_GPIO,
        DynamicConstants::Option::BRUSH_3_COLOR,
        DynamicConstants::Option::BRUSH_3_COEFF,
        DynamicConstants::Option::BRUSH_3_CONST},
        {Constants::MOTOR_BRUSH4_GPIO,
        DynamicConstants::Option::BRUSH_4_COLOR,
        DynamicConstants::Option::BRUSH_4_COEFF,
        DynamicConstants::Option::BRUSH_4_CONST},
    };

    const std::unordered_map<std::string, ColorScaler::Sensitivity> string_to_color_map = {
        {"R", ColorScaler::Sensitivity::R},
        {"G", ColorScaler::Sensitivity::G},
        {"B", ColorScaler::Sensitivity::B},
        {"C", ColorScaler::Sensitivity::C},
        {"C", ColorScaler::Sensitivity::C},
        {"Y", ColorScaler::Sensitivity::Y},
        {"K", ColorScaler::Sensitivity::K},
        {"S", ColorScaler::Sensitivity::GRAYSCALE}
    };
};