#pragma once

#include <algorithm>
#include <string>

std::string &remove_spaces(std::string &str)
{
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) {
        return std::isspace(c);
    }), str.end());

    return str;
}