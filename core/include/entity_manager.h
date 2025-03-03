#pragma once

#include <vector>
#include <queue>
#include <memory>

#include "entity.h"

namespace core {

    /// @brief Manager class for handling all entities in the game.
    class entity_manager {
    private:
        static entity_manager* s_instance; ///< Singleton instance of the entity manager.

        std::vector<std::shared_ptr<entity>> m_entities; ///< List of all entities.

        std::queue<int> m_entities_to_remove; ///< Queue of entities to be removed.
        std::queue<std::shared_ptr<entity>> m_entities_to_add; ///< Queue of entities to be removed.

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
        template <typename entity_type>
        void add_entity();

        template <typename entity_type>
        void replace_entity(int id, unit_type type);
        
        void query_remove_entity(int id);

        /// @brief Update all entities managed by the entity manager.
        void update(int dt = 1);

    private:
        /// @brief Remove entities that are marked for removal.
        void remove_entities();
    };

    template <typename entity_type>
    inline void entity_manager::add_entity() {
        m_entities.push_back(std::make_shared<entity_type>(m_entities.size()));
    }

    template <typename entity_type>
    inline void entity_manager::replace_entity(int id, unit_type type) {
        auto entity = m_entities[id];
        query_remove_entity(id);
        m_entities_to_add.push(std::make_shared<entity_type>(id, entity->pos(), entity->get_tile(), type));
    }

} // namespace core