#include "message.h"

#include "entity.h"

namespace core {

    bool inbox::has_messages() const {
        return !m_messages.empty();
    }

    inbox::const_iterator inbox::has_messages_of_type(message_type type) const {
        for (auto it = m_messages.begin(); it != m_messages.end(); ++it) {
            if (it->m_type == type) {
                return it;
            }
        }
    }

    inbox::iterator inbox::has_messages_of_type(message_type type) {
        for (auto it = m_messages.begin(); it != m_messages.end(); ++it) {
            if (it->m_type == type) {
                return it;
            }
        }
    }

    inbox::const_iterator inbox::has_messages_from(int id) const {
        for (auto it = m_messages.begin(); it != m_messages.end(); ++it) {
            if (it->m_sender_id == id) {
                return it;
            }
        }
    }

    inbox::iterator inbox::has_messages_from(int id) {
        for (auto it = m_messages.begin(); it != m_messages.end(); ++it) {
            if (it->m_sender_id == id) {
                return it;
            }
        }
    }

    void inbox::receive(message msg) {
        m_messages.push_back(msg);
    }

    void inbox::clear_messages() {
        m_messages.clear();
    }

    message_dispatcher* message_dispatcher::s_instance = nullptr;

    message_dispatcher::message_dispatcher() {
        s_instance = this;
    }

    void message_dispatcher::send_to(message_type type, int sender_id, int receiver_id, int delay) {
        // m_message_queue.emplace(type, sender_id, receiver_id, delay, 0);
        entity_manager::instance()->entities()[receiver_id]->inbox().receive({
            type,
            sender_id,
            receiver_id,
            delay
        });
    }

    void message_dispatcher::send_to_everyone(message_type type, int sender_id, int delay) {
        for (int receiver_id = 0; receiver_id < entity_manager::instance()->entities().size(); ++receiver_id) {
            if (receiver_id == sender_id) {
                continue;
            }

            entity_manager::instance()->entities()[receiver_id]->inbox().receive({
                type,
                sender_id,
                receiver_id,
                delay
            });
        }
    }

    //void message_dispatcher::update() {
    //    for (auto& m : m_message_queue) {
    //        m.m_waited++;
    //    }
    //
    //    while (!m_message_queue.empty()) {
    //        auto msg = m_message_queue.top();
    //        // if ((msg.m_delay - msg.m_waited) > 0) break;
    //
    //        entity_manager::instance()->entities()[msg.m_receiver_id]->inbox().receive(msg);
    //        m_message_queue.pop();
    //    }
    //}

} // namespace core