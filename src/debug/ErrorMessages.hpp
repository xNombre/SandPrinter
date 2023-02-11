#pragma once

#include <map>

enum class ErrorMessage {
    NO_SDCARD,
    SDCARD_ERROR,
    CORRUPTED_CONFIG,
    INVALID_CONFIG,
    AXIS_BOUND_REACHED,
    NO_IMAGE_FILES,
    IMAGE_FORMAT_UNSUPPORTED
};

const inline std::map<ErrorMessage, std::string> error_messages_map = {
    // Screen limit                          |................|
    {ErrorMessage::NO_SDCARD,                "No sdcard"},
    {ErrorMessage::SDCARD_ERROR,             "Sdcard error"},
    {ErrorMessage::CORRUPTED_CONFIG,         "Config corrupted"},
    {ErrorMessage::INVALID_CONFIG,           "Config invalid"},
    {ErrorMessage::AXIS_BOUND_REACHED,       "Axis bound error"},
    {ErrorMessage::NO_IMAGE_FILES,           "No files found"},
    {ErrorMessage::IMAGE_FORMAT_UNSUPPORTED, "File unsupported"}
};