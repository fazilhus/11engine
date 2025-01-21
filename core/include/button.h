#pragma once

#include "raylib.h"
#include "raymath.h"
#include <string>

namespace core::ui {
    
    class button {
    private:
        std::string m_label;

        Vector2 m_pos;
        Vector2 m_size;
        Vector2 m_padding;
        
        bool m_pressed;

        Color m_btn_color;
        Color m_btn_pressed_color;
        Color m_font_color;
        
        float m_font_size;

    public:
        button(const std::string& label, Vector2 pos, float font_size);
        ~button() = default;

        void draw() const;
        void update();

        bool is_pressed() const;
    };

} // namespace core::ui