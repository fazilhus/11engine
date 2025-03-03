#include "entity_manager.h"

#include "scout.h"
#include "worker.h"

namespace core {

    entity_manager* entity_manager::s_instance = nullptr;

    entity_manager::entity_manager() {
        s_instance = this;
    }

    void entity_manager::query_remove_entity(int id) {
        m_entities_to_remove.push(id);
    }

    void entity_manager::update(int dt) {
        if (!m_entities_to_remove.empty()) {
            remove_entities();
        }

        for (auto& e : m_entities) {
            e->update(dt);
        }
    }

    void entity_manager::remove_entities() {
        while (!m_entities_to_remove.empty()) {
            auto idx = m_entities_to_remove.front();
            m_entities_to_remove.pop();

            assert(idx >= 0 && idx < m_entities.size());
            m_entities.erase(m_entities.begin() + idx);
        }

        for (int i = 0; i < m_entities.size(); ++i) {
            m_entities[i]->set_id(i);
        }

        while (!m_entities_to_add.empty()) {
            m_entities.push_back(m_entities_to_add.front());
            m_entities.back()->set_id(m_entities.size() - 1);
            m_entities_to_add.pop();
        }
    }

} // namespace core