#include "entity.h"

#include <cassert>

#include "state.h"
#include "fsm.h"

namespace core {

    entity::entity(int id)
        : m_id(id) {
        set_id(id);
    }

    entity::~entity() {
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
            e->update();

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
            m_fsm_state = fsm_state::resting;
            m_location = loc::home;
            m_current_state = fsm::instance()->get_state(m_fsm_state);
            m_money = stat(util::random_int(25, 60), 0, 100, 200, 1000);
            m_hunger = stat(util::random_int(10, 35), 0, 35, 65, 100);
            m_thirst = stat(util::random_int(10, 35), 0, 35, 65, 100);
            m_fatigue = stat(util::random_int(10, 35), 0, 40, 60, 100);
            m_loneliness = stat(util::random_int(10, 35), 0, 25, 75, 100);
            m_cycles = 0;
    }

    human::~human() {
    }

    void human::update() {
        m_cycles++;
        if (m_current_state) {
            m_current_state->execute(this);
        }
    }

    void human::change_state(fsm_state new_state) {
        if (m_fsm_state == new_state) {
            return;
        }

        m_current_state->exit(this);
        m_current_state = fsm::instance()->get_state(new_state);
        m_current_state->enter(this);
    }

} // namespace core