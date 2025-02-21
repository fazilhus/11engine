#pragma once

namespace core {

    class clock {
    private:
        static clock* s_instance;
        long long m_tick;
    
    public:
        clock();

        void update(int dt = 1);

        static const clock* get() { return s_instance; }
        long long tick() const { return m_tick; }
    };

} // namespace core