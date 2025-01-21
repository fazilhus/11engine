#pragma once

#include "stat.h"

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

    private:
        state* m_current_state;

    public:
        human(int id);
        ~human() override;

        void update() override;

        void change_state(state* new_state);
    };

} // namespace core