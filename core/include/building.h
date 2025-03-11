#pragma once

#include <array>

#include "enum.h"

namespace core {

    struct building {
        building_type type;
        std::array<int, resource_type_num> contents;

        building(building_type type) : type(type), contents({}) {}
        building() : building(type) {}

        int get_resource(resource_type type) { return contents[type]; }

        int put_resource(resource_type type) { return ++contents[type]; }

        int take_resource(resource_type type) { return --contents[type]; }
    };

} // namespace core