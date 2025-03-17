#include "strategy_app.h"

#include <iostream>
#include <filesystem>
#include <chrono>
#include <fstream>
#include <sstream>

#include "nlohmann/json.hpp"

#include "util.h"
#include "scout.h"
#include "worker.h"

namespace core {

	app* app::s_instance = nullptr;

	app::app() {
		InitWindow(1400, 1000, "11Engine: Pathfinding");
		SetTargetFPS(60);

		s_instance = this;

		m_is_running = true;
		m_is_paused = false;
		m_timer = 0.0f;

		m_config = nullptr;
		m_clock = nullptr;
		m_map = nullptr;
		m_tm = nullptr;
		m_jm = nullptr;
		m_em = nullptr;

		// Create a texture for the map
		m_map_texture = LoadRenderTexture(1000, 1000);

		m_button = new ui::button("Pause", Vector2{ 1300, 10 }, 20);
		m_slider = new ui::slider(1.0f / 60.0f, 1.0f, Vector2{ 1020, 900 }, Vector2{ 360, 20 }, 10);
	}

	app::~app() {
		delete m_slider;
		delete m_button;
		// Unload the map texture
		UnloadRenderTexture(m_map_texture);

		CloseWindow();
	}

	void app::run() {
		init();

		while (!WindowShouldClose()) {
			update_ui();

			if (!m_is_paused)
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
		m_tm = new timer_manager();
		m_jm = new job_manager();
		m_jm->add_worker_job({job_type_create_scout, 9, {}, resource_type_none}, 10);
		m_jm->add_worker_job({job_type_create_builder, 9, {}, resource_type_none}, 2);
		m_jm->add_worker_job({job_type_create_miner, 9, {}, resource_type_none}, 6);
		//m_jm->add_worker_job({job_type_collect_resource, 1, m_map->get_start().lock(), resource_type_wood}, 100);
		m_jm->add_builder_job({job_type_build_coal_mine, 5}, 6);
		m_jm->add_miner_job({job_type_produce_coal, 5}, 200);
		
		m_em = new entity_manager();
		for (int i = 0; i < 50; ++i) {
			m_em->add_entity<worker>();
		}

	}

	void app::deinit() {
		if (m_em)
			delete m_em;

		if (m_jm)
			delete m_jm;
			
		if (m_tm)
			delete m_tm;
			
		if (m_map)
			delete m_map;

		if (m_clock)
			delete m_clock;
			
		if (m_config)
				delete m_config;
	}

	void app::update_ui() {
		m_button->update();
		m_slider->update();
		
		if (m_button->is_pressed()) {
			m_is_paused = !m_is_paused;
		}
	}

	void app::update(int dt) {
		m_timer += GetFrameTime();

		if (m_timer > m_slider->value()) {
			m_timer = 0;

			// update stuff
			m_clock->update(dt);
			m_tm->update(dt);
			m_em->update(dt);

			if (m_map->get_start().lock()->storage[resource_type_coal] >= 200) {
				m_is_paused = true;
				m_is_running = false;
			}
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
		
		DrawTextureRec(m_map_texture.texture, {0, 0, (float)m_map_texture.texture.width, -(float)m_map_texture.texture.height}, {0, 0}, WHITE);
		DrawText(("Tickrate: " + std::to_string(1.0f / m_slider->value())).c_str(), 1020, 10, 20, WHITE);
		DrawText(("Framerate: " + std::to_string(GetFrameTime())).c_str(), 1020, 40, 20, WHITE);
		DrawText(("Cycles: " + std::to_string(m_clock->tick())).c_str(), 1020, 70, 20, WHITE);
		DrawText(("Coal: " + std::to_string(m_map->get_start().lock()->storage[resource_type_coal])).c_str(), 1020, 100, 20, WHITE);

		m_button->draw();
		m_slider->draw();

		if (m_is_paused) {
			if (m_is_running)
				DrawText("PAUSED", 590, 470, 80, RED);
			else
				DrawText("YOU WIN", 550, 470, 80, GOLD);
		}

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

				switch(tile->building) {
				case building_type_base:
					DrawText("B", i * 10 + 1, j * 10 + 1, 8, BLACK);
					break;
				case building_type_coal_mine:
					DrawText("M", i * 10 + 1, j * 10 + 1, 8, BLACK);
					break;
				}
			}
		}
    }

    void app::draw_entities() const {
		for (const auto& e : m_em->entities()) {
			auto [x, y] = e->pos();
			
			auto col = BLACK;
			switch (e->type()) {
			case unit_type_worker: col = ORANGE; break;
			case unit_type_scout: col = WHITE; break;
			case unit_type_builder: col = GRAY; break;
			case unit_type_miner: col = BLACK; break;
			}
			DrawCircle(x, y, 2, col);
		}
    }

} // namespace core
