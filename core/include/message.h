#pragma once

#include <map>

#include "util.h"

namespace core {

    /// @brief Struct representing a message.
    struct message {
        message_type m_type; ///< Type of the message.
        int m_sender_id; ///< ID of the sender.
        int m_receiver_id; ///< ID of the receiver.
    };

    /// @brief Class representing an inbox for receiving messages.
    class inbox {
    private:
        std::multimap<message_type, message> m_messages; ///< Multimap of messages.

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
        /// @return True if the inbox has messages of the specified type, false otherwise.
        bool has_messages_of_type(message_type type) const;

        /// @brief Receive a message and add it to the inbox.
        /// @param msg The message to receive.
        void receive(message msg);

        /// @brief Clear all messages from the inbox.
        void clear_messages();

        /// @brief Get the multimap of messages.
        /// @return Const reference to the multimap of messages.
        const std::multimap<message_type, message>& messages() const { return m_messages; }

        /// @brief Get the multimap of messages.
        /// @return Reference to the multimap of messages.
        std::multimap<message_type, message>& messages() { return m_messages; }
    };

    /// @brief Class for sending messages to entities.
    class message_sender {
    private:
        static message_sender* s_instance; ///< Singleton instance of the message sender.

    public:
        /// @brief Constructor for the message sender class.
        message_sender();

        /// @brief Default destructor for the message sender class.
        ~message_sender() = default;

        /// @brief Get the singleton instance of the message sender.
        /// @return Singleton instance of the message sender.
        static message_sender* instance() { return s_instance; }

        /// @brief Send a message to all entities.
        /// @param type Type of the message to send.
        /// @param sender_id ID of the sender.
        void send_to_everyone(message_type type, int sender_id);
    };

} // namespace core