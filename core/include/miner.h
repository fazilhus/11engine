#pragma once

#include <memory>

#include "entity.h"
#include "state_machine.h"

namespace core {

    class miner;

    template<>
    struct state_machine_traits<miner_state_type> {
        enum { size = miner_state_num };
    };

    class miner_state_machine : public state_machine<miner, miner_state_type> {
    public:
        miner_state_machine(miner* ptr);
        ~miner_state_machine() override = default;

        void update(int dt = 1) override;
    
    protected:
        void change_state() override;
    };

    class miner : public entity {
    private:
        miner_state_machine m_sm;

    public:
        miner(int id, std::array<int, 2> pos, std::weak_ptr<tile> tile, unit_type type);
        ~miner() override = default;

        void update(int dt = 1) override;

        miner_state_machine& sm() { return m_sm; }
    };

} // namespace core