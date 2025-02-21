#include "map.h"

namespace core {

    default_map* default_map::s_instance = nullptr;

    default_map::default_map() {
        s_instance = this;
    }

} // namespace core