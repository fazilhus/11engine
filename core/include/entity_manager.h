#pragma once

#include <vector>
#include <queue>
#include <memory>

#include "scout.h"
#include "worker.h"

namespace core {

    /// @brief Manager class for handling all entities in the game.
    class entity_manager {
    private:
        static entity_manager* s_instance; ///< Singleton instance of the entity manager.

        std::vector<std::shared_ptr<entity>> m_entities; ///< List of all entities.
        std::vector<std::weak_ptr<scout>> m_scouts;
        std::vector<std::weak_ptr<worker>> m_workers;

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
        const std::vector<std::shared_ptr<entity>>& entities() const { return m_entities; }

        /// @brief Add a new entity to the manager.
        /// @param entity Unique pointer to the new entity.
        void add_entity(std::shared_ptr<entity> entity);

        /// @brief Update all entities managed by the entity manager.
        void update(int dt = 1);

    private:
        /// @brief Remove entities that are marked for removal.
        void remove_entities();
    };

} // namespace core