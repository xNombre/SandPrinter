#pragma once

#include "../plotter/HeadController.hpp"

class PrinterSettings {
public:
    PrinterSettings(HeadController &head_controller);
    ~PrinterSettings() = default;

    void enter_menu();

private:
    HeadController &head_controller;
};