#pragma once

#include "pmap.h"

namespace core {

    /// @brief Class representing the main application.
    class app {
    private:
        static app* s_instance; ///< Singleton instance of the app.
        bool m_is_running; ///< Flag indicating if the app is running.

        map* m_map;
        path<tile<tile_type>> m_path;
        path<tile<tile_type>> m_path_d;
        path<tile<tile_type>> m_path_a;

        int m_map_size_px_x, m_map_size_px_y;
        int m_tile_size, m_path_tile_size;
        
        float m_time;
        float m_time_d;
        float m_time_a;

        int m_map_choice;

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

        void load_map();
        void draw_map(const map* m, int x0 = 0, int y0 = 0) const;
        void draw_path(const path<tile<tile_type>>& p, int x0 = 0, int y0 = 0) const;
    };

} // namespace core
