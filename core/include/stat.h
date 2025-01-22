#pragma once

#include <string>

namespace core {

    class stat {
    private:
        int m_value;
        int m_min;
        int m_low;
        int m_high;
        int m_max;
    
    public:
        stat() : stat(0, 0, 25, 75, 100) {
        }

        stat(int value, int min, int low, int high, int max)
            : m_value(value), m_min(min), m_low(low), m_high(high), m_max(max) {
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

        bool is_min() const {
            return m_value == m_min;
        }

        bool is_lower() const {
            return m_value < m_low;
        }

        bool is_normal() const {
            return m_value >= m_low && m_value <= m_high;
        }

        bool is_higher() const {
            return m_value > m_high;
        }

        bool is_max() const {
            return m_value == m_max;
        }

        bool operator>(int value) const {
            return m_value > value;
        }

        bool operator<(int value) const {
            return m_value < value;
        }

        bool operator>=(int value) const {
            return m_value >= value;
        }

        bool operator<=(int value) const {
            return m_value <= value;
        }
    };

} // namespace core