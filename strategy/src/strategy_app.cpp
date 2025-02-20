#include "strategy_app.h"

#include <iostream>
#include <filesystem>
#include <chrono>
#include <fstream>
#include <sstream>

#include "nlohmann/json.hpp"

#include "util.h"

namespace core {

	app* app::s_instance = nullptr;

	app::app() {
		InitWindow(1600, 1000, "11Engine: Pathfinding");
		SetTargetFPS(60);

		s_instance = this;

		m_is_running = true;
		m_timer = 0.0f;

		m_config = nullptr;

		m_map = nullptr;

		// Create a texture for the map
		m_map_texture = LoadRenderTexture(1000, 1000);
	}

	app::~app() {
		// Unload the map texture
		UnloadRenderTexture(m_map_texture);

		CloseWindow();
	}

	void app::run() {
		init();

		while (!WindowShouldClose()) {
			update_ui();

			if (m_timer > 0.1f) {
				m_timer = 0;
	
				// update stuff
				update();
			}

			render();
		}

		deinit();
	}

	void app::init() {
		util::init_random();
		
		std::fstream f(std::filesystem::absolute("./strategy/res/cfg.json"), std::ios::binary | std::ios::in);
		std::stringstream buf;
		buf << f.rdbuf();
		
		auto doc = nlohmann::json::parse(buf);
		f.close();
		
		m_config = new game_config(doc);
		
		m_map = new map(std::filesystem::absolute("./strategy/res/map.txt"));
	}

	void app::deinit() {
		if (m_config)
			delete m_config;

		if (m_map)
			delete m_map;
	}

	void app::update_ui() {
	}

	void app::update() {
	}

	void app::render() {
		BeginDrawing();
		ClearBackground(BLACK);

		// Draw the map texture
		draw_map(m_map);
		DrawTextureRec(m_map_texture.texture, {0, 0, (float)m_map_texture.texture.width, (float)m_map_texture.texture.height}, {0, 0}, WHITE);

		EndDrawing();
	}

    void app::draw_map(const map *map) const {
		BeginTextureMode(m_map_texture);
		ClearBackground(BLACK);

		// Draw the map onto the texture
		auto [n, m] = map->get_dim();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				tile_type tile = map->get(i, j)->type;
				Color color;

				switch (tile) {
					case tile_type_forest:
						color = DARKGREEN;
						break;
					case tile_type_water:
						color = BLUE;
						break;
					case tile_type_swamp:
						color = BROWN;
						break;
						case tile_type_mountain:
						color = GRAY;
						break;
					case tile_type_grass:
						color = GREEN;
						break;
					default:
						color = WHITE;
						break;
				}

				DrawRectangle(i * 10, j * 10, 10, 10, color); // Assuming each tile is 10x10 pixels
			}
		}

		EndTextureMode();
    }

} // namespace core
