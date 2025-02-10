#pragma once

#include "state.h"

namespace core {

    class human;

    class global_state : public istate<human> {
    public:
        void enter(human* e) override;
        void execute(human* e) override;
        void make_decision(human* e) override;
        void process_messages(human* e) override;
        void change_state(human* e) override;
        void exit(human* e) override;
    };

    class state : public istate<human> {
    public:
        void enter(human* e) override;
        void execute(human* e) override;
        void make_decision(human* e) override;
        void process_messages(human* e) override;
        void change_state(human* e) override;
        void exit(human* e) override;
    };

} // namespace fsm