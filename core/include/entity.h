#pragma once

#include <memory>
#include <vector>
#include <queue>

#include "need.h"
#include "util.h"
#include "message.h"
#include "travel.h"

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
        virtual void update_stage1() = 0;

        /// @brief Update the entity in the second stage.
        virtual void update_stage2() = 0;

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
        void accept_invite(message_type type);

        /// @brief Send an invite of a specific type.
        /// @param type Type of the invite.
        /// @param sender_id ID of the sender.
        /// @param delay a time in the future
        void send_invite(message_type type, int sender_id, int timestamp, int delay = 0);

        /// @brief Send an invite of a specific type.
        /// @param type Type of the invite.
        /// @param sender_id ID of the sender.
        /// @param receiver_id ID of the receiver
        /// @param delay a time in the future
        void send_invite(message_type type, int sender_id, int receiver_id, int timestamp, int delay = 0);
    };

    /// @brief Manager class for handling all entities in the game.
    class entity_manager {
    private:
        static entity_manager* s_instance; ///< Singleton instance of the entity manager.

        std::vector<std::unique_ptr<entity>> m_entities; ///< List of all entities.

        std::priority_queue<int> m_entities_to_remove; ///< Queue of entities to be removed.

    public:
        /// @brief Constructor for the entity manager class.
        entity_manager();

        /// @brief Destructor for the entity manager class.
        ~entity_manager() = default;

        /// @brief Get the singleton instance of the entity manager.
        /// @return Singleton instance of the entity manager.
        static entity_manager* instance() { return s_instance; }

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

    template <typename entity_type>
    class istate;

    /// @brief Class representing a human entity in the game.
    class human : public entity {
    public:
        need m_money; ///< Money need of the human.
        need m_hunger; ///< Hunger need of the human.
        need m_thirst; ///< Thirst need of the human.
        need m_fatigue; ///< Fatigue need of the human.
        need m_loneliness; ///< Loneliness need of the human.
        float m_chance; ///< Chance of accepting an invite.
        loc_type m_location; ///< Current location of the human.
        long long m_cycles; ///< Number of cycles the human has lived.

    private:
        std::shared_ptr<istate<human>> m_global_state; ///< A reference to a current global state of the human.
        std::shared_ptr<istate<human>> m_state; ///< A reference to a current state of the human.
        state_type m_curr_state; ///< Current state of the human
        state_type m_next_state; ///< Next state of the human.
        state_type m_prev_state; ///< Previous state of the human.

        travel_data m_travel; ///< travel data

    public:
        /// @brief Constructor for the human class.
        /// @param id Unique identifier for the human.
        /// @param name Name of the human.
        human(int id, const std::string& name);

        /// @brief Destructor for the human class.
        ~human() override;

        /// @brief Update the human in the first stage.
        void update_stage1() override;

        /// @brief Update the human in the second stage.
        void update_stage2() override;

        /// @brief Change the state of the human.
        void change_state();

        /// @brief Get the current state of the human.
        /// @return Current state of the human.
        state_type curr_state() const { return m_curr_state; }

        /// @brief Get the next state of the human.
        /// @return Next state of the human.
        state_type next_state() const { return m_next_state; }

        /// @brief Get the previous state of the human.
        /// @return Previous state of the human.
        state_type prev_state() const { return m_prev_state; }

        /// @brief Set the current state of the human.
        /// @param state Current state of the human.
        void set_curr_state(state_type state) { m_curr_state = state; }

        /// @brief Set the next state of the human.
        /// @param state Next state of the human.
        void set_next_state(state_type state) { m_next_state = state; }

        /// @brief Set the previous state of the human.
        /// @param state Previous state of the human.
        void set_prev_state(state_type state) { m_prev_state = state; }

        const travel_data& travel() const { return m_travel; }
        travel_data& travel() { return m_travel; }

        /// @brief Check if the human is dead.
        /// @return True if the human is dead, false otherwise.
        bool is_dead() const {
            return /*m_cycles >= 1000 ||*/ m_hunger.is_max() || m_thirst.is_max() || m_fatigue.is_max() || m_loneliness.is_max();
        }

        /// @brief Check if the human is wealthy.
        /// @return True if the human is wealthy, false otherwise.
        bool is_wealthy() const { return m_money.is_higher(); }

        /// @brief Check if the human is poor.
        /// @return True if the human is poor, false otherwise.
        bool is_poor() const { return m_money.is_lower(); }

        /// @brief Check if the human is hungry.
        /// @return True if the human is hungry, false otherwise.
        bool is_hungry() const { return m_hunger.is_higher(); }

        /// @brief Check if the human is not hungry.
        /// @return True if the human is not hungry, false otherwise.
        bool is_not_hungry() const { return m_hunger.is_lower(); }

        /// @brief Check if the human is thirsty.
        /// @return True if the human is thirsty, false otherwise.
        bool is_thirsty() const { return m_thirst.is_higher(); }

        /// @brief Check if the human is not thirsty.
        /// @return True if the human is not thirsty, false otherwise.
        bool is_not_thirsty() const { return m_thirst.is_lower(); }

        /// @brief Check if the human is tired.
        /// @return True if the human is tired, false otherwise.
        bool is_tired() const { return m_fatigue.is_higher(); }

        /// @brief Check if the human is not tired.
        /// @return True if the human is not tired, false otherwise.
        bool is_not_tired() const { return m_fatigue.is_lower(); }

        /// @brief Check if the human is lonely.
        /// @return True if the human is lonely, false otherwise.
        bool is_lonely() const { return m_loneliness.is_higher(); }

        /// @brief Check if the human is not lonely.
        /// @return True if the human is not lonely, false otherwise.
        bool is_not_lonely() const { return m_loneliness.is_lower(); }

        /// @brief Check if the human should eat.
        /// @return True if the human should eat, false otherwise.
        bool should_eat() const { return is_hungry() && m_money >= 20; }

        /// @brief Check if the human should continue eating.
        /// @return True if the human should continue eating, false otherwise.
        bool should_continue_eat() const { return !is_not_hungry() && m_money >= 20; }

        /// @brief Check if the human could eat.
        /// @return True if the human could eat, false otherwise.
        bool could_eat() const {
            return !is_thirsty() && !is_tired() && !is_lonely() && m_money >= 20 && want_accept_invite();
        }

        /// @brief Check if the human should drink.
        /// @return True if the human should drink, false otherwise.
        bool should_drink() const { return is_thirsty() && m_money >= 15; }

        /// @brief Check if the human should continue drinking.
        /// @return True if the human should continue drinking, false otherwise.
        bool should_continue_drink() const { return !is_not_thirsty() && m_money >= 15; }

        /// @brief Check if the human could drink.
        /// @return True if the human could drink, false otherwise.
        bool could_drink() const {
            return !is_hungry() && !is_tired() && !is_lonely() && m_money >= 15 && want_accept_invite();
        }

        /// @brief Check if the human should party.
        /// @return True if the human should party, false otherwise.
        bool should_party() const { return is_lonely() && m_money >= 30; }

        /// @brief Check if the human should continue partying.
        /// @return True if the human should continue partying, false otherwise.
        bool should_continue_party() const { return !is_not_lonely() && m_money >= 30; }

        /// @brief Check if the human could party.
        /// @return True if the human could party, false otherwise.
        bool could_party() const {
            return !is_hungry() && !is_thirsty() && !is_tired() && m_money >= 30 && want_accept_invite();
        }

        /// @brief Check if the human should shop.
        /// @return True if the human should shop, false otherwise.
        bool should_shop() const { return is_wealthy() && m_money >= 30; }

        /// @brief Check if the human should continue shopping.
        /// @return True if the human should continue shopping, false otherwise.
        bool should_continue_shop() const { return !is_poor() && m_money >= 30; }

        /// @brief Check if the human could go shopping.
        /// @return True if the human could go shopping, false otherwise.
        bool could_shop() const {
            return !is_hungry() && !is_thirsty() && !is_tired() && !is_lonely() && m_money >= 30 && want_accept_invite();
        }

    private:
        /// @brief Check if the human wants to accept an invite.
        /// @return True if the human wants to accept an invite, false otherwise.
        bool want_accept_invite() const { return util::random_float(0.0f, 1.0f) > m_chance; }

    };

} // namespace core