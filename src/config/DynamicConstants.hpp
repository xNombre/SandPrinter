#pragma once

#include <memory>
#include <string>
#include <optional>
#include <unordered_map>

#include <sd_card/File.hpp>

class DynamicConstants;
using DynamicConstantsInstance = std::shared_ptr<DynamicConstants>;

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
        BRUSH_4_CONST,
        ASYNC_PRINT
    };

    static std::shared_ptr<DynamicConstants> get_instance();

    bool load_constants();
    std::optional<std::string> get_value(Option param);
    bool value_is_available(Option param);
    std::optional<int64_t> get_value_int(Option param);
    bool get_value_bool(Option param);
    std::optional<double> get_value_double(Option param);

private:
    DynamicConstants() = default;
    ~DynamicConstants() = default;

    bool read_config_file(File &file);

    static std::shared_ptr<DynamicConstants> instance;

    // Pair stores name in config file and whether parameter is required
    const std::unordered_map<std::string, std::pair<Option, bool>> option_strings_map = {
        {"DEBUG",{Option::DEBUG, false}},
        {"MAX_HEIGHT",{Option::MAX_HEIGHT, true}},
        {"MAX_WIDTH",{Option::MAX_WIDTH, true}},
        {"STEPS_PER_PIXEL",{Option::STEPS_PER_PIXEL, true}},
        {"DUTY_MOVE_SPEED",{Option::DUTY_MOVE_SPEED, true}},
        {"FREE_MOVE_SPEED",{Option::FREE_MOVE_SPEED, true}},
        {"AUTOPOSITIONING",{Option::AUTOPOSITIONING, false}},
        {"POSITIONING_PRECISE_SPEED",{Option::POSITIONING_PRECISE_SPEED, false}},
        {"POSITIONING_ROUGH_SPEED",{Option::POSITIONING_ROUGH_SPEED,  false}},
        {"BRUSH_MOTOR_SPEED",{Option::BRUSH_MOTOR_SPEED, true}},
        {"PAINT_DELAY", {Option::PAINT_DELAY, true}},
        {"BRUSH_1_COLOR", {Option::BRUSH_1_COLOR, true}},
        {"BRUSH_2_COLOR", {Option::BRUSH_2_COLOR, false}},
        {"BRUSH_3_COLOR", {Option::BRUSH_3_COLOR, false}},
        {"BRUSH_4_COLOR", {Option::BRUSH_4_COLOR, false}},
        {"BRUSH_1_COEFF", {Option::BRUSH_1_COEFF, true}},
        {"BRUSH_1_CONST", {Option::BRUSH_1_CONST, true}},
        {"BRUSH_2_COEFF", {Option::BRUSH_2_COEFF, false}},
        {"BRUSH_2_CONST", {Option::BRUSH_2_CONST, false}},
        {"BRUSH_3_COEFF", {Option::BRUSH_3_COEFF, false}},
        {"BRUSH_3_CONST", {Option::BRUSH_3_CONST, false}},
        {"BRUSH_4_COEFF", {Option::BRUSH_4_COEFF, false}},
        {"BRUSH_4_CONST", {Option::BRUSH_4_CONST, false}},
        {"ASYNC_PRINT", {Option::ASYNC_PRINT, true}},
    };

    std::unordered_map<Option, std::string> param_values = {
        {Option::DEBUG, "0"}
    };
};