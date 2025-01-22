#pragma once

#include "raylib.h"
#include "raymath.h"

namespace core::ui {

    class slider {
    private:
        float m_min;
        float m_max;

        Vector2 m_bar_pos;
        Vector2 m_bar_size;
        float m_knob_val;
        Vector2 m_knob_pos;
        float m_knob_radius;

        bool m_pressed;

    public:
        slider(float min, float max, Vector2 bar_pos, Vector2 bar_size, float knob_radius);
        ~slider() = default;

        void draw();
        void update();

        float value() const;
    };

} // namespace core::ui