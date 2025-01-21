#include "util.h"

namespace core::util {

    std::string str(fsm_state state) {
        switch (state) {
        case fsm_state::resting:
            return "Resting";
        case fsm_state::working:
            return "Working";
        case fsm_state::eating:
            return "Eating";
        case fsm_state::drinking:
            return "Drinking";
        case fsm_state::partying:
            return "Partying";
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
        case loc::restaurant:
            return "Restaurant";
        case loc::bar:
            return "Bar";
        case loc::party:
            return "Party";
        default:
            return "Unknown";
        }
    }

} // namespace core