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

        if (!m_entities_to_add.empty()) {
            add_entities();
        }

        for (auto& e : m_entities) {
            e->update(dt);
        }
    }

    void entity_manager::add_entities() {
        while (!m_entities_to_add.empty()) {
            auto i = m_entities.size();
            m_entities.push_back(m_entities_to_add.front());
            m_entities.back()->set_id(i);
            m_entities_to_add.pop();
        }
    }

    void entity_manager::remove_entities() {
        while (!m_entities_to_remove.empty()) {
            auto idx = m_entities_to_remove.top();
            m_entities_to_remove.pop();

            assert(idx >= 0 && idx < m_entities.size());
            m_entities.erase(m_entities.begin() + idx);
        }

        for (int i = 0; i < m_entities.size(); ++i) {
            m_entities[i]->set_id(i);
        }
    }

} // namespace core