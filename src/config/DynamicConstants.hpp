#pragma once

#include <memory>
#include <string>
#include <optional>
#include <unordered_map>

class DynamicConstants {
public:
    enum class Option {
        DEBUG,
        MAX_HEIGHT,
        MAX_WIDTH,
        STEPS_PER_PIXEL,
        DUTY_MOVE_SPEED,
        FREE_MOVE_SPEED,
        AUTOPOSITIONING,
        POSITIONING_PRECISE_SPEED,
        POSITIONING_ROUGH_SPEED,
        BRUSH_MOTOR_SPEED,
        PAINT_DELAY,
        BRUSH_1_COLOR,
        BRUSH_2_COLOR,
        BRUSH_3_COLOR,
        BRUSH_4_COLOR,
        BRUSH_1_COEFF,
        BRUSH_1_CONST,
        BRUSH_2_COEFF,
        BRUSH_2_CONST,
        BRUSH_3_COEFF,
        BRUSH_3_CONST,
        BRUSH_4_COEFF,
        BRUSH_4_CONST
    };

    DynamicConstants();
    ~DynamicConstants();

    static std::shared_ptr<DynamicConstants> get_instance();

    bool load_constants();
    std::optional<std::string> get_value(Option param);

private:
    std::shared_ptr<DynamicConstants> instance;

    // Pair stores name in config file and whether parameter is required
    const std::unordered_map<Option, std::pair<std::string, bool>> param_strings = {
        {Option::DEBUG, {"{DEBUG", false}},
        {Option::MAX_HEIGHT, {"MAX_HEIGHT", true}},
        {Option::MAX_WIDTH, {"MAX_WIDTH", true}},
        {Option::STEPS_PER_PIXEL, {"STEPS_PER_PIXEL", true}},
        {Option::DUTY_MOVE_SPEED, {"DUTY_MOVE_SPEED", true}},
        {Option::FREE_MOVE_SPEED, {"FREE_MOVE_SPEED", true}},
        {Option::AUTOPOSITIONING, {"AUTOPOSITIONING", false}},
        {Option::POSITIONING_PRECISE_SPEED, {"POSITIONING_PRECISE_SPEED", false}},
        {Option::POSITIONING_ROUGH_SPEED, {"POSITIONING_ROUGH_SPEED", false}},
        {Option::BRUSH_MOTOR_SPEED, {"BRUSH_MOTOR_SPEED", true}},
        {Option::PAINT_DELAY, {"PAINT_DELAY", true}},
        {Option::BRUSH_1_COLOR, {"BRUSH_1_COLOR", true}},
        {Option::BRUSH_2_COLOR, {"BRUSH_2_COLOR", false}},
        {Option::BRUSH_3_COLOR, {"BRUSH_3_COLOR", false}},
        {Option::BRUSH_4_COLOR, {"BRUSH_4_COLOR", false}},
        {Option::BRUSH_1_COEFF, {"BRUSH_1_COEFF", true}},
        {Option::BRUSH_1_CONST, {"BRUSH_1_CONST", true}},
        {Option::BRUSH_2_COEFF, {"BRUSH_2_COEFF", false}},
        {Option::BRUSH_2_CONST, {"BRUSH_2_CONST", false}},
        {Option::BRUSH_3_COEFF, {"BRUSH_3_COEFF", false}},
        {Option::BRUSH_3_CONST, {"BRUSH_3_CONST", false}},
        {Option::BRUSH_4_COEFF, {"BRUSH_4_COEFF", false}},
        {Option::BRUSH_4_CONST, {"BRUSH_4_CONST", false}}
    };

    std::unordered_map<Option, std::string> param_values = {
        {Option::DEBUG, "0"}
    };
};