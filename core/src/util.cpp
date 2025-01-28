#include "util.h"

#include <ctime>
#include <cassert>

namespace core::util {

    std::string str(state_type state) {
        switch (state) {
        case state_type::resting:
            return "Resting";
        case state_type::working_at_construction:
            return "Working at Construction";
        case state_type::working_at_office:
            return "Working at Office";
        case state_type::eating:
            return "Eating";
        case state_type::drinking:
            return "Drinking";
        case state_type::partying:
            return "Partying";
        case state_type::shopping:
            return "Shopping";
        case state_type::travelling:
            return "Travelling";
        default:
            return "Unknown";
        }
    }

    std::string str(loc_type location) {
        switch (location) {
        case loc_type::home:
            return "Home";
        case loc_type::construction:
            return "Construction";
        case loc_type::office:
            return "Office";
        case loc_type::restaurant:
            return "Restaurant";
        case loc_type::bar:
            return "Bar";
        case loc_type::party:
            return "Party";
        case loc_type::mall:
            return "Mall";
        case loc_type::road:
            return "Road";
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
        case message_type::go_shopping:
            return "Go Shopping";
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

    loc_type loc_by(state_type s) {
        switch (s) {
            case state_type::resting:
                return loc_type::home;
            case state_type::working_at_construction:
                return loc_type::construction;
            case state_type::working_at_office:
                return loc_type::office;
            case state_type::eating:
                return loc_type::restaurant;
            case state_type::drinking:
                return loc_type::bar;
            case state_type::partying:
                return loc_type::party;
            case state_type::shopping:
                return loc_type::mall;
            case state_type::travelling:
                return loc_type::road;
            default:
                assert(false && "unreachable state");
        }
    }

    state_type state_by(loc_type l) {
        switch (l) {
            case loc_type::home:
                return state_type::resting;
            case loc_type::construction:
                return state_type::working_at_construction;
            case loc_type::office:
                return state_type::working_at_office;
            case loc_type::restaurant:
                return state_type::eating;
            case loc_type::bar:
                return state_type::drinking;
            case loc_type::party:
                return state_type::partying;
            case loc_type::mall:
                return state_type::shopping;
            case loc_type::road:
                return state_type::travelling;
            default: {
                assert(false && "unreachable location");
            }
        }
    }

} // namespace core::util