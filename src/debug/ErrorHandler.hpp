#pragma once

#include <string>

#include "pico/stdlib.h"

void fatal_error(const std::string &msg)
{
    // get display service and display error message
    panic(msg.c_str());
}