#include "state.h"

#include <cassert>

#include "entity.h"
#include "message.h"

namespace core {

    void global_state::enter(human* h) {
        return;
    }

    void global_state::execute(human* h) {
        h->m_hunger += 1;
        h->m_thirst += 1;
        h->m_fatigue += 1;
        h->m_loneliness += 1;
    }

    void global_state::make_decision(human* h) {
        return;
    }

    void global_state::process_messages(human* h) {
        return;
    }

    void global_state::change_state(human* h) {
        return;
    }

    void global_state::exit(human* h) {
        return;
    }

    void state::enter(human* h) {
        std::cout << h->name() << " is entering state " << util::str(h->curr_state()) << '\n';
        h->m_location = util::loc_by(h->curr_state());
    }

    void state::execute(human* h) {
        if (h->curr_state() == state_type::travelling) {
            h->travel().travelled++;
            if (h->travel().travelled >= h->travel().total) {
                h->set_curr_state(util::state_by(h->travel().dest));
                h->set_next_state(state_type::none);
            }
        }
        else {
            switch (h->curr_state()) {
                case state_type::resting: {
                    h->m_hunger += 1;
                    h->m_thirst += 1;
                    h->m_fatigue -= 12;
                    h->m_loneliness += 1;
                    break;
                }
                case state_type::working_at_construction: {
                    h->m_money += 14;
                    h->m_hunger += 4;
                    h->m_thirst += 1;
                    h->m_fatigue += 7;
                    h->m_loneliness += 1;
                    break;
                }
                case state_type::working_at_office: {
                    h->m_money += 10;
                    h->m_hunger += 1;
                    h->m_thirst += 1;
                    h->m_fatigue += 4;
                    h->m_loneliness -= 3;
                    break;
                }
                case state_type::eating: {
                    h->m_money -= 7;
                    h->m_hunger -= 12;
                    h->m_thirst -= 3;
                    h->m_fatigue += 1;
                    h->m_loneliness -= 2;
                    break;
                }
                case state_type::drinking: {
                    h->m_money -= 6;
                    h->m_hunger -= 3;
                    h->m_thirst -= 11;
                    h->m_fatigue += 1;
                    h->m_loneliness -= 4;
                    break;
                }
                case state_type::partying: {
                    h->m_money -= 10;
                    h->m_hunger -= 4;
                    h->m_thirst -= 6;
                    h->m_fatigue += 2;
                    h->m_loneliness -= 11;
                    break;
                }
                case state_type::shopping: {
                    h->m_money -= 11;
                    h->m_hunger += 1;
                    h->m_thirst += 1;
                    h->m_fatigue += 3;
                    h->m_loneliness += 1;
                    break;
                }
                case state_type::travelling: {
                    h->m_hunger += 1;
                    h->m_thirst += 1;
                    h->m_fatigue += 1;
                    h->m_loneliness += 1;
                    h->travel().travelled += 1;
                    break;
                }
                default:
                    assert(false && "unreachable state");
            }
        }
    }

    void make_decision_by(human* h) {
        if (h->should_eat() && h->curr_state() != state_type::eating) {
            h->send_invite(message_type::go_eating, h->id());
            h->set_next_state(state_type::travelling);
            h->travel().start_travelling_to(loc_type::restaurant, 1);
        }
        else if (h->should_drink() && h->curr_state() != state_type::drinking) {
            h->send_invite(message_type::go_drinking, h->id());
            h->set_next_state(state_type::travelling);
            h->travel().start_travelling_to(loc_type::bar, 1);
        }
        else if (h->is_tired() && h->curr_state() != state_type::resting) {
            h->set_next_state(state_type::travelling);
            h->travel().start_travelling_to(loc_type::home, 1);
        }
        else if (h->should_party() && h->curr_state() != state_type::partying) {
            h->send_invite(message_type::go_partying, h->id());
            h->set_next_state(state_type::travelling);
            h->travel().start_travelling_to(loc_type::party, 1);
        }
        else if (h->should_shop() && h->curr_state() != state_type::shopping) {
            h->send_invite(message_type::go_shopping, h->id());
            h->set_next_state(state_type::travelling);
            h->travel().start_travelling_to(loc_type::mall, 1);
        }
        else if (h->is_not_tired() && h->curr_state() != state_type::working_at_construction) {
            h->set_next_state(state_type::travelling);
            h->travel().start_travelling_to(loc_type::construction, 1);
        }
        else if (h->curr_state() != state_type::working_at_office) {
            h->set_next_state(state_type::travelling);
            h->travel().start_travelling_to(loc_type::office, 1);
        }
    }

    void state::make_decision(human* h) {
        if (h->curr_state() == state_type::travelling) {
            const auto& t = h->travel();
            if (t.travelled < t.total) {
                return;
            }

            h->set_next_state(util::state_by(t.dest));
            return;
        }

        switch (h->curr_state()) {
            case state_type::travelling: {

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
            case state_type::resting: {
                if (!h->is_not_tired()) return;
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
            case state_type::working_at_construction:
            case state_type::working_at_office: {
                make_decision_by(h);
                break;
            }
            default:
                assert(false && "unreachable state");
        }
    }

    void state::process_messages(human* h) {
        if (h->curr_state() == state_type::travelling) {
            const auto& t = h->travel();
            if (t.travelled < t.total) {
                return;
            }

            h->set_next_state(util::state_by(t.dest));
            return;
        }

        if (!h->inbox().has_messages()) {
            return;
        }

        if (h->inbox().has_messages_of_type(message_type::go_eating)
            && h->could_eat()) {
            h->accept_invite(message_type::go_eating);
            h->set_next_state(state_type::travelling);
            h->travel().start_travelling_to(loc_type::restaurant, 1);
        }
        else if (h->inbox().has_messages_of_type(message_type::go_drinking)
            && h->could_drink()) {
            h->accept_invite(message_type::go_drinking);
            h->set_next_state(state_type::travelling);
            h->travel().start_travelling_to(loc_type::bar, 1);
        }
        else if (h->inbox().has_messages_of_type(message_type::go_partying)
            && h->could_party()) {
            h->accept_invite(message_type::go_partying);
            h->set_next_state(state_type::travelling);
            h->travel().start_travelling_to(loc_type::party, 1);
        }
        else if (h->inbox().has_messages_of_type(message_type::go_shopping)
            && h->could_shop()) {
            h->accept_invite(message_type::go_shopping);
            h->set_next_state(state_type::travelling);
            h->travel().start_travelling_to(loc_type::mall, 1);
        }
    }

    void state::change_state(human* h) {
        h->change_state();
    }

    void state::exit(human* h) {
        std::cout << h->name() << " is exiting state " << util::str(h->curr_state()) << '\n';
    }

} // namespace core