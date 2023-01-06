#pragma once

#include <vector>

#include "../motor/Motor.hpp"

class BrushController {
public:
    BrushController();
    ~BrushController() = default;

    bool init();

    bool paint(uint8_t brush_number, uint8_t steps, bool async = false);
    void wait_for_motors();

private:
    std::vector<Motor> brushes;
};