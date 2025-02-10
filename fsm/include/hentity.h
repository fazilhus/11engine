#pragma once

#include <memory>

#include "entity.h"
#include "need.h"
#include "enum.h"
#include "travel.h"

namespace core {

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
        uint8_t m_location; ///< Current location of the human.
        long long m_cycles; ///< Number of cycles the human has lived.

    private:
        std::shared_ptr<istate<human>> m_global_state; ///< A reference to a current global state of the human.
        std::shared_ptr<istate<human>> m_state; ///< A reference to a current state of the human.
        uint8_t m_curr_state; ///< Current state of the human
        uint8_t m_next_state; ///< Next state of the human.
        uint8_t m_prev_state; ///< Previous state of the human.

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
        uint8_t curr_state() const { return m_curr_state; }

        /// @brief Get the next state of the human.
        /// @return Next state of the human.
        uint8_t next_state() const { return m_next_state; }

        /// @brief Get the previous state of the human.
        /// @return Previous state of the human.
        uint8_t prev_state() const { return m_prev_state; }

        /// @brief Set the current state of the human.
        /// @param state Current state of the human.
        void set_curr_state(uint8_t state) { m_curr_state = state; }

        /// @brief Set the next state of the human.
        /// @param state Next state of the human.
        void set_next_state(uint8_t state) { m_next_state = state; }

        /// @brief Set the previous state of the human.
        /// @param state Previous state of the human.
        void set_prev_state(uint8_t state) { m_prev_state = state; }

        const travel_data& travel() const { return m_travel; }
        travel_data& travel() { return m_travel; }

        /// @brief Check if the human is dead.
        /// @return True if the human is dead, false otherwise.
        bool is_dead() const override {
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