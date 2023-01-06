#pragma once

#include "../motor/Motor.hpp"

class HeadController {
public:
    HeadController();
    ~HeadController() = default;

    bool init();

    bool goto_position(uint32_t x, uint32_t y, bool async = false);
    void wait_for_motors();

    uint32_t get_x() const;
    uint32_t get_y() const;

private:
    Motor x_axis;
    Motor y_axis;

    uint32_t x;
    uint32_t y;
};