#include "PixelProcessor.hpp"

bool PixelProcessor::init_ok()
{
    auto dynamic_config = DynamicConstants::get_instance();

    for (const auto &brush : brush_list) {
        if (!dynamic_config->value_is_available(brush.brush_color))
            break;

        const auto color_str = dynamic_config->get_value(brush.brush_color).value();
        if (string_to_color_map.find(color_str) == string_to_color_map.end())
            return false;

        const auto color = string_to_color_map.at(color_str);

        if (!dynamic_config->value_is_available(brush.brush_coefficient) ||
            !dynamic_config->value_is_available(brush.brush_constant)) {
            return false;
        }

        const auto coeff = dynamic_config->get_value_double(brush.brush_coefficient).value();
        const auto constant = dynamic_config->get_value_double(brush.brush_constant).value();

        brush_scalers.push_back(ColorScaler(color, coeff, constant));
    }

    return brush_scalers.size() > 0;
}

void PixelProcessor::paint_pixel(const rgb &pixel)
{
    for (uint8_t i = 0; i < brush_scalers.size(); i++) {
        auto steps = brush_scalers[i].process_color(pixel);
        brush_controller.paint(i, steps, true);
    }
    brush_controller.wait_for_motors();
}