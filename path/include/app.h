#pragma once

#include "button.h"
#include "slider.h"

namespace core {

    /// @brief Class representing the main application.
    class app {
    private:
        static app* s_instance; ///< Singleton instance of the app.
        bool m_is_running; ///< Flag indicating if the app is running.
        bool m_is_paused; ///< Flag indicating if the app is paused.

        float m_timer; ///< Timer for the app.

        ui::button* m_button; ///< UI button for the app.
        ui::slider* m_slider; ///< UI slider for the app.

    public:
        /// @brief Constructor for the app class.
        app();

        /// @brief Destructor for the app class.
        virtual ~app();

        /// @brief Run the main loop of the app.
        void run();

    private:
        /// @brief Initialize the app.
        void init();

        /// @brief Deinitialize the app.
        void deinit();

        /// @brief Update the UI elements of the app.
        void update_ui();

        /// @brief Update the app state.
        void update();

        /// @brief Render the app.
        void render();
    };

} // namespace core
