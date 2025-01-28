#include "state.h"

#include <cassert>

#include "entity.h"
#include "message.h"

namespace core {

    void state::enter(human* h) {
        std::cout << h->name() << " is entering state " << util::str(h->curr_state()) << '\n';
        h->m_location = util::loc_by(h->curr_state());
    }

    void state::execute(human* h) {
        std::cout << h->name() << " is " << util::str(h->curr_state()) << '\n';
        switch (h->curr_state()) {
            case state_type::resting: {
                h->m_hunger += 5;
                h->m_thirst += 5;
                h->m_fatigue -= 25;
                h->m_loneliness += 5;
                break;
            }
            case state_type::working_at_construction: {
                h->m_money += 20;
                h->m_hunger += 10;
                h->m_thirst += 5;
                h->m_fatigue += 18;
                h->m_loneliness += 5;
                break;
            }
            case state_type::working_at_office: {
                h->m_money += 15;
                h->m_hunger += 5;
                h->m_thirst += 5;
                h->m_fatigue += 15;
                h->m_loneliness -= 5;
                break;
            }
            case state_type::eating: {
                h->m_money -= 20;
                h->m_hunger -= 20;
                h->m_thirst -= 5;
                h->m_fatigue += 5;
                h->m_loneliness -= 5;
                break;
            }
            case state_type::drinking: {
                h->m_money -= 15;
                h->m_hunger -= 5;
                h->m_thirst -= 20;
                h->m_fatigue += 5;
                h->m_loneliness -= 10;
                break;
            }
            case state_type::partying: {
                h->m_money -= 30;
                h->m_hunger -= 10;
                h->m_thirst -= 20;
                h->m_fatigue += 10;
                h->m_loneliness -= 20;
                break;
            }
            case state_type::shopping: {
                h->m_money -= 30;
                h->m_hunger += 5;
                h->m_thirst += 5;
                h->m_fatigue += 8;
                h->m_loneliness += 5;
                break;
            }
            default:
                assert(false && "unreachable state");
        }
    }

    void make_decision_by(human* h) {
        if (h->should_eat() && h->curr_state() != state_type::eating) {
            h->send_invite(message_type::go_eating, h->id());
            h->set_next_state(state_type::eating);
        }
        else if (h->should_drink() && h->curr_state() != state_type::drinking) {
            h->send_invite(message_type::go_drinking, h->id());
            h->set_next_state(state_type::drinking);
        }
        else if (h->is_tired() && h->curr_state() != state_type::resting) {
            h->set_next_state(state_type::resting);
        }
        else if (h->should_party() && h->curr_state() != state_type::partying) {
            h->send_invite(message_type::go_partying, h->id());
            h->set_next_state(state_type::partying);
        }
        else if (h->should_shop() && h->curr_state() != state_type::shopping) {
            h->send_invite(message_type::go_shopping, h->id());
            h->set_next_state(state_type::shopping);
        }
        else if (h->is_not_tired() && h->curr_state() != state_type::working_at_construction) {
            h->set_next_state(state_type::working_at_construction);
        }
        else if (h->curr_state() != state_type::working_at_office) {
            h->set_next_state(state_type::working_at_office);
        }
    }

    void state::make_decision(human* h) {
        switch (h->curr_state()) {
            case state_type::resting: {
                if (!h->is_not_tired()) return;
                make_decision_by(h);
                break;
            }
            case state_type::working_at_construction:
            case state_type::working_at_office: {
                make_decision_by(h);
                break;
            }
            case state_type::eating: {
                if (h->should_continue_eat()) return;
                make_decision_by(h);
                break;
            }
            case state_type::drinking: {
                if (h->should_continue_drink()) return;
                make_decision_by(h);
                break;
            }
            case state_type::partying: {
                if (h->should_continue_party()) return;
                make_decision_by(h);
                break;
            }
            case state_type::shopping: {
                if (h->should_continue_shop()) return;
                make_decision_by(h);
                break;
            }
            default:
                assert(false && "unreachable state");
        }
    }

    void state::process_messages(human* h) {
        if (!h->inbox().has_messages()) {
            return;
        }

        if (h->inbox().has_messages_of_type(message_type::go_eating)
            && h->could_eat()) {
            h->accept_invite(message_type::go_eating);
            h->set_next_state(state_type::eating);
        }
        else if (h->inbox().has_messages_of_type(message_type::go_drinking)
            && h->could_drink()) {
            h->accept_invite(message_type::go_drinking);
            h->set_next_state(state_type::drinking);
        }
        else if (h->inbox().has_messages_of_type(message_type::go_partying)
            && h->could_party()) {
            h->accept_invite(message_type::go_partying);
            h->set_next_state(state_type::partying);
        }
        else if (h->inbox().has_messages_of_type(message_type::go_shopping)
            && h->could_shop()) {
            h->accept_invite(message_type::go_shopping);
            h->set_next_state(state_type::shopping);
        }
    }

    void state::change_state(human* h) {
        h->change_state();
    }

    void state::exit(human* h) {
        std::cout << h->name() << " is exiting state " << util::str(h->curr_state()) << '\n';
    }

} // namespace core