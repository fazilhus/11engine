#pragma once

#include "raylib.h"

#include "cfg.h"
#include "smap.h"

namespace core {

    /// @brief Class representing the main application.
    class app {
    private:
        static app* s_instance; ///< Singleton instance of the app.
        bool m_is_running; ///< Flag indicating if the app is running.
        
        float m_timer;

        game_config* m_config;

        map* m_map;

        RenderTexture2D m_map_texture;

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

        void draw_map(const map* m) const;
    };

} // namespace core
