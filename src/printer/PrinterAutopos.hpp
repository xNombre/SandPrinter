#pragma once

#include "../plotter/HeadController.hpp"

class PrinterAutopos {
public:
    PrinterAutopos(HeadController& head_controller);
    ~PrinterAutopos();

    void enter_menu();

private:
    HeadController& head_controller;
};