#include "util.h"

namespace core::util {

    std::string str(fsm_state state) {
        switch (state) {
        case fsm_state::resting:
            return "Resting";
        case fsm_state::working_at_construction:
            return "Working at Construction";
        case fsm_state::working_at_office:
            return "Working at Office";
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
        case loc::construction:
            return "Construction";
        case loc::office:
            return "Office";
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