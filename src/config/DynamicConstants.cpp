#include "DynamicConstants.hpp"

#include "../sd_card/Storage.hpp"
#include "../utils/string_trim.hpp"

namespace Constants
{
    const std::string config_file_name = "config.txt";
    const std::string enabled_option = "1";
    const char comment_indicator = '#';
    const char option_equals = '=';
}

std::shared_ptr<DynamicConstants> DynamicConstants::get_instance()
{
    class public_cstor: public DynamicConstants {};

    if (!instance) {
        instance = std::make_shared<public_cstor>();
    }

    return instance;
}

bool DynamicConstants::load_constants()
{
    auto sd_card = Storage::get_instance();

    if (!sd_card->file_exists(Constants::config_file_name))
        return false;

    auto ret = sd_card->open_file("", Constants::config_file_name, FileMode::READ);
    if (!ret)
        return false;

    // TODO: check if all required options are filled
    return read_config_file(ret.value());
}

bool DynamicConstants::read_config_file(File &file)
{
    while (!file.eof()) {
        auto line = file.read_line();

        if (line.empty() || line[0] == Constants::comment_indicator)
            continue;

        auto option_end = line.find(Constants::option_equals);
        if (option_end == std::string::npos)
            continue;

        auto option_string = line.substr(0, option_end - 1);
        remove_spaces(option_string);

        if (option_strings_map.find(option_string) == option_strings_map.end())
            continue;

        auto option = option_strings_map.at(option_string);

        auto option_value = line.substr(option_end + 1);
        remove_spaces(option_value);

        if (option_value.empty()) {
            if (option.second == true)
                return false;
            continue;
        }

        param_values[option.first] = option_value;
    }

    return true;
}

std::optional<std::string> DynamicConstants::get_value(Option param)
{
    if (!value_is_available(param))
        return std::nullopt;

    return param_values[param];
}

bool DynamicConstants::value_is_available(Option param)
{
    return param_values.find(param) != param_values.end();
}

std::optional<int64_t> DynamicConstants::get_value_int(Option param)
{
    if (!value_is_available(param))
        return std::nullopt;

    return std::stoll(param_values[param]);
}

bool DynamicConstants::get_value_bool(Option param)
{
    auto value = get_value(param);
    if (value && value.value() == Constants::enabled_option)
        return true;

    return false;
}