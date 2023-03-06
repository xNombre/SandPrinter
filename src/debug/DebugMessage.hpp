#pragma once

#include <stdio.h>
#include <string>
#include <map>

enum class MessageType {
    LOG = 1,
    INFO,
    WARN,
    ERR
};

const std::map<MessageType, std::string> message_types_to_color_map = {
    {MessageType::LOG,            "[LOG]  "},
    {MessageType::INFO, "\033[0;32m[INFO] "},
    {MessageType::WARN, "\033[0;33m[WARN] "},
    {MessageType::ERR,  "\033[0;31m[ERR]  "}
};

const inline std::string color_clear("\033[m ");

inline MessageType log_level = MessageType::LOG;

#ifndef DEBUG_IN_SDIO
static inline void print(MessageType type, const std::string &message) { }
#else
static void print(MessageType type, const std::string &message)
{
    if (int(type) < int(log_level)) {
        return;
    }

    auto output = message_types_to_color_map.at(type);
    output += message;
    output += color_clear;
    output += '\n';

    printf(output.c_str());
}
#endif