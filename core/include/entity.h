#pragma once

#include <memory>
#include <array>
#include <string>

#include "message.h"
#include "tile.h"
#include "map.h"

namespace core {

    class inbox;

    /// @brief Base class for all entities in the game.
    class entity {
    protected:
        int m_id; ///< Unique identifier for the entity.
        std::string m_name; ///< Name of the entity.
        inbox m_inbox; ///< Inbox for receiving messages.
        std::array<int, 2> m_pos;
        std::weak_ptr<tile> m_tile;
        int m_speed;

        path m_path;

    public:
        /// @brief Constructor for the entity class.
        /// @param id Unique identifier for the entity.
        /// @param name Name of the entity.
        entity(int id, const std::string& name);

        /// @brief Virtual destructor for the entity class.
        virtual ~entity();

        /// @brief Update the entity in the first stage.
        virtual void update(int dt = 1) = 0;

        /// @brief Get the unique identifier of the entity.
        /// @return Unique identifier of the entity.
        int id() const { return m_id; }

        /// @brief Set the unique identifier of the entity.
        /// @param id Unique identifier of the entity.
        void set_id(int id) { m_id = id; }

        /// @brief Get the name of the entity.
        /// @return Name of the entity.
        const std::string& name() const { return m_name; }

        std::array<int, 2> pos() const { return m_pos; }
        void set_pos(std::array<int, 2> p) { m_pos = p; }
        void update_pos(std::array<int, 2> dp) {
            m_pos[0] += dp[0];
            m_pos[1] += dp[1];
        }

        std::weak_ptr<tile> get_tile() const { return m_tile; }
        void set_tile(std::weak_ptr<tile> t) { m_tile = t; }

        int speed() const { return m_speed; }

        const path& get_path() const { return m_path; }
        path& get_path() { return m_path; }
        void set_path(const path& p) { m_path = p; }

        /// @brief Get the inbox of the entity.
        /// @return Inbox of the entity.
        inbox& inbox() { return m_inbox; }

        /// @brief Accept an invite of a specific type.
        /// @param type Type of the invite.
        void accept_invite(uint8_t msg_type);

        /// @brief Send an invite of a specific type.
        /// @param type Type of the invite.
        /// @param sender_id ID of the sender.
        /// @param delay a time in the future
        void send_invite(uint8_t msg_type, int sender_id, long long timestamp, int delay = 0);

        /// @brief Send an invite of a specific type.
        /// @param type Type of the invite.
        /// @param sender_id ID of the sender.
        /// @param receiver_id ID of the receiver
        /// @param delay a time in the future
        void send_invite(uint8_t msg_type, int sender_id, int receiver_id, long long timestamp, int delay = 0);
    };

} // namespace core