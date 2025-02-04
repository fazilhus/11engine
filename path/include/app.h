#pragma once

namespace core {

    /// @brief Class representing the main application.
    class app {
    private:
        static app* s_instance; ///< Singleton instance of the app.
        bool is_running; ///< Flag indicating if the app is running.
        bool is_paused; ///< Flag indicating if the app is paused.

        float timer; ///< Timer for the app.
        float timer_max; ///< Maximum value for the timer.
        long long cycles; ///< amount of simulation ticks

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
