#pragma once

#include "state.h"

namespace core {

    class scout;

    class wander : public istate<scout> {
        void enter(scout* e) override;
        void execute(scout* e, int dt = 1) override;
        void make_decision(scout* e) override;
        void process_messages(scout* e) override;
        void change_state(scout* e) override;
        void exit(scout* e) override;
    };

};