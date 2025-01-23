#include "state.h"

#include "entity.h"
#include "message.h"

namespace core {

    void resting::enter(human* e) {
        std::cout << e->name() << " is Entering resting state" << std::endl;
        e->m_fsm_state = fsm_state::resting;
        e->m_location = loc::home;
    }

    void resting::execute(human* e) {
        std::cout << e->name() << " is Resting..." << std::endl;
        e->m_hunger += 5;
        e->m_thirst += 5;
        e->m_fatigue -= 25;
        e->m_loneliness += 5;
    }

    void resting::make_decision(human* e) {
        if (!e->is_not_tired()) {
            return;
        }

        if (e->should_eat()) {
            e->send_invite(message_type::go_eating, e->id());
            e->set_next_state(fsm_state::eating);
        }
        else if (e->should_drink()) {
            e->send_invite(message_type::go_drinking, e->id());
            e->set_next_state(fsm_state::drinking);
        }
        else if (e->should_party()) {
            e->send_invite(message_type::go_partying, e->id());
            e->set_next_state(fsm_state::partying);
        }
        else {
            e->set_next_state(e->decide_where_to_work());
        }
    }

    void resting::process_messages(human* e) {
        if (!e->inbox().has_messages()) {
            return;
        }

        if (e->inbox().has_messages_of_type(message_type::go_eating)
            && e->could_eat()) {
            e->accept_invite(message_type::go_eating);
            e->set_next_state(fsm_state::eating);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_drinking)
            && e->could_drink()) {
            e->accept_invite(message_type::go_drinking);
            e->set_next_state(fsm_state::drinking);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_partying)
            && e->could_party()) {
            e->accept_invite(message_type::go_partying);
            e->set_next_state(fsm_state::partying);
        }
    }

    void resting::maybe_change_state(human *e) {
        if (e->next_state() != fsm_state::none) {
            e->change_state();
        }
    }

    void resting::exit(human* e) {
        std::cout << e->name() << " is Exiting resting state" << std::endl;
    }

    void working_at_construction::enter(human* e) {
        std::cout << e->name() << " is Entering working state" << std::endl;
        e->m_fsm_state = fsm_state::working_at_construction;
        e->m_location = loc::construction;
    }

    void working_at_construction::execute(human* e) {
        std::cout << e->name() << " is Working..." << std::endl;
        e->m_money += 17;
        e->m_hunger += 10;
        e->m_thirst += 5;
        e->m_fatigue += 20;
        e->m_loneliness += 5;
    }

    void working_at_construction::make_decision(human* e) {
        if (e->should_eat()) {
            e->send_invite(message_type::go_eating, e->id());
            e->set_next_state(fsm_state::eating);
        }
        else if (e->should_drink()) {
            e->send_invite(message_type::go_drinking, e->id());
            e->set_next_state(fsm_state::drinking);
        }
        else if (e->is_tired()) {
            e->set_next_state(fsm_state::resting);
        }
        else if (e->should_party()) {
            e->send_invite(message_type::go_partying, e->id());
            e->set_next_state(fsm_state::partying);
        }
    }

    void working_at_construction::process_messages(human* e) {
        if (!e->inbox().has_messages()) {
            return;
        }

        if (e->inbox().has_messages_of_type(message_type::go_eating)
            && e->could_eat()) {
            e->accept_invite(message_type::go_eating);
            e->set_next_state(fsm_state::eating);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_drinking)
            && e->could_drink()) {
            e->accept_invite(message_type::go_drinking);
            e->set_next_state(fsm_state::drinking);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_partying)
            && e->could_party()) {
            e->accept_invite(message_type::go_partying);
            e->set_next_state(fsm_state::partying);
        }
    }

    void working_at_construction::maybe_change_state(human *e) {
        if (e->next_state() != fsm_state::none) {
            e->change_state();
        }
    }

    void working_at_construction::exit(human* e) {
        std::cout << e->name() << " is Exiting working state" << std::endl;
    }

    void working_at_office::enter(human* e) {
        std::cout << e->name() << " is Entering working state" << std::endl;
        e->m_fsm_state = fsm_state::working_at_office;
        e->m_location = loc::office;
    }

    void working_at_office::execute(human* e) {
        std::cout << e->name() << " is Working..." << std::endl;
        e->m_money += 12;
        e->m_hunger += 5;
        e->m_thirst += 5;
        e->m_fatigue += 10;
        e->m_loneliness -= 5;
    }

    void working_at_office::make_decision(human* e) {
        if (e->should_eat()) {
            e->send_invite(message_type::go_eating, e->id());
            e->set_next_state(fsm_state::eating);
        }
        else if (e->should_drink()) {
            e->send_invite(message_type::go_drinking, e->id());
            e->set_next_state(fsm_state::drinking);
        }
        else if (e->is_tired()) {
            e->set_next_state(fsm_state::resting);
        }
        else if (e->should_party()) {
            e->send_invite(message_type::go_partying, e->id());
            e->set_next_state(fsm_state::partying);
        }
    }

    void working_at_office::process_messages(human* e) {
        if (!e->inbox().has_messages()) {
            return;
        }

        if (e->inbox().has_messages_of_type(message_type::go_eating)
            && e->could_eat()) {
            e->accept_invite(message_type::go_eating);
            e->set_next_state(fsm_state::eating);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_drinking)
            && e->could_drink()) {
            e->accept_invite(message_type::go_drinking);
            e->set_next_state(fsm_state::drinking);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_partying)
            && e->could_party()) {
            e->accept_invite(message_type::go_partying);
            e->set_next_state(fsm_state::partying);
        }
    }

    void working_at_office::maybe_change_state(human *e) {
        if (e->next_state() != fsm_state::none) {
            e->change_state();
        }
    }

    void working_at_office::exit(human* e) {
        std::cout << e->name() << " is Exiting working state" << std::endl;
    }

    void eating::enter(human* e) {
        std::cout << e->name() << " is Entering eating state" << std::endl;
        e->m_fsm_state = fsm_state::eating;
        e->m_location = loc::restaurant;
    }

    void eating::execute(human* e) {
        std::cout << e->name() << " is Eating..." << std::endl;
        e->m_money -= 20;
        e->m_hunger -= 20;
        e->m_thirst -= 5;
        e->m_fatigue += 5;
        e->m_loneliness -= 5;
    }

    void eating::make_decision(human* e) {
        if (e->should_continue_eat()) {
            return;
        }

        if (e->should_drink()) {
            e->send_invite(message_type::go_drinking, e->id());
            e->set_next_state(fsm_state::drinking);
        }
        else if (e->is_tired()) {
            e->set_next_state(fsm_state::resting);
        }
        else if (e->should_party()) {
            e->send_invite(message_type::go_partying, e->id());
            e->set_next_state(fsm_state::partying);
        }
        else {
            e->set_next_state(e->decide_where_to_work());
        }
    }

    void eating::process_messages(human* e) {
        if (!e->inbox().has_messages()) {
            return;
        }

        if (e->inbox().has_messages_of_type(message_type::go_drinking)
            && e->could_drink()) {
            e->accept_invite(message_type::go_drinking);
            e->set_next_state(fsm_state::drinking);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_partying)
            && e->could_party()) {
            e->accept_invite(message_type::go_partying);
            e->set_next_state(fsm_state::partying);
        }
    }

    void eating::maybe_change_state(human *e) {
        if (e->next_state() != fsm_state::none) {
            e->change_state();
        }
    }

    void eating::exit(human* e) {
        std::cout << e->name() << " is Exiting eating state" << std::endl;
    }

    void drinking::enter(human* e) {
        std::cout << e->name() << " is Entering drinking state" << std::endl;
        e->m_fsm_state = fsm_state::drinking;
        e->m_location = loc::bar;
    }

    void drinking::execute(human* e) {
        std::cout << e->name() << " is Drinking..." << std::endl;
        e->m_money -= 15;
        e->m_hunger -= 5;
        e->m_thirst -= 20;
        e->m_fatigue += 5;
        e->m_loneliness -= 10; 
    }

    void drinking::make_decision(human* e) {
        if (e->should_continue_drink()) {
            return;
        }

        if (e->should_eat()) {
            e->send_invite(message_type::go_eating, e->id());
            e->set_next_state(fsm_state::eating);
        }
        else if (e->is_tired()) {
            e->set_next_state(fsm_state::resting);
        }
        else if (e->should_party()) {
            e->send_invite(message_type::go_partying, e->id());
            e->set_next_state(fsm_state::partying);
        }
        else {
            e->set_next_state(e->decide_where_to_work());
        }
    }

    void drinking::process_messages(human* e) {
        if (!e->inbox().has_messages()) {
            return;
        }

        if (e->inbox().has_messages_of_type(message_type::go_eating)
            && e->could_eat()) {
            e->accept_invite(message_type::go_eating);
            e->set_next_state(fsm_state::eating);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_partying)
            && e->could_party()) {
            e->accept_invite(message_type::go_partying);
            e->set_next_state(fsm_state::partying);
        }
    }

    void drinking::maybe_change_state(human *e) {
        if (e->next_state() != fsm_state::none) {
            e->change_state();
        }
    }

    void drinking::exit(human* e) {
        std::cout << e->name() << " is Exiting drinking state" << std::endl;
    }

    void partying::enter(human* e) {
        std::cout << e->name() << " is Entering partying state" << std::endl;
        e->m_fsm_state = fsm_state::partying;
        e->m_location = loc::party;
    }

    void partying::execute(human* e) {
        std::cout << e->name() << " is Partying..." << std::endl;
        e->m_money -= 30;
        e->m_hunger -= 10;
        e->m_thirst -= 20;
        e->m_fatigue += 20;
        e->m_loneliness -= 20;
    }

    void partying::make_decision(human* e) {
        if (e->should_continue_party()) {
            return;
        }

        if (e->should_eat()) {
            e->send_invite(message_type::go_eating, e->id());
            e->set_next_state(fsm_state::eating);
        }
        else if (e->should_drink()) {
            e->send_invite(message_type::go_drinking, e->id());
            e->set_next_state(fsm_state::drinking);
        }
        else if (e->is_tired()) {
            e->set_next_state(fsm_state::resting);
        }
        else {
            e->set_next_state(e->decide_where_to_work());
        }
    }

    void partying::process_messages(human* e) {
        if (!e->inbox().has_messages()) {
            return;
        }

        if (e->inbox().has_messages_of_type(message_type::go_eating)
            && e->could_eat()) {
            e->accept_invite(message_type::go_eating);
            e->set_next_state(fsm_state::eating);
        }
        else if (e->inbox().has_messages_of_type(message_type::go_drinking)
            && e->could_drink()) {
            e->accept_invite(message_type::go_drinking);
            e->set_next_state(fsm_state::drinking);
        }
    }

    void partying::maybe_change_state(human *e) {
        if (e->next_state() != fsm_state::none) {
            e->change_state();
        }
    }

    void partying::exit(human* e) {
        std::cout << e->name() << " is Exiting partying state" << std::endl;
    }

} // namespace core