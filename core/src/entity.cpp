#include "entity.h"

#include <cassert>

#include "state.h"
#include "state_provider.h"
#include "message.h"
#include "util.h"

namespace core {

    entity::entity(int id, const std::string& name)
        : m_id(id), m_name(name) {
    }

    entity::~entity() {
    }

    void entity::accept_invite(message_type type) {
        std::cout << m_name << " accepted invite to " << util::str(type) << std::endl;
        m_inbox.messages().erase(type);
    }

    void entity::send_invite(message_type type, int sender_id) {
        std::cout << m_name << " sent invite to " << util::str(type) << std::endl;
        message_sender::instance()->send_to_everyone(type, sender_id);
    }

    entity_manager* entity_manager::s_instance = nullptr;

    entity_manager::entity_manager() {
        s_instance = this;
    }

    void entity_manager::add_entity(std::unique_ptr<entity> entity) {
        m_entities.push_back(std::move(entity));
    }

    void entity_manager::update() {
        if (!m_entities_to_remove.empty()) {
            remove_entities();
        }

        int i = 0;
        for (auto& e : m_entities) {
            e->update_stage1();
            i++;
        }

        i = 0;
        for (auto& e : m_entities) {
            e->update_stage2();

            auto h = dynamic_cast<human*>(e.get());
            if (!h) continue;

            if (h->is_dead()) {
                std::cout << "Human " << h->name() << " is dead :(" << std::endl;
				std::cout << "Human lived for " << h->m_cycles << " cycles" << std::endl;
				std::cout << "Wealth: " << h->m_money.str() << std::endl;
				std::cout << "Hunger: " << h->m_hunger.str() << std::endl;
				std::cout << "Thirst: " << h->m_thirst.str() << std::endl;
				std::cout << "Fatigue: " << h->m_fatigue.str() << std::endl;
				std::cout << "Loneliness: " << h->m_loneliness.str() << std::endl;
                m_entities_to_remove.push(i);
            }

            i++;
        }
    }

    void entity_manager::remove_entities() {
        do {
            auto idx = m_entities_to_remove.top();
            m_entities_to_remove.pop();

            assert(idx >= 0 && idx < m_entities.size());
            m_entities.erase(m_entities.begin() + idx);

            for (int i = 0; i < m_entities.size(); ++i) {
                m_entities[i]->set_id(i);
            }
        }
        while (!m_entities_to_remove.empty());
    }

    human::human(int id, const std::string& name)
        : entity(id, name) {
            m_location = loc_type::home;
            m_state = state_provider::instance()->get_state();
            m_curr_state = state_type::resting;
            m_next_state = state_type::none;
            m_prev_state = state_type::none;
            m_money = need(util::random_int(25, 60), 0, 100, 200, 1000);
            m_hunger = need(util::random_int(10, 35), 0, 35, 65, 100);
            m_thirst = need(util::random_int(10, 35), 0, 35, 65, 100);
            m_fatigue = need(util::random_int(10, 35), 0, 20, 60, 100);
            m_loneliness = need(util::random_int(10, 35), 0, 25, 75, 100);
            m_chance = util::random_float(0.33f, 0.66f);
            m_cycles = 0;
    }

    human::~human() {
    }

    void human::update_stage1() {
        m_cycles++;
        if (m_state) {
            m_state->execute(this);
            m_state->make_decision(this);
        }
    }

    void human::update_stage2() {
        if (m_state) {
            m_state->process_messages(this);
            m_state->change_state(this);
        }
        m_inbox.clear_messages();
    }

    void human::change_state() {
        if (m_curr_state == m_next_state || m_next_state == state_type::none) {
            return;
        }

        m_prev_state = m_curr_state;
        m_state->exit(this);
        m_curr_state = m_next_state;
        // m_state = state_provider::instance()->get_state();
        m_state->enter(this);
        m_next_state = state_type::none;
    }

} // namespace core