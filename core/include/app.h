#pragma once

#include "entity.h"
#include "state_provider.h"
#include "timer.h"
#include "message.h"

#include "button.h"
#include "slider.h"

namespace core {

    /// @brief Class representing the main application.
    class app {
    private:
        static app* s_instance; ///< Singleton instance of the app.
        bool is_running; ///< Flag indicating if the app is running.
        bool is_paused; ///< Flag indicating if the app is paused.

        state_provider* m_fsm; ///< Finite state machine for the app.
        timer_manager* m_timer_manager; ///< Timer manager for the app.
        entity_manager* m_entity_manager; ///< Entity manager for the app.
        message_sender* m_message_sender; ///< Message sender for the app.

        ui::button* m_button; ///< UI button for the app.
        ui::slider* m_slider; ///< UI slider for the app.

        float timer; ///< Timer for the app.
        float timer_max; ///< Maximum value for the timer.
        long long cycles;

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

        /// @brief Check if the app should quit.
        /// @return True if the app should quit, false otherwise.
        bool should_quit();

        /// @brief Draw all humans in the app.
        void draw_humans() const;

        /// @brief Draw a single human in the app.
        /// @param h Pointer to the human to draw.
        /// @param x X-coordinate for drawing the human.
        /// @param y Y-coordinate for drawing the human.
        void draw_human(const human* h, int x, int y) const;
    };

} // namespace core
