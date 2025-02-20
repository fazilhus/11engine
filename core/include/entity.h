#pragma once

#include <memory>
#include <vector>
#include <queue>

#include "message.h"

namespace core {

    class inbox;

    /// @brief Base class for all entities in the game.
    class entity {
    protected:
        int m_id; ///< Unique identifier for the entity.
        std::string m_name; ///< Name of the entity.
        inbox m_inbox; ///< Inbox for receiving messages.

    public:
        /// @brief Constructor for the entity class.
        /// @param id Unique identifier for the entity.
        /// @param name Name of the entity.
        entity(int id, const std::string& name);

        /// @brief Virtual destructor for the entity class.
        virtual ~entity();

        /// @brief Update the entity in the first stage.
        virtual void update() = 0;

        /// @brief Get the unique identifier of the entity.
        /// @return Unique identifier of the entity.
        int id() const { return m_id; }

        /// @brief Set the unique identifier of the entity.
        /// @param id Unique identifier of the entity.
        void set_id(int id) { m_id = id; }

        /// @brief Get the name of the entity.
        /// @return Name of the entity.
        const std::string& name() const { return m_name; }

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

    /// @brief Manager class for handling all entities in the game.
    class entity_manager {
    private:
        static entity_manager* s_instance; ///< Singleton instance of the entity manager.

        std::vector<std::unique_ptr<entity>> m_entities; ///< List of all entities.

        std::queue<int> m_entities_to_remove; ///< Queue of entities to be removed.

    public:
        /// @brief Constructor for the entity manager class.
        entity_manager();

        /// @brief Destructor for the entity manager class.
        ~entity_manager() = default;

        /// @brief Get the singleton instance of the entity manager.
        /// @return Singleton instance of the entity manager.
        static entity_manager* get() { return s_instance; }

        /// @brief Get the list of all entities.
        /// @return List of all entities.
        const std::vector<std::unique_ptr<entity>>& entities() const { return m_entities; }

        /// @brief Add a new entity to the manager.
        /// @param entity Unique pointer to the new entity.
        void add_entity(std::unique_ptr<entity> entity);

        /// @brief Update all entities managed by the entity manager.
        void update();

    private:
        /// @brief Remove entities that are marked for removal.
        void remove_entities();
    };

} // namespace core