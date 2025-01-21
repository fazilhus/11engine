#include "util.h"

namespace core::util {

    std::string str(fsm_state state) {
        switch (state) {
        case fsm_state::resting:
            return "Resting";
        case fsm_state::working:
            return "Working";
        default:
            return "Unknown";
        }
    }

    std::string str(loc location) {
        switch (location) {
        case loc::home:
            return "Home";
        case loc::work:
            return "Work";
        default:
            return "Unknown";
        }
    }

} // namespace core