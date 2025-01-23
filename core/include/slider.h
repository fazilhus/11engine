#pragma once

#include "raylib.h"
#include "raymath.h"

namespace core::ui {

    /// @brief Class representing a UI slider.
    class slider {
    private:
        float m_min; ///< Minimum value of the slider.
        float m_max; ///< Maximum value of the slider.

        Vector2 m_bar_pos; ///< Position of the slider bar.
        Vector2 m_bar_size; ///< Size of the slider bar.
        float m_knob_val; ///< Current value of the slider knob.
        Vector2 m_knob_pos; ///< Position of the slider knob.
        float m_knob_radius; ///< Radius of the slider knob.

        bool m_pressed; ///< Flag indicating if the slider knob is pressed.

    public:
        /// @brief Constructor for the slider class.
        /// @param min Minimum value of the slider.
        /// @param max Maximum value of the slider.
        /// @param bar_pos Position of the slider bar.
        /// @param bar_size Size of the slider bar.
        /// @param knob_radius Radius of the slider knob.
        slider(float min, float max, Vector2 bar_pos, Vector2 bar_size, float knob_radius);

        /// @brief Default destructor for the slider class.
        ~slider() = default;

        /// @brief Draw the slider.
        void draw();

        /// @brief Update the slider.
        void update();

        /// @brief Get the current value of the slider.
        /// @return Current value of the slider.
        float value() const;
    };

} // namespace core::ui