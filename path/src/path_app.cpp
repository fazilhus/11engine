#include "path_app.h"

#include "raylib.h"
#include <iostream>
#include <filesystem>
#include <chrono>

#include "util.h"
#include "enum.h"
#include "pmap.h"


namespace core {

	app* app::s_instance = nullptr;

	app::app() {
		InitWindow(1280, 720, "11Engine: Pathfinding");
		SetTargetFPS(60);

		s_instance = this;

		m_is_running = true;
		m_is_paused = true;

		m_timer = 0;
	}

	app::~app() {
		CloseWindow();
	}

	void app::run() {
		init();

		while (!WindowShouldClose()) {
			update_ui();

			if (!m_is_paused) {
				update();
			}

			render();
		}

		deinit();
	}

	void app::init() {
		util::init_random();

		m_map = new map(std::filesystem::absolute("./path/res/Map3.txt"));

		{
			auto start = std::chrono::high_resolution_clock::now();
			m_path = m_map->get_path(tile_type_start, tile_type_finish);
			auto stop = std::chrono::high_resolution_clock::now();
			auto dur = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
			m_time = dur.count();
		}
		{
			auto start = std::chrono::high_resolution_clock::now();
			m_path_d = m_map->get_path(tile_type_start, tile_type_finish, path_algo_dijkstra);
			auto stop = std::chrono::high_resolution_clock::now();
			auto dur = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
			m_time_d = dur.count();
		}
		{
			auto start = std::chrono::high_resolution_clock::now();
			m_path_a = m_map->get_path(tile_type_start, tile_type_finish, path_algo_astar);
			auto stop = std::chrono::high_resolution_clock::now();
			auto dur = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
			m_time_a = dur.count();
		}
	}

	void app::deinit() {
		delete m_map;
	}

	void app::update_ui() {
	}

	void app::update() {
		m_timer += GetFrameTime();
		
		if (m_timer >= 0.5f) {
			m_timer = 0;
		}
	}

	void app::render() {
		BeginDrawing();
		ClearBackground(BLACK);

		draw_map(m_map);
		draw_path(m_path);
		draw_map(m_map, 416, 0);
		draw_path(m_path_d, 416, 0);
		draw_map(m_map, 832, 0);
		draw_path(m_path_a, 832, 0);

		DrawText(("Breadth-First " + std::to_string(m_time)).c_str(), 10, 450, 20, WHITE);
		DrawText(("Dijkstra " + std::to_string(m_time_d)).c_str(), 416, 450, 20, WHITE);
		DrawText(("A* " + std::to_string(m_time_a)).c_str(), 832, 450, 20, WHITE);

		EndDrawing();
	}

	void app::draw_map(const map* map, int x0, int y0) const {
		auto [n, m] = map->get_dim();
		const int tile_size = 16;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int x = x0 + i * tile_size;
				int y = y0 + j * tile_size;

				switch (map->get(i, j)->type) {
				case tile_type_start: {
						DrawRectangle(x, y, tile_size, tile_size, GREEN);
						break;
				}
				case tile_type_finish: {
						DrawRectangle(x, y, tile_size, tile_size, RED);
						break;
				}
				case tile_type_rock: {
						DrawRectangle(x, y, tile_size, tile_size, DARKGRAY);
						break;
				}
				case tile_type_road: {
						DrawRectangle(x, y, tile_size, tile_size, BEIGE);
						break;
				}
				default: {
#ifdef DEBUG
						assert(false && "invalid map path algorithm");
#endif
				}
				}
			}
		}
	}

	void app::draw_path(const path<tile<tile_type>>& p, int x0, int y0) const {
		const int map_tile_size = 16;
		const int tile_size = 12;
		for (const auto& tile : p.m_path) {
			int x = x0 + tile.lock()->posx * map_tile_size + (map_tile_size - tile_size) / 2;
			int y = y0 + tile.lock()->posy * map_tile_size + (map_tile_size - tile_size) / 2;
			DrawRectangle(x, y, tile_size, tile_size, BLUE);
		}
	}
} // namespace core
