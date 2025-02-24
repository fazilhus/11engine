#pragma once

#include <memory>

#include "entity.h"
#include "map.h"

namespace core {

    template <typename entity_type>
    class istate;

    class worker : public entity {
    public:
        using state_type = std::unique_ptr<istate<worker>>;

    private:
        state_type m_state;
        worker_state_type m_cur_state;
        worker_state_type m_next_state;
        path m_path;

    public:
        worker(int id, const std::string& name);
        ~worker() override;

        void update(int dt = 1) override;

        void change_state() override;

        worker_state_type state() const { return m_cur_state; }
        void set_state(worker_state_type state) { m_cur_state = state; }
        worker_state_type next_state() const { return m_next_state; }
        void set_next_state(worker_state_type state) { m_next_state = state; }

        path& path() { return m_path; }
    };

} // namespace core