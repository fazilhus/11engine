#pragma once

#include <memory>

#include "stat.h"
#include "util.h"

namespace core {

    class entity {
    private:
        int m_id;

    public:
        entity(int id);
        virtual ~entity();

        virtual void update() = 0;

        int id() const { return m_id; }

    private:
        void set_id(int id) { m_id = id; }
    };

    class state;

    class human : public entity {
    public:
        stat m_money;
        stat m_hunger;
        stat m_thirst;
        stat m_fatigue;
        stat m_loneliness;
        fsm_state m_fsm_state;
        loc m_location;
        int m_cycles;

    private:
        std::shared_ptr<state> m_current_state;

    public:
        human(int id);
        ~human() override;

        void update() override;

        void change_state(fsm_state new_state);

        bool is_dead() const {
            return m_hunger.value() == 100 || m_thirst.value() == 100 || m_fatigue.value() == 100 || m_loneliness.value() == 100;
        }
    };

} // namespace core