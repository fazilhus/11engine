#pragma once

#include <memory>

#include "entity.h"
#include "state_machine.h"

namespace core {

    class scout;

    template<>
    struct state_machine_traits<scout_state_type> {
        enum { size = scout_state_num };
    };

    class scout_state_machine : public state_machine<scout, scout_state_type> {
    public:
        scout_state_machine(scout* ptr);
        ~scout_state_machine() override = default;

        void update(int dt = 1) override;
    
    protected:
        void change_state() override;
    };

    class scout : public entity {
    private:
        scout_state_machine m_sm;

    public:
        scout(int id, std::array<int, 2> pos, std::weak_ptr<tile> tile, unit_type type);
        ~scout() override = default;

        void update(int dt = 1) override;

        scout_state_machine& sm() { return m_sm; }
    };

} // namespace core