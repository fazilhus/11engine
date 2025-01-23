#pragma once

#include <iostream>

namespace core {

    template <typename entity_type>
    class state {
    public:
        virtual ~state() {}

        virtual void enter(entity_type* e) = 0;
        virtual void make_decision(entity_type* e) = 0;
        virtual void process_messages(entity_type* e) = 0;
        virtual void execute(entity_type* e) = 0;
        virtual void exit(entity_type* e) = 0;
    };

    class human;

    class resting : public state<human> {
    public:
        void enter(human* e) override;
        void make_decision(human* e) override;
        void process_messages(human* e) override;
        void execute(human* e) override;
        void exit(human* e) override;
    };

    class working_at_construction : public state<human> {
    public:
        void enter(human* e) override;
        void make_decision(human* e) override;
        void process_messages(human* e) override;
        void execute(human* e) override;
        void exit(human* e) override;
    };

    class working_at_office : public state<human> {
    public:
        void enter(human* e) override;
        void make_decision(human* e) override;
        void process_messages(human* e) override;
        void execute(human* e) override;
        void exit(human* e) override;
    };

    class eating : public state<human> {
    public:
        void enter(human* e) override;
        void make_decision(human* e) override;
        void process_messages(human* e) override;
        void execute(human* e) override;
        void exit(human* e) override;
    };

    class drinking : public state<human> {
    public:
        void enter(human* e) override;
        void make_decision(human* e) override;
        void process_messages(human* e) override;
        void execute(human* e) override;
        void exit(human* e) override;
    };

    class partying : public state<human> {
    public:
        void enter(human* e) override;
        void make_decision(human* e) override;
        void process_messages(human* e) override;
        void execute(human* e) override;
        void exit(human* e) override;
    };

} // namespace core