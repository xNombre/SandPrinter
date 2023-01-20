#include "PrinterJob.hpp"

#include "../sd_card/File.hpp"
#include "../sd_card/Storage.hpp"
#include "../config/DynamicConstants.hpp"
#include "../views/Views.hpp"
#include "../button/Button.hpp"
#include "../config/Constants.hpp"
#include "../debug/ErrorHandler.hpp"
#include "../leds/StatusLed.hpp"

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
    DisplayMessages::message_list status_message, debug_message;
    Button detailed_info_button(Constants::BUTTON_DOWN_GPIO);
    uint32_t finished_pixels = 0, all_pixels;
    bool debug_view = false;

    all_pixels = image->get_height() * image->get_width();
    head_controller->set_mode(HeadController::MotorMode::DUTY);
    detailed_info_button.set_callback([&] {
        debug_view = !debug_view;
    });

    while (!image->eof()) {
        const auto &pixel = image->get_next_pixel();
        const auto &new_pos = image->get_current_pixel_position();

        debug_message = DisplayMessages::Debug::get(new_pos.x, new_pos.y, 0, 0, pixel.r, pixel.g, pixel.b);
        status_message = DisplayMessages::PrintProgress::get(finished_pixels, all_pixels);
        MessagePrinter::print_message(debug_view ? debug_message : status_message);
        
        pixel_processor.paint_pixel(pixel);

        auto position_status = head_controller->goto_position(new_pos.x * pixel_size, new_pos.y * pixel_size);
        if (!position_status)
            fatal_error("goto_position failed");

        finished_pixels++;
    }

    return true;
}
