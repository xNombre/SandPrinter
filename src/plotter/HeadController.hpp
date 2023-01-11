#pragma once

#include <memory>

#include "../motor/Motor.hpp"
#include "../config/DynamicConstants.hpp"

class HeadController;
using HeadControllerInstance = std::shared_ptr<HeadController>;

class HeadController {
public:
    enum class MotorMode {
        DUTY,
        FREE
    };
    enum class Axis {
        X,
        Y
    };

    static HeadControllerInstance get_instance();

    bool autoposition_axes();

    bool goto_position(uint32_t x, uint32_t y, bool async = false);
    void wait_for_motors();
    void set_mode(MotorMode mode);

    // !!CAREFULL!!
    // Moves motor without any bound checks
    // Used for manual positioning
    void move_motor_raw(Axis axis, Motor<>::Direction dir, uint32_t steps, bool async = false);
    
    void reset_axes_position();
    
    uint32_t get_x() const;
    uint32_t get_y() const;

private:
    HeadController();
    ~HeadController() = default;

    static HeadControllerInstance instance;

    Motor<> x_axis_motor;
    Motor<> y_axis_motor;

    uint32_t x_pos = 0;
    uint32_t y_pos = 0;

    uint32_t max_x;
    uint32_t max_y;

    uint32_t duty_speed;
    uint32_t free_speed;

    bool autoposition_axis(Motor<> &axis_motor, const uint8_t axis_switch_gpio);
    void move_motor(Motor<> &motor, Motor<>::Direction dir, uint32_t steps, bool async);
};