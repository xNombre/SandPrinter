#include "PrinterJob.hpp"

#include "../sd_card/File.hpp"
#include "../sd_card/Storage.hpp"
#include "../config/DynamicConstants.hpp"
#include "../views/Views.hpp"

namespace Constant
{
    const std::string images_location = "images/";
}

PrinterJob::PrinterJob()
    : head_controller(HeadController::get_instance())
{
    auto dynamic_config = DynamicConstants::get_instance();
}

bool PrinterJob::prepare_job(const std::string &filename)
{
    auto storage_instance = Storage::get_instance();

    if (!storage_instance->file_exists(Constant::images_location + filename))
        return false;

    auto file = storage_instance->open_file(Constant::images_location + filename, File::Mode::READ);

    if (!file)
        return false;

    image = std::make_unique<Bmp>(std::move(file.value()), Bmp::ReadingOrder::ZIGZAG);

    return image->load_file();
}

bool PrinterJob::start_job()
{
    uint32_t finished_pixels = 0, all_pixels;

    all_pixels = image->get_height() * image->get_width();

    auto message = DisplayMessages::PrintProgress::get(finished_pixels, all_pixels);
    MessagePrinter::print_message(message);

    while (1);

    return true;
}
