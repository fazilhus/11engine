#include "enum.h"

#include <cassert>

namespace core::util {

    std::string state_to_str(uint8_t state) {
        switch (state) {
        case state_type_resting:
            return "Resting";
        case state_type_working_at_construction:
            return "Working at Construction";
        case state_type_working_at_office:
            return "Working at Office";
        case state_type_eating:
            return "Eating";
        case state_type_drinking:
            return "Drinking";
        case state_type_partying:
            return "Partying";
        case state_type_shopping:
            return "Shopping";
        case state_type_travelling:
            return "Travelling";
        default:
            return "Unknown";
        }
    }

    std::string loc_to_str(uint8_t location) {
        switch (location) {
        case loc_type_home:
            return "Home";
        case loc_type_construction:
            return "Construction";
        case loc_type_office:
            return "Office";
        case loc_type_restaurant:
            return "Restaurant";
        case loc_type_bar:
            return "Bar";
        case loc_type_party:
            return "Party";
        case loc_type_mall:
            return "Mall";
        case loc_type_road:
            return "Road";
        default:
            return "Unknown";
        }
    }

    std::string msg_to_str(uint8_t type) {
        switch (type) {
        case message_type_go_eating:
            return "Go Eating";
        case message_type_go_drinking:
            return "Go Drinking";
        case message_type_go_partying:
            return "Go Partying";
        case message_type_go_shopping:
            return "Go Shopping";
        default:
            return "Unknown";
        }
    }

    uint8_t loc_by_state(uint8_t s) {
        switch (s) {
            case state_type_resting:
                return loc_type_home;
            case state_type_working_at_construction:
                return loc_type_construction;
            case state_type_working_at_office:
                return loc_type_office;
            case state_type_eating:
                return loc_type_restaurant;
            case state_type_drinking:
                return loc_type_bar;
            case state_type_partying:
                return loc_type_party;
            case state_type_shopping:
                return loc_type_mall;
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
            case message_type_go_eating:
                return loc_type_restaurant;
            case message_type_go_drinking:
                return loc_type_bar;
            case message_type_go_partying:
                return loc_type_party;
            case message_type_go_shopping:
                return loc_type_mall;
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
            case loc_type_home:
                return state_type_resting;
            case loc_type_construction:
                return state_type_working_at_construction;
            case loc_type_office:
                return state_type_working_at_office;
            case loc_type_restaurant:
                return state_type_eating;
            case loc_type_bar:
                return state_type_drinking;
            case loc_type_party:
                return state_type_partying;
            case loc_type_mall:
                return state_type_shopping;
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
            case message_type_go_eating:
                return state_type_eating;
            case message_type_go_drinking:
                return state_type_drinking;
            case message_type_go_partying:
                return state_type_partying;
            case message_type_go_shopping:
                return state_type_shopping;
            default: {
#ifdef DEBUG
                assert(false && "unreachable message type");
#endif
                return state_type_none;
            }
        }
    }

} // namespace core::util