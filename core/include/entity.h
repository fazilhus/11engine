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

        virtual void update_stage1() = 0;
        virtual void update_stage2() = 0;

        int id() const { return m_id; }
        void set_id(int id) { m_id = id; }

        const std::string& name() const { return m_name; }
        inbox& inbox() { return m_inbox; }

        void accept_invite(message_type type);
        void send_invite(message_type type, int sender_id);
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

    template <typename entity_type>
    class state;

    class human : public entity {
    public:
        stat m_money;
        stat m_hunger;
        stat m_thirst;
        stat m_fatigue;
        stat m_loneliness;
        float m_chance;
        fsm_state m_fsm_state;
        loc m_location;
        int m_cycles;

    private:
        std::shared_ptr<state<human>> m_current_state;
        fsm_state m_next_state;

    public:
        human(int id, const std::string& name);
        ~human() override;

        void update_stage1() override;
        void update_stage2() override;

        void change_state();

        fsm_state next_state() const { return m_next_state; }
        void set_next_state(fsm_state state) { m_next_state = state; }

        bool is_dead() const {
            return m_cycles >= 100 || m_hunger.is_max() || m_thirst.is_max() || m_fatigue.is_max() || m_loneliness.is_max();
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

        bool should_eat() const { return is_hungry() && m_money >= 20; }
        bool should_continue_eat() const { return !is_not_hungry() && m_money >= 20; }
        bool could_eat() const {
            return !is_thirsty() && !is_tired() && !is_lonely() && m_money >= 20 && want_accept_invite();
        }

        bool should_drink() const { return is_thirsty() && m_money >= 15; }
        bool should_continue_drink() const { return !is_not_thirsty() && m_money >= 15; }
        bool could_drink() const {
            return !is_hungry() && !is_tired() && !is_lonely() && m_money >= 15 && want_accept_invite();
        }

        bool should_party() const { return is_lonely() && m_money >= 30; }
        bool should_continue_party() const { return !is_not_lonely() && m_money >= 30; }
        bool could_party() const {
            return !is_hungry() && !is_thirsty() && !is_tired() && m_money >= 30 && want_accept_invite();
        }

        fsm_state decide_where_to_work() const;

    private:
        //bool could_accept_invite() const { return !is_hungry() && !is_thirsty() && !is_tired(); }
        bool want_accept_invite() const { return util::random_float(0.0f, 1.0f) > m_chance; }

    };

} // namespace core