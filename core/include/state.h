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

    class resting : public state {
    public:
        void enter(human* e) override;

        void execute(human* e) override;

        void exit(human* e) override;
    };

    class working_at_construction : public state {
    public:
        void enter(human* e) override;

        void execute(human* e) override;

        void exit(human* e) override;
    };

    class working_at_office : public state {
    public:
        void enter(human* e) override;

        void execute(human* e) override;

        void exit(human* e) override;
    };

    class eating : public state {
    public:
        void enter(human* e) override;

        void execute(human* e) override;

        void exit(human* e) override;
    };

    class drinking : public state {
    public:
        void enter(human* e) override;

        void execute(human* e) override;

        void exit(human* e) override;
    };

    class partying : public state {
    public:
        void enter(human* e) override;

        void execute(human* e) override;

        void exit(human* e) override;
    };

} // namespace core