#include "enum.h"

#include <cassert>

namespace core::util {

    std::string state_to_str(uint8_t state) {
        switch (state) {
        case state_type_travelling:
            return "Travelling";
        default:
            return "Unknown";
        }
    }

    std::string loc_to_str(uint8_t location) {
        switch (location) {
        case loc_type_road:
            return "Road";
        default:
            return "Unknown";
        }
    }

    std::string msg_to_str(uint8_t type) {
        switch (type) {
        default:
            return "Unknown";
        }
    }

    uint8_t loc_by_state(uint8_t s) {
        switch (s) {
            case state_type_travelling:
                return loc_type_road;
            default: {
#ifdef DEBUG
                assert(false && "unreachable state type");
#endif
                return loc_type_none;
            }
        }
    }

    uint8_t loc_by_msg(uint8_t m) {
        switch (m) {
            default: {
#ifdef DEBUG
                assert(false && "unreachable message type");
#endif
                return loc_type_none;
            }
        }
    }

    uint8_t state_by_loc(uint8_t l) {
        switch (l) {
            case loc_type_road:
                return state_type_travelling;
            default: {
#ifdef DEBUG
                assert(false && "unreachable loc type");
#endif
                return state_type_none;
            }
        }
    }

    uint8_t state_by_msg(uint8_t m) {
        switch (m) {
            default: {
#ifdef DEBUG
                assert(false && "unreachable message type");
#endif
                return state_type_none;
            }
        }
    }

} // namespace core::util