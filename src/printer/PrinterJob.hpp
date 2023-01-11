#pragma once

#include <string>
#include "../plotter/BrushController.hpp"
#include "../plotter/HeadController.hpp"
#include "../bmp/Bmp.hpp"
#include "../display/Display.hpp"

class PrinterJob {
public:
    PrinterJob();
    ~PrinterJob() = default;

    bool prepare_job(const std::string &filename);
    bool start_job();

private:
    BrushController brush_controller;
    HeadControllerInstance head_controller;
    std::unique_ptr<Bmp> image;
};