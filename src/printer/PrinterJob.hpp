#pragma once

#include <string>

#include <plotter/BrushController.hpp>
#include <plotter/HeadController.hpp>
#include <bmp/Bmp.hpp>
#include <display/Display.hpp>
#include <color/ColorScaler.hpp>

#include "PixelProcessor.hpp"

class PrinterJob {
public:
    PrinterJob();
    ~PrinterJob() = default;

    bool prepare_job(const std::string &filename);
    bool start_job();

private:
    BrushController brush_controller;
    HeadControllerInstance head_controller;
    PixelProcessor pixel_processor;
    std::unique_ptr<Bmp> image;
    uint32_t pixel_size;
    uint32_t max_height_px;
    uint32_t max_width_px;
};