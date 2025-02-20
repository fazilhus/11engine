#include "entity.h"

#include <cassert>
#include <iostream>

#include "message.h"
#include "util.h"

namespace core {

    entity::entity(int id, const std::string& name)
        : m_id(id), m_name(name) {
    }

    entity::~entity() {
    }

    void entity::accept_invite(uint8_t msg_type) {
        std::cout << m_name << " accepted invite to " << msg_type << std::endl;
    }

    void entity::send_invite(uint8_t msg_type, int sender_id, long long timestamp, int delay) {
        std::cout << m_name << " sent invite to " << msg_type << " in " << timestamp << std::endl;
        message_dispatcher::get()->send_to_everyone(msg_type, sender_id, timestamp, delay);
    }

    void entity::send_invite(uint8_t msg_type, int sender_id, int receiver_id, long long timestamp, int delay) {
        std::cout << m_name << " sent invite to " << msg_type << " in " << timestamp << " to " << receiver_id <<  std::endl;
        message_dispatcher::get()->send_to(msg_type, sender_id, receiver_id, timestamp, delay);
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

        for (auto& e : m_entities) {
            e->update();
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