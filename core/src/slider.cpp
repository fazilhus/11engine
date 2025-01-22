#include "slider.h"

namespace core::ui {

    slider::slider(float min, float max, Vector2 bar_pos, Vector2 bar_size, float knob_radius)
        : m_min(min), m_max(max), m_bar_pos(bar_pos), m_bar_size(bar_size), m_knob_radius(knob_radius) {
            m_pressed = false;
            m_knob_val = 0;
    }

    void slider::draw() {
        auto bar_pos = m_bar_pos + m_bar_size / 2;
        DrawRectangleV(m_bar_pos, m_bar_size, LIGHTGRAY);

        //m_knob_pos = Vector2{ m_bar_pos.x + m_bar_size.x * m_knob_val, bar_pos.y };
        m_knob_pos.x = m_bar_pos.x + m_bar_size.x * m_knob_val;
        m_knob_pos.y = m_bar_pos.y + m_bar_size.y / 2;
        DrawCircleV(m_knob_pos, m_knob_radius, GRAY);
    }

    void slider::update() {
        if (m_pressed) {
            float mx = (float)GetMouseX();
            if (mx < m_bar_pos.x) mx = m_bar_pos.x;
            if (mx > m_bar_pos.x + m_bar_size.x) mx = m_bar_pos.x + m_bar_size.x;
            m_knob_val = (mx - m_bar_pos.x) / m_bar_size.x;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            auto mouse_pos = GetMousePosition();
            m_pressed = CheckCollisionPointCircle(mouse_pos, m_knob_pos, m_knob_radius);
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            m_pressed = false;
        }
    }

    float slider::value() const {
        return m_min + (m_max - m_min) * m_knob_val;
    }

} // namespace core::ui