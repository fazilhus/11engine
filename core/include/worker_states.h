#pragma once

#include "state.h"

namespace core {

    class worker;

    class worker_idle : public istate<worker> {
        void enter(worker* e) override;
        void execute(worker* e, int dt = 1) override;
        void make_decision(worker* e) override;
        void process_messages(worker* e) override;
        void change_state(worker* e) override;
        void exit(worker* e) override;
    };

    class worker_move_to_resource : public istate<worker> {
        void enter(worker* e) override;
        void execute(worker* e, int dt = 1) override;
        void make_decision(worker* e) override;
        void process_messages(worker* e) override;
        void change_state(worker* e) override;
        void exit(worker* e) override;
    };

    class worker_move_to_base : public istate<worker> {
        void enter(worker* e) override;
        void execute(worker* e, int dt = 1) override;
        void make_decision(worker* e) override;
        void process_messages(worker* e) override;
        void change_state(worker* e) override;
        void exit(worker* e) override;
    };

    class worker_gather_resource : public istate<worker> {
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