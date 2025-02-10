#pragma once

#include <iostream>

namespace core {

    /// @brief pure virtual base 'state' class
    /// @tparam entity_type entity
    template <typename entity_type>
    class istate {
    public:
        virtual ~istate() {}

        /// @brief handles entering into a state
        /// @param e entity entering the state
        virtual void enter(entity_type* e) = 0;

        /// @brief executes the state's behavior
        /// @param e entity executing the state
        virtual void execute(entity_type* e) = 0;

        /// @brief makes decisions based on the entity's current state
        /// @param e entity making the decision
        virtual void make_decision(entity_type* e) = 0;

        /// @brief processes messages received by the entity
        /// @param e entity processing the messages
        virtual void process_messages(entity_type* e) = 0;

        /// @brief checks if the entity should change state
        /// @param e entity checking for state change
        virtual void change_state(entity_type* e) = 0;

        /// @brief handles exiting from a state
        /// @param e entity exiting the state
        virtual void exit(entity_type* e) = 0;
    };

} // namespace core