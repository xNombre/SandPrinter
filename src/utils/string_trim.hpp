#pragma once

#include <algorithm>
#include <string>

std::string &remove_spaces(std::string &str)
{
    std::remove_if(str.begin(), str.end(), [](unsigned char c) {
        return std::isspace(c);
    });
}