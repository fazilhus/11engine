#pragma once

#include <memory>

#include "entity.h"
#include "state_machine.h"

namespace core {

    class builder;

    template<>
    struct state_machine_traits<builder_state_type> {
        enum { size = builder_state_num };
    };

    class builder_state_machine : public state_machine<builder, builder_state_type> {
    public:
        builder_state_machine(builder* ptr);
        ~builder_state_machine() override = default;

        void update(int dt = 1) override;
    
    protected:
        void change_state() override;
    };

    class builder : public entity {
    private:
        builder_state_machine m_sm;

    public:
        builder(int id, std::array<int, 2> pos, std::weak_ptr<tile> tile, unit_type type);
        ~builder() override = default;

        void update(int dt = 1) override;

        builder_state_machine& sm() { return m_sm; }
    };

} // namespace core