#pragma once

#include "raylib.h"
#include "raymath.h"
#include <string>

namespace core::ui {
    
    /// @brief Class representing a UI button.
    class button {
    private:
        std::string m_label; ///< Label of the button.

        Vector2 m_pos; ///< Position of the button.
        Vector2 m_size; ///< Size of the button.
        Vector2 m_padding; ///< Padding of the button.
        
        bool m_pressed; ///< Flag indicating if the button is pressed.

        Color m_btn_color; ///< Color of the button.
        Color m_btn_pressed_color; ///< Color of the button when pressed.
        Color m_font_color; ///< Color of the button label.
        
        float m_font_size; ///< Font size of the button label.

    public:
        /// @brief Constructor for the button class.
        /// @param label Label of the button.
        /// @param pos Position of the button.
        /// @param font_size Font size of the button label.
        button(const std::string& label, Vector2 pos, float font_size);

        /// @brief Default destructor for the button class.
        ~button() = default;

        /// @brief Draw the button.
        void draw() const;

        /// @brief Update the button state.
        void update();

        /// @brief Check if the button is pressed.
        /// @return True if the button is pressed, false otherwise.
        bool is_pressed() const;
    };

} // namespace core::ui