#include "DynamicConstants.hpp"

#include <sd_card/Storage.hpp>
#include <utils/string_trim.hpp>
#include <debug/DebugMessage.hpp>

std::shared_ptr<DynamicConstants> DynamicConstants::instance;

namespace Constant
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

    if (!sd_card->file_exists(Constant::config_file_name))
        return false;

    auto ret = sd_card->open_file(Constant::config_file_name, File::Mode::READ);
    if (!ret)
        return false;

    if (!read_config_file(ret.value()))
        return false;

    return are_required_constants_loaded();
}

bool DynamicConstants::read_config_file(File &file)
{
    print(MessageType::INFO, "Reading configuration file...");
    
    while (!file.eof()) {
        auto line = file.read_line();

        if (line.empty() || line[0] == Constant::comment_indicator)
            continue;

        auto option_end = line.find(Constant::option_equals);
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
            if (option.second == true) {
                print(MessageType::WARN, "Required option value is empty! -> " + option_string);
                return false;
            }
            
            continue;
        }

        param_values[option.first] = option_value;
        print(MessageType::LOG, "Value: " + option_string + " -> " + option_value);
    }

    return true;
}

std::optional<std::string> DynamicConstants::get_value(Option param) const
{
    if (!value_is_available(param))
        return std::nullopt;

    return param_values.at(param);
}

bool DynamicConstants::value_is_available(Option param) const
{
    return param_values.find(param) != param_values.end();
}

std::optional<int64_t> DynamicConstants::get_value_int(Option param) const
{
    if (!value_is_available(param))
        return std::nullopt;

    return std::stoll(param_values.at(param));
}

bool DynamicConstants::get_value_bool(Option param) const
{
    auto value = get_value(param);
    if (value && value.value() == Constant::enabled_option)
        return true;

    return false;
}

std::optional<double> DynamicConstants::get_value_double(Option param) const
{
    if (!value_is_available(param))
        return std::nullopt;

    return std::stod(param_values.at(param));
}

bool DynamicConstants::are_required_constants_loaded() const {
    for (const auto &option : option_strings_map) {
        if (!option.second.second) {
            continue;
        }

        if (!value_is_available(option.second.first)) {
            print(MessageType::WARN, "Required option is nonexistent! -> " + option.first);
            return false;
        }
    }

    return true;
}