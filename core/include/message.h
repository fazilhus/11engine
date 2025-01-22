#pragma once

#include <map>

#include "util.h"

namespace core {

    struct message {
        message_type m_type;
        int m_sender_id;
        int m_receiver_id;
    };

    class inbox {
    private:
        std::multimap<message_type, message> m_messages;

    public:
        inbox() = default;
        ~inbox() = default;

        bool has_messages() const;
        bool has_messages_of_type(message_type type) const;

        void receive(message msg);
        void clear_messages();

        const std::multimap<message_type, message>& messages() const { return m_messages; }
        std::multimap<message_type, message>& messages() { return m_messages; }
    };

    class message_sender {
    private:
        static message_sender* s_instance;

    public:
        message_sender();
        ~message_sender() = default;

        static message_sender* instance() { return s_instance; }

        void send_to_everyone(message_type type, int sender_id);
    };

} // namespace core