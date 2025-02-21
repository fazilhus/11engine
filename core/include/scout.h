#pragma once

#include <memory>

#include "entity.h"
#include "map.h"

namespace core {

    template <typename entity_type>
    class istate;

    class scout : public entity {
    public:
        using state_type = std::shared_ptr<istate<scout>>;
        using wstate_type = std::weak_ptr<istate<scout>>;

    private:
        state_type m_state;
        path m_path;

    public:
        scout(int id, const std::string& name);
        ~scout() override;

        void update(int dt = 1) override;

        void change_state() override;

        wstate_type state() { return m_state; }
        path& path() { return m_path; }
    };

} // namespace core