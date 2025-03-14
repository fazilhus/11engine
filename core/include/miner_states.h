#pragma once

#include "state.h"

namespace core {

    class miner;

    class miner_idle : public istate<miner> {
        void enter(miner* e) override;
        void execute(miner* e, int dt = 1) override;
        void make_decision(miner* e) override;
        void process_messages(miner* e) override;
        void change_state(miner* e) override;
        void exit(miner* e) override;        
    };

    class miner_move : public istate<miner> {
        void enter(miner* e) override;
        void execute(miner* e, int dt = 1) override;
        void make_decision(miner* e) override;
        void process_messages(miner* e) override;
        void change_state(miner* e) override;
        void exit(miner* e) override;
    };

    class miner_produce_coal : public istate<miner> {
        void enter(miner* e) override;
        void execute(miner* e, int dt = 1) override;
        void make_decision(miner* e) override;
        void process_messages(miner* e) override;
        void change_state(miner* e) override;
        void exit(miner* e) override;

        bool m_started = false, m_finished = false;
    
    public:
        void finished() { m_finished = true; }
    };

};