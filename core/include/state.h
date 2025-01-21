#pragma once

#include <iostream>

namespace core {

    class human;

    class state {
    public:
        virtual ~state();

        virtual void enter(human* e) = 0;
        virtual void execute(human* e) = 0;
        virtual void exit(human* e) = 0;
    };

    class working : public state {
    public:
        void enter(human* e) override;

        void execute(human* e) override;

        void exit(human* e) override;
    };

    class resting : public state {
    public:
        void enter(human* e) override;

        void execute(human* e) override;

        void exit(human* e) override;
    };

} // namespace core