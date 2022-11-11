#pragma once

#include <map>

#include "AbstractService.hpp"

class ServiceList {
    enum class List {
        constants_service,
    };

    const std::map<List, AbstractService *> map = { };

};