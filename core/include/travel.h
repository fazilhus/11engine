#pragma once

#include <memory>

#include "tile.h"

namespace core {

    /// Represents a link between two locations with a distance.
    struct link {
        std::weak_ptr<tile> m_to; ///< The destination location.
    };

} // namespace core