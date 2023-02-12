#include "FileSelector.hpp"

#include <display/Display.hpp>
#include <sd_card/File.hpp>
#include <sd_card/Storage.hpp>
#include <button/Button.hpp>
#include <config/Constants.hpp>
#include <views/Views.hpp>
#include <leds/StatusLed.hpp>

FileSelector::FileSelector(const std::string &directory, const std::string &extension)
    : directory(directory)
{
    if (!extension.empty())
        this->extension = '.' + extension;
}

std::optional<std::string> FileSelector::enter_menu()
{
    if (!load_file_list())
        return std::nullopt;

    return get_user_selection();
}

bool FileSelector::load_file_list()
{
    auto storage_instance = Storage::get_instance();
    file_list = storage_instance->list_files_in_directory(directory);

    file_list.erase(std::remove_if(file_list.begin(), file_list.end(), [&](const std::string &name) {
        return name.substr(name.size() - extension.size()) != extension;
                                   }), file_list.end());

    return file_list.size() != 0;
}

std::string FileSelector::get_user_selection()
{
    bool user_input_event_select = false;
    file_list_iterator_t current_selection = file_list.begin();
    auto last_selection = current_selection;

    Button up(StaticConstants::BUTTON_UP_GPIO);
    Button ok(StaticConstants::BUTTON_OK_GPIO);
    Button down(StaticConstants::BUTTON_DOWN_GPIO);

    up.set_callback([&] {
        if (current_selection == file_list.begin())
        current_selection = file_list.end() - 1;
        else
            current_selection--;
                    });
    ok.set_callback([&] {user_input_event_select = true;});

    down.set_callback([&] {
        current_selection++;
    if (current_selection == file_list.end())
        current_selection = file_list.begin();
                      });

    while (!user_input_event_select) {
        auto message = DisplayMessages::FileMenu::get(file_list, current_selection);
        MessagePrinter::print_message(message);

        last_selection = current_selection;
        while (last_selection == current_selection && !user_input_event_select)
            __wfi();

        StatusLed::get_instance()->blink();
    }

    return *current_selection;
}