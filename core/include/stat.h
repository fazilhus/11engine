#pragma once

#include <string>

namespace core {

    class stat {
    private:
        int m_value;
        int m_min;
        int m_max;
    
    public:
        stat() : stat(0, 0, 100) {
        }

        stat(int value, int min, int max)
            : m_value(value), m_min(min), m_max(max) {
        }

        ~stat() = default;

        int value() const { return m_value; }
        std::string str() const { return std::to_string(m_value); }

        stat& operator+=(int value) {
            m_value += value;
            if (m_value > m_max) {
                m_value = m_max;
            }
            return *this;
        }

        stat& operator-=(int value) {
            m_value -= value;
            if (m_value < m_min) {
                m_value = m_min;
            }
            return *this;
        }
    };

} // namespace core