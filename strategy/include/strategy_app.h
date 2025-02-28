#pragma once

#include "raylib.h"

#include "game_config.h"
#include "clock.h"
#include "timer.h"
#include "map.h"
#include "entity_manager.h"

namespace core {

    /// @brief Class representing the main application.
    class app {
    private:
        static app* s_instance; ///< Singleton instance of the app.
        bool m_is_running; ///< Flag indicating if the app is running.
        
        float m_timer;

        game_config* m_config;
        clock* m_clock;
        map* m_map;
        timer_manager* m_tm;
        entity_manager* m_em;

        RenderTexture2D m_map_texture;

    public:
        /// @brief Constructor for the app class.
        app();

        /// @brief Destructor for the app class.
        virtual ~app();

        /// @brief Run the main loop of the app.
        void run();

        const map* get_map() const { return m_map; }

    private:
        /// @brief Initialize the app.
        void init();

        /// @brief Deinitialize the app.
        void deinit();

        /// @brief Update the UI elements of the app.
        void update_ui();

        /// @brief Update the app state.
        void update(int dt = 1);

        /// @brief Render the app.
        void render();

        void draw_map() const;
        void draw_entities() const;
    };

} // namespace core
