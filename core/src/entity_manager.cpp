#include "entity_manager.h"

namespace core {

    entity_manager* entity_manager::s_instance = nullptr;

    entity_manager::entity_manager() {
        s_instance = this;
    }

    void entity_manager::add_entity(std::shared_ptr<entity> entity) {
        m_entities.push_back(std::move(entity));
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
    }

} // namespace core