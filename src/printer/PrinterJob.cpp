#include "PrinterJob.hpp"

#include "../sd_card/File.hpp"
#include "../sd_card/Storage.hpp"
#include "../config/DynamicConstants.hpp"
#include "../views/Views.hpp"
#include "../button/Button.hpp"
#include "../config/Constants.hpp"
#include "../debug/ErrorHandler.hpp"
#include "../leds/StatusLed.hpp"
#include "../debug/DebugMessage.hpp"

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

    bool pixel_was_skipped = false;
    while (!image->eof()) {
        const auto &pixel = image->get_next_pixel();

        if (!pixel_processor.is_pixel_interesting(pixel.color)) {
            print(MessageType::LOG, "Skipping pixel: X" + std::to_string(pixel.x) + "Y" + std::to_string(pixel.y));
            pixel_was_skipped = true;
            continue;
        }
        
        debug_message = DisplayMessages::Debug::get(pixel.x, pixel.y, 0, 0, pixel.color.r, pixel.color.g, pixel.color.b);
        status_message = DisplayMessages::PrintProgress::get(finished_pixels, all_pixels);
        MessagePrinter::print_message(debug_view ? debug_message : status_message);

        if (pixel_was_skipped) {
            head_controller->set_mode(HeadController::MotorMode::FREE);
        }
        
        print(MessageType::LOG, "Move head to: X" + std::to_string(pixel.x) + "Y" + std::to_string(pixel.y));
        auto position_status = head_controller->goto_position(pixel.x * pixel_size, pixel.y * pixel_size);
        if (!position_status)
            fatal_error("goto_position failed");

        if (pixel_was_skipped) {
            head_controller->set_mode(HeadController::MotorMode::DUTY);
            pixel_was_skipped = false;
        }
        
        print(MessageType::LOG, "Paint color: R" + std::to_string(pixel.color.r) + "G" + std::to_string(pixel.color.g) + "B" + std::to_string(pixel.color.b));
        pixel_processor.paint_pixel(pixel.color);

        finished_pixels++;
    }

    return true;
}
