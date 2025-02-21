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
		m_clock = nullptr;
		m_map = nullptr;
		m_em = nullptr;

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

			update();

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

		m_clock = new clock();

		m_map = new map(std::filesystem::absolute("./strategy/res/map.txt"));
		m_em = new entity_manager();
		for (int i = 0; i < 10; ++i) {
			m_em->add_entity(std::make_unique<scout>(i, std::to_string(i)));
		}
	}

	void app::deinit() {
		if (m_em)
			delete m_em;	
			
		if (m_map)
			delete m_map;

		if (m_clock)
			delete m_clock;
			
		if (m_config)
				delete m_config;
	}

	void app::update_ui() {
	}

	void app::update(int dt) {
		m_timer += GetFrameTime();

		if (m_timer > 0.25f) {
			m_timer = 0;

			// update stuff
			m_clock->update(dt);
			m_em->update(dt);
		}
	}

	void app::render() {
		BeginDrawing();
		ClearBackground(BLACK);

		// Draw the map texture
		BeginTextureMode(m_map_texture);
		ClearBackground(BLACK);
		
		draw_map();
		draw_entities();
		
		EndTextureMode();
		
		DrawTextureRec(m_map_texture.texture, {0, 0, (float)m_map_texture.texture.width, (float)m_map_texture.texture.height}, {0, 0}, WHITE);

		EndDrawing();
	}

    void app::draw_map() const {
		// Draw the map onto the texture
		auto [n, m] = m_map->get_dim();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				const auto& tile = m_map->get_tile(i, j);
				Color color;

				if (!tile->discovered) {
					color = BLACK;
				}
				else {
					switch (tile->type) {
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
				}

				DrawRectangle(i * 10, j * 10, 10, 10, color); // Assuming each tile is 10x10 pixels
			}
		}
    }

    void app::draw_entities() const {
		for (const auto& e : m_em->entities()) {
			auto [x, y] = e->pos();
			DrawCircle(x, y, 1, DARKGRAY);
		}
    }

} // namespace core
