#include "PrinterJob.hpp"

#include "../sd_card/File.hpp"
#include "../sd_card/Storage.hpp"
#include "../config/DynamicConstants.hpp"
#include "../views/Views.hpp"
#include "../button/Button.hpp"
#include "../config/Constants.hpp"
#include "../debug/ErrorHandler.hpp"

namespace Constant
{
    const std::string images_location = "images/";
}

PrinterJob::PrinterJob()
    : head_controller(HeadController::get_instance())
{
    auto dynamic_config = DynamicConstants::get_instance();

    auto val = dynamic_config->get_value_int(DynamicConstants::Option::STEPS_PER_PIXEL);
    if (val)
        pixel_size = val.value();

    const auto max_width = dynamic_config->get_value_int(DynamicConstants::Option::MAX_WIDTH).value();
    const auto max_height = dynamic_config->get_value_int(DynamicConstants::Option::MAX_HEIGHT).value();

    max_width_px = max_width * pixel_size;
    max_height_px = max_height * pixel_size;
}

bool PrinterJob::prepare_job(const std::string &filename)
{
    auto storage_instance = Storage::get_instance();

    auto file = storage_instance->open_file(Constant::images_location + filename, File::Mode::READ);
    if (!file)
        return false;

    image = std::make_unique<Bmp>(std::move(file.value()), Bmp::ReadingOrder::ZIGZAG);

    auto load_img = image->load_file();
    if (!load_img)
        return false;

    if (image->get_height() > max_height_px ||
        image->get_width() > max_width_px)
        return false;

    if (!pixel_processor.init_ok())
        return false;

    return true;
}

bool PrinterJob::start_job()
{
    Button detailed_info_button(Constants::BUTTON_DOWN_GPIO);
    uint32_t finished_pixels = 0, all_pixels;
    uint32_t pixels_in_row = image->get_width() * pixel_size;
    bool zigzag_bit = true;
    bool debug_view = false;

    all_pixels = image->get_height() * image->get_width();
    head_controller->set_mode(HeadController::MotorMode::DUTY);
    detailed_info_button.set_callback([&] { debug_view = !debug_view; });

    while (!image->eof()) {
        auto x = head_controller->get_x();
        auto y = head_controller->get_y();

        if (x == 0 || x == pixels_in_row) {
            zigzag_bit = !zigzag_bit;
            y += 1;
        }
        else {
            x = zigzag_bit ? x + pixel_size : x - pixel_size;
        }
        auto position_status = head_controller->goto_position(x, y);
        if (!position_status)
            fatal_error("goto_position failed");

        const auto &pixel = image->get_next_pixel();

        DisplayMessages::message_list message;
        if (debug_view) {
            message = DisplayMessages::Debug::get(x, y, 0, 0, pixel.r, pixel.g, pixel.b);
        }
        else {
            message = DisplayMessages::PrintProgress::get(finished_pixels, all_pixels);
        }
        MessagePrinter::print_message(message);

        pixel_processor.paint_pixel(pixel);

        finished_pixels++;
    }

    return true;
}
