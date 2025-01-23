#include "util.h"

#include <ctime>

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

    std::string str(message_type type) {
        switch (type) {
        case message_type::go_eating:
            return "Go Eating";
        case message_type::go_drinking:
            return "Go Drinking";
        case message_type::go_partying:
            return "Go Partying";
        default:
            return "Unknown";
        }
    }

    void init_random() {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    int random_int(int min, int max) {
        return min + rand() % (max - min + 1);
    }

    float random_float(float min, float max) {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

} // namespace core::util