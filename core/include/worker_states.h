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

    class worker_move_to_target : public istate<worker> {
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

        bool m_started = false;
        bool m_finished = false;

    public:
        void finished() { m_finished = true; }
    };
    
    class worker_store_resource : public istate<worker> {
        void enter(worker* e) override;
        void execute(worker* e, int dt = 1) override;
        void make_decision(worker* e) override;
        void process_messages(worker* e) override;
        void change_state(worker* e) override;
        void exit(worker* e) override;
    };

    class worker_upgrade_to_scout : public istate<worker> {
        void enter(worker* e) override;
        void execute(worker* e, int dt = 1) override;
        void make_decision(worker* e) override;
        void process_messages(worker* e) override;
        void change_state(worker* e) override;
        void exit(worker* e) override;

        bool m_finished = false;

    public:
        void finished() { m_finished = true; }
    };

    class worker_upgrade_to_builder : public istate<worker> {
        void enter(worker* e) override;
        void execute(worker* e, int dt = 1) override;
        void make_decision(worker* e) override;
        void process_messages(worker* e) override;
        void change_state(worker* e) override;
        void exit(worker* e) override;

        bool m_finished = false;

    public:
        void finished() { m_finished = true; }
    };

    class worker_upgrade_to_miner : public istate<worker> {
        void enter(worker* e) override;
        void execute(worker* e, int dt = 1) override;
        void make_decision(worker* e) override;
        void process_messages(worker* e) override;
        void change_state(worker* e) override;
        void exit(worker* e) override;

        bool m_finished = false;

    public:
        void finished() { m_finished = true; }
    };

};