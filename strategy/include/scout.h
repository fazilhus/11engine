#pragma once

#include <memory>

#include "entity.h"
#include "travel.h"

namespace core {

    template <typename entity_type>
    class istate;

    class scout : public entity {
    public:
        using state_type = std::shared_ptr<istate<scout>>;
        using wstate_type = std::weak_ptr<istate<scout>>;
        using link_type = link;
    private:
        state_type m_state;
        link_type m_link;

    public:
        scout(int id, const std::string& name);
        ~scout() override;

        void update(int dt = 1) override;

        void change_state() override;

        wstate_type state() { return m_state; }
        link_type link() { return m_link; }
    };

} // namespace core