#include "button.h"

namespace core::ui {

    button::button(const std::string& label, Vector2 pos, float font_size)
        : m_label(label), m_pos(pos), m_font_size(font_size), m_pressed(false) {
        m_btn_color = LIGHTGRAY;
        m_btn_pressed_color = GRAY;
        m_font_color = BLACK;

        m_padding = { 10, 5 };

        Vector2 label_size = MeasureTextEx(GetFontDefault(), m_label.c_str(), m_font_size, 1);
        m_size = { label_size.x + m_padding.x * 2, label_size.y + m_padding.y * 2 };
    }

    void button::draw() const {
        DrawRectangleV(m_pos, m_size, m_pressed ? m_btn_pressed_color : m_btn_color);
        auto label_pos = Vector2{ m_pos.x + m_padding.x, m_pos.y + m_padding.y };
        DrawText(
            m_label.c_str(),
            static_cast<int>(label_pos.x), static_cast<int>(label_pos.y),
            static_cast<int>(m_font_size), m_font_color);
    }

    void button::update() {
        auto mouse_pos = GetMousePosition();
        m_pressed = CheckCollisionPointRec(mouse_pos,
            { m_pos.x, m_pos.y, m_size.x, m_size.y }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }

    bool button::is_pressed() const {
        return m_pressed;
    }

} // namespace core::ui