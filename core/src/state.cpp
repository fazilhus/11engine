#include "state.h"

#include "entity.h"
#include "message.h"

namespace core {

    state::~state() {
    }

    fsm_state decide_where_to_work(const human* e) {
        if (e->is_not_tired()) {
            return fsm_state::working_at_construction;
        }
        else {
            return fsm_state::working_at_office;
        }
    }

    void resting::enter(human* e) {
        // std::cout << "Entering resting state" << std::endl;
        e->m_fsm_state = fsm_state::resting;
        e->m_location = loc::home;
    }

    void resting::execute(human* e) {
        // std::cout << "Resting..." << std::endl;
        e->m_hunger += 5;
        e->m_thirst += 5;
        e->m_fatigue -= 25;
        e->m_loneliness += 5;

        if (!e->is_not_tired()) return;

        if (e->is_hungry() && e->m_money >= 20) {
            e->send_invite(message_type::go_eating, e->id());
            e->change_state(fsm_state::eating);
        }
        else if (e->is_thirsty() && e->m_money >= 15) {
            e->send_invite(message_type::go_drinking, e->id());
            e->change_state(fsm_state::drinking);
        }
        else if (e->is_lonely() && e->m_money >= 30) {
            e->send_invite(message_type::go_partying, e->id());
            e->change_state(fsm_state::partying);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_eating)
            && !e->is_not_hungry() && e->m_money >= 20) {
            e->accept_invite(message_type::go_eating);
            e->change_state(fsm_state::eating);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_drinking)
            && !e->is_not_thirsty() && e->m_money >= 15) {
            e->accept_invite(message_type::go_drinking);
            e->change_state(fsm_state::drinking);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_partying)
            && !e->is_not_lonely() && e->m_money >= 30) {
            e->accept_invite(message_type::go_partying);
            e->change_state(fsm_state::partying);
        }
        else {
            auto new_state = decide_where_to_work(e);
            e->change_state(new_state);
        }
    }

    void resting::exit(human* e) {
        // std::cout << "Exiting resting state" << std::endl;
    }

    void working_at_construction::enter(human* e) {
        // std::cout << "Entering working state" << std::endl;
        e->m_fsm_state = fsm_state::working_at_construction;
        e->m_location = loc::construction;
    }

    void working_at_construction::execute(human* e) {
        // std::cout << "Working..." << std::endl;
        e->m_money += 17;
        e->m_hunger += 10;
        e->m_thirst += 5;
        e->m_fatigue += 20;
        e->m_loneliness += 5;

        if (e->is_hungry() && e->m_money >= 20) {
            e->send_invite(message_type::go_eating, e->id());
            e->change_state(fsm_state::eating);
        }
        else if (e->is_thirsty() && e->m_money >= 15) {
            e->send_invite(message_type::go_drinking, e->id());
            e->change_state(fsm_state::drinking);
        }
        else if (e->is_tired()) {
            e->change_state(fsm_state::resting);
        }
        else if (e->is_lonely() && e->m_money >= 30) {
            e->send_invite(message_type::go_partying, e->id());
            e->change_state(fsm_state::partying);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_eating)
            && !e->is_not_hungry() && e->m_money >= 20) {
            e->accept_invite(message_type::go_eating);
            e->change_state(fsm_state::eating);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_drinking)
            && !e->is_not_thirsty() && e->m_money >= 15) {
            e->accept_invite(message_type::go_drinking);
            e->change_state(fsm_state::drinking);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_partying)
            && !e->is_not_lonely() && e->m_money >= 30) {
            e->accept_invite(message_type::go_partying);
            e->change_state(fsm_state::partying);
        }
    }

    void working_at_construction::exit(human* e) {
        // std::cout << "Exiting working state" << std::endl;
    }

    void working_at_office::enter(human* e) {
        // std::cout << "Entering working state" << std::endl;
        e->m_fsm_state = fsm_state::working_at_office;
        e->m_location = loc::office;
    }

    void working_at_office::execute(human* e) {
        // std::cout << "Working..." << std::endl;
        e->m_money += 12;
        e->m_hunger += 5;
        e->m_thirst += 5;
        e->m_fatigue += 10;
        e->m_loneliness -= 5;

        if (e->is_hungry() && e->m_money >= 20) {
            e->send_invite(message_type::go_eating, e->id());
            e->change_state(fsm_state::eating);
        }
        else if (e->is_thirsty() && e->m_money >= 15) {
            e->send_invite(message_type::go_drinking, e->id());
            e->change_state(fsm_state::drinking);
        }
        else if (e->is_tired()) {
            e->change_state(fsm_state::resting);
        }
        else if (e->is_lonely() && e->m_money >= 30) {
            e->send_invite(message_type::go_partying, e->id());
            e->change_state(fsm_state::partying);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_eating)
            && !e->is_not_hungry() && e->m_money >= 20) {
            e->accept_invite(message_type::go_eating);
            e->change_state(fsm_state::eating);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_drinking)
            && !e->is_not_thirsty() && e->m_money >= 15) {
            e->accept_invite(message_type::go_drinking);
            e->change_state(fsm_state::drinking);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_partying)
            && !e->is_not_lonely() && e->m_money >= 30) {
            e->accept_invite(message_type::go_partying);
            e->change_state(fsm_state::partying);
        }
    }

    void working_at_office::exit(human* e) {
        // std::cout << "Exiting working state" << std::endl;
    }

    void eating::enter(human* e) {
        // std::cout << "Entering eating state" << std::endl;
        e->m_fsm_state = fsm_state::eating;
        e->m_location = loc::restaurant;
    }

    void eating::execute(human* e) {
        // std::cout << "Eating..." << std::endl;
        e->m_money -= 20;
        e->m_hunger -= 20;
        e->m_thirst -= 5;
        e->m_fatigue += 5;
        e->m_loneliness -= 5;

        if (!e->is_not_hungry() && e->m_money >= 20) return;

        if (e->is_thirsty() && e->m_money >= 15) {
            e->send_invite(message_type::go_drinking, e->id());
            e->change_state(fsm_state::drinking);
        }
        else if (e->is_tired()) {
            e->change_state(fsm_state::resting);
        }
        else if (e->is_lonely() && e->m_money >= 30) {
            e->send_invite(message_type::go_partying, e->id());
            e->change_state(fsm_state::partying);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_drinking)
            && !e->is_not_thirsty() && e->m_money >= 15) {
            e->accept_invite(message_type::go_drinking);
            e->change_state(fsm_state::drinking);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_partying)
            && !e->is_not_lonely() && e->m_money >= 30) {
            e->accept_invite(message_type::go_partying);
            e->change_state(fsm_state::partying);
        }
        else {
            auto new_state = decide_where_to_work(e);
            e->change_state(new_state);
        }
    }

    void eating::exit(human* e) {
        // std::cout << "Exiting eating state" << std::endl;
    }

    void drinking::enter(human* e) {
        // std::cout << "Entering drinking state" << std::endl;
        e->m_fsm_state = fsm_state::drinking;
        e->m_location = loc::bar;
    }

    void drinking::execute(human* e) {
        // std::cout << "Drinking..." << std::endl;
        e->m_money -= 15;
        e->m_hunger -= 5;
        e->m_thirst -= 20;
        e->m_fatigue += 5;
        e->m_loneliness -= 10;

        if (!e->is_not_thirsty() && e->m_money >= 15) return;

        if (e->is_hungry() && e->m_money >= 20) {
            e->send_invite(message_type::go_eating, e->id());
            e->change_state(fsm_state::eating);
        }
        else if (e->is_tired()) {
            e->change_state(fsm_state::resting);
        }
        else if (e->is_lonely() && e->m_money >= 30) {
            e->send_invite(message_type::go_partying, e->id());
            e->change_state(fsm_state::partying);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_eating)
            && !e->is_not_hungry() && e->m_money >= 20) {
            e->accept_invite(message_type::go_eating);
            e->change_state(fsm_state::eating);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_partying)
            && !e->is_not_lonely() && e->m_money >= 30) {
            e->accept_invite(message_type::go_partying);
            e->change_state(fsm_state::partying);
        }
        else {
            auto new_state = decide_where_to_work(e);
            e->change_state(new_state);
        }
    }

    void drinking::exit(human* e) {
        // std::cout << "Exiting drinking state" << std::endl;
    }

    void partying::enter(human* e) {
        // std::cout << "Entering partying state" << std::endl;
        e->m_fsm_state = fsm_state::partying;
        e->m_location = loc::party;
    }

    void partying::execute(human* e) {
        // std::cout << "Partying..." << std::endl;
        e->m_money -= 30;
        e->m_hunger -= 10;
        e->m_thirst -= 20;
        e->m_fatigue += 20;
        e->m_loneliness -= 20;

        if (!e->is_not_lonely() && e->m_money >= 30) return;

        if (e->is_hungry() && e->m_money >= 20) {
            e->send_invite(message_type::go_eating, e->id());
            e->change_state(fsm_state::eating);
        }
        else if (e->is_thirsty() && e->m_money >= 15) {
            e->send_invite(message_type::go_drinking, e->id());
            e->change_state(fsm_state::drinking);
        }
        else if (e->is_tired()) {
            e->change_state(fsm_state::resting);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_eating)
            && !e->is_not_hungry() && e->m_money >= 20) {
            e->accept_invite(message_type::go_eating);
            e->change_state(fsm_state::eating);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_drinking)
            && !e->is_not_thirsty() && e->m_money >= 15) {
            e->accept_invite(message_type::go_drinking);
            e->change_state(fsm_state::drinking);
        }
        else {
            auto new_state = decide_where_to_work(e);
            e->change_state(new_state);
        }
    }

    void partying::exit(human* e) {
        // std::cout << "Exiting partying state" << std::endl;
    }

} // namespace core