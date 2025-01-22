#pragma once

#include <memory>
#include <vector>
#include <queue>

#include "stat.h"
#include "util.h"
#include "message.h"

namespace core {

    class inbox;

    class entity {
    protected:
        int m_id;
        std::string m_name;
        inbox m_inbox;

    public:
        entity(int id, const std::string& name);
        virtual ~entity();

        virtual void update() = 0;

        int id() const { return m_id; }
        void set_id(int id) { m_id = id; }

        const std::string& name() const { return m_name; }
        inbox& inbox() { return m_inbox; }
    };

    class entity_manager {
    private:
        static entity_manager* s_instance;

        std::vector<std::unique_ptr<entity>> m_entities;

        std::priority_queue<int> m_entities_to_remove;

    public:
        entity_manager();
        ~entity_manager() = default;

        static entity_manager* instance() { return s_instance; }

        const std::vector<std::unique_ptr<entity>>& entities() const { return m_entities; }

        void add_entity(std::unique_ptr<entity> entity);
        void update();

    private:
        void remove_entities();
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
        human(int id, const std::string& name);
        ~human() override;

        void update() override;

        void change_state(fsm_state new_state);

        bool is_dead() const {
            return m_cycles > 1000 || m_hunger.is_max() || m_thirst.is_max() || m_fatigue.is_max() || m_loneliness.is_max();
        }

        bool is_wealthy() const { return m_money.is_higher(); }
        bool is_poor() const { return m_money.is_lower(); }

        bool is_hungry() const { return m_hunger.is_higher(); }
        bool is_not_hungry() const { return m_hunger.is_lower(); }

        bool is_thirsty() const { return m_thirst.is_higher(); }
        bool is_not_thirsty() const { return m_thirst.is_lower(); }

        bool is_tired() const { return m_fatigue.is_higher(); }
        bool is_not_tired() const { return m_fatigue.is_lower(); }

        bool is_lonely() const { return m_loneliness.is_higher(); }
        bool is_not_lonely() const { return m_loneliness.is_lower(); }

    };

} // namespace core