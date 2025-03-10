#pragma once

#include "state.h"

namespace core {

    class builder;

    class builder_idle : public istate<builder> {
        void enter(builder* e) override;
        void execute(builder* e, int dt = 1) override;
        void make_decision(builder* e) override;
        void process_messages(builder* e) override;
        void change_state(builder* e) override;
        void exit(builder* e) override;        
    };

    class builder_build : public istate<builder> {
        void enter(builder* e) override;
        void execute(builder* e, int dt = 1) override;
        void make_decision(builder* e) override;
        void process_messages(builder* e) override;
        void change_state(builder* e) override;
        void exit(builder* e) override;
    };

};