#pragma once

#include <string>

namespace core {

    /// @brief Representation of an agent's need
    class need {
    private:
        int m_value; ///< Current value
        int m_min; ///< Minimum
        int m_low; ///< Low bar value
        int m_high; ///< High bar value
        int m_max; ///< Maximum
    
    public:
        /// @brief Default constructor for the need class.
        need() : need(0, 0, 25, 75, 100) {
        }

        /// @brief Constructor for the need class.
        /// @param value Initial value of the need.
        /// @param min Minimum value of the need.
        /// @param low Low bar value of the need.
        /// @param high High bar value of the need.
        /// @param max Maximum value of the need.
        need(int value, int min, int low, int high, int max)
            : m_value(value), m_min(min), m_low(low), m_high(high), m_max(max) {
        }

        ~need() = default;

        /// @brief Get the current value of the need.
        /// @return Current value of the need.
        int value() const { return m_value; }

        /// @brief Get the string representation of the need's value.
        /// @return String representation of the need's value.
        std::string str() const { return std::to_string(m_value); }

        /// @brief Increment the value of the need.
        /// @param value Amount to increment the need by.
        /// @return Reference to the updated need object.
        need& operator+=(int value) {
            m_value += value;
            if (m_value > m_max) {
                m_value = m_max;
            }
            return *this;
        }

        /// @brief Decrement the value of the need.
        /// @param value Amount to decrement the need by.
        /// @return Reference to the updated need object.
        need& operator-=(int value) {
            m_value -= value;
            if (m_value < m_min) {
                m_value = m_min;
            }
            return *this;
        }

        /// @brief Check if the need is at its minimum value.
        /// @return True if the need is at its minimum value, false otherwise.
        bool is_min() const {
            return m_value == m_min;
        }

        /// @brief Check if the need is lower than the low bar value.
        /// @return True if the need is lower than the low bar value, false otherwise.
        bool is_lower() const {
            return m_value < m_low;
        }

        /// @brief Check if the need is within the normal range.
        /// @return True if the need is within the normal range, false otherwise.
        bool is_normal() const {
            return m_value >= m_low && m_value <= m_high;
        }

        /// @brief Check if the need is higher than the high bar value.
        /// @return True if the need is higher than the high bar value, false otherwise.
        bool is_higher() const {
            return m_value > m_high;
        }

        /// @brief Check if the need is at its maximum value.
        /// @return True if the need is at its maximum value, false otherwise.
        bool is_max() const {
            return m_value == m_max;
        }

        /// @brief Check if the need's value is greater than a given value.
        /// @param value Value to compare against.
        /// @return True if the need's value is greater than the given value, false otherwise.
        bool operator>(int value) const {
            return m_value > value;
        }

        /// @brief Check if the need's value is less than a given value.
        /// @param value Value to compare against.
        /// @return True if the need's value is less than the given value, false otherwise.
        bool operator<(int value) const {
            return m_value < value;
        }

        /// @brief Check if the need's value is greater than or equal to a given value.
        /// @param value Value to compare against.
        /// @return True if the need's value is greater than or equal to the given value, false otherwise.
        bool operator>=(int value) const {
            return m_value >= value;
        }

        /// @brief Check if the need's value is less than or equal to a given value.
        /// @param value Value to compare against.
        /// @return True if the need's value is less than or equal to the given value, false otherwise.
        bool operator<=(int value) const {
            return m_value <= value;
        }
    };

} // namespace core