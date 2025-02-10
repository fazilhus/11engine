#pragma once

#include <vector>

#include "pqueue.h"
#include "util.h"

namespace core {

    /// @brief Struct representing a message.
    struct message {
        message_type m_type; ///< Type of the message.
        int m_sender_id; ///< ID of the sender.
        int m_receiver_id; ///< ID of the receiver.
        int m_timestamp; ///< some time on the future
        int m_delay; ///< delay of the message
        int m_waited;
    };

    struct message_cmp {
       bool operator()(const message& a, const message& b) const {
           return a.m_delay < b.m_delay;
       }
    };

    /// @brief Class representing an inbox for receiving messages.
    class inbox {
    public:
        using iterator = std::vector<message>::iterator;
        using const_iterator = std::vector<message>::const_iterator;
    private:
        std::vector<message> m_messages; ///< Multimap of messages.

    public:
        /// @brief Default constructor for the inbox class.
        inbox() = default;

        /// @brief Default destructor for the inbox class.
        ~inbox() = default;

        /// @brief Check if the inbox has any messages.
        /// @return True if the inbox has messages, false otherwise.
        bool has_messages() const;

        /// @brief Check if the inbox has messages of a specific type.
        /// @param type Type of the messages to check for.
        /// @return const_iterator
        const_iterator has_messages_of_type(message_type type) const;

        /// @brief Check if the inbox has messages of a specific type.
        /// @param type Type of the messages to check for.
        /// @return iterator
        iterator has_messages_of_type(message_type type);

        /// @brief Check if the inbox has messages of a specific type.
        /// @param id Sender of the messages to check for.
        /// @return const_iterator
        const_iterator has_messages_from(int id) const;

        /// @brief Check if the inbox has messages of a specific type.
        /// @param id Sender of the messages to check for.
        /// @return iterator
        iterator has_messages_from(int id);

        /// @brief Receive a message and add it to the inbox.
        /// @param msg The message to receive.
        void receive(message msg);

        /// @brief Clear all messages from the inbox.
        void clear_messages();

        /// @brief Get the multimap of messages.
        /// @return Const reference to the multimap of messages.
        const std::vector<message>& messages() const { return m_messages; }

        /// @brief Get the multimap of messages.
        /// @return Reference to the multimap of messages.
        std::vector<message>& messages() { return m_messages; }
    };

    /// @brief Class for sending messages to entities.
    class message_dispatcher {
    private:
        static message_dispatcher* s_instance; ///< Singleton instance of the message sender.

        container::pqueue<message, message_cmp> m_message_queue;

    public:
        /// @brief Constructor for the message sender class.
        message_dispatcher();

        /// @brief Default destructor for the message sender class.
        ~message_dispatcher() = default;

        /// @brief Get the singleton instance of the message sender.
        /// @return Singleton instance of the message sender.
        static message_dispatcher* instance() { return s_instance; }

        /// @brief Send a message to all entities.
        /// @param type Type of the message to send.
        /// @param sender_id ID of the sender.
        /// @param receiver ID of the receiver
        void send_to(message_type type, int sender_id, int receiver_id, int timestamp, int delay = 0);

        /// @brief Send a message to all entities.
        /// @param type Type of the message to send.
        /// @param sender_id ID of the sender.
        void send_to_everyone(message_type type, int sender_id, int timestamp, int delay = 0);

        void update();
    };

} // namespace core