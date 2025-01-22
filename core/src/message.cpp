#include "message.h"

#include "entity.h"

namespace core {

    bool inbox::has_messages() const {
        return !m_messages.empty();
    }

    bool inbox::has_messages_of_type(message_type type) const {
        return m_messages.find(type) != m_messages.end();
    }

    void inbox::receive(message msg) {
        m_messages.insert({msg.m_type, msg});
    }

    void inbox::clear_messages() {
        m_messages.clear();
    }

    message_sender* message_sender::s_instance = nullptr;

    message_sender::message_sender() {
        s_instance = this;
    }

    void message_sender::send_to_everyone(message_type type, int sender_id) {
        for (int i = 0; i < entity_manager::instance()->entities().size(); ++i) {
            if (i == sender_id) {
                continue;
            }

            message msg;
            msg.m_type = type;
            msg.m_sender_id = sender_id;
            msg.m_receiver_id = i;

            entity_manager::instance()->entities()[i]->inbox().receive(msg);
        }
    }

} // namespace core