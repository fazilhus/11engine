#pragma once

#include "state.h"

namespace core {

    class worker;

    class idle : public istate<worker> {
        void enter(worker* e) override;
        void execute(worker* e, int dt = 1) override;
        void make_decision(worker* e) override;
        void process_messages(worker* e) override;
        void change_state(worker* e) override;
        void exit(worker* e) override;
    };

    class move : public istate<worker> {
        void enter(worker* e) override;
        void execute(worker* e, int dt = 1) override;
        void make_decision(worker* e) override;
        void process_messages(worker* e) override;
        void change_state(worker* e) override;
        void exit(worker* e) override;
    };

    class gather_resource : public istate<worker> {
        void enter(worker* e) override;
        void execute(worker* e, int dt = 1) override;
        void make_decision(worker* e) override;
        void process_messages(worker* e) override;
        void change_state(worker* e) override;
        void exit(worker* e) override;

        bool m_finished = false;

    public:
        void finished_gathering() { m_finished = true; }
    };

};