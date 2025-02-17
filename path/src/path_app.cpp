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

		m_map = nullptr;
		m_map_choice = -1;
	}

	app::~app() {
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
	}

	void app::deinit() {
		if (m_map)
			delete m_map;
	}

	void app::update_ui() {
	}

	void app::update() {
		if (m_map_choice == -1) {
			if (IsKeyPressed(KEY_ONE)) {
				m_map_choice = 1;
				load_map();
			}
			if (IsKeyPressed(KEY_TWO)) {
				m_map_choice = 2;
				load_map();
			}
			if (IsKeyPressed(KEY_THREE)) {
				m_map_choice = 3;
				load_map();
			}
		}
		else {
			if (IsKeyPressed(KEY_Q)) {
				delete m_map;
				m_map_choice = -1;
			}
		}
	}

	void app::render() {
		BeginDrawing();
		ClearBackground(BLACK);

		if (m_map_choice == -1) {
			DrawText("Select the Map:", 500, 315, 20, WHITE);
			DrawText("Map1: Press 1", 500, 345, 20, WHITE);
			DrawText("Map2: Press 2", 500, 375, 20, WHITE);
			DrawText("Map3: Press 3", 500, 405, 20, WHITE);
		}
		else {
			draw_map(m_map);
			draw_path(m_path);
			DrawText(("Breadth-First " + std::to_string(m_time) + " ms").c_str(), 10, m_map_size_px_y + 25, 20, WHITE);

			draw_map(m_map, m_map_size_px_x, 0);
			draw_path(m_path_d, m_map_size_px_x, 0);
			DrawText(("Dijkstra " + std::to_string(m_time_d) + " ms").c_str(), m_map_size_px_x + 10, m_map_size_px_y + 25, 20, WHITE);

			draw_map(m_map, m_map_size_px_x * 2, 0);
			draw_path(m_path_a, m_map_size_px_x * 2, 0);
			DrawText(("A* " + std::to_string(m_time_a) + " ms").c_str(), m_map_size_px_x * 2 + 10, m_map_size_px_y + 25, 20, WHITE);

			DrawText("To go back to Selection: Press Q", 10, 680, 20, WHITE);
		}

		EndDrawing();
	}

	void app::load_map() {
		switch (m_map_choice) {
		case 1:
			m_map = new map(std::filesystem::absolute("./path/res/Map1.txt"));
			break;
		case 2:
			m_map = new map(std::filesystem::absolute("./path/res/Map2.txt"));
			break;
		case 3:
			m_map = new map(std::filesystem::absolute("./path/res/Map3.txt"));
			break;
		default:
			std::cerr << "[ERROR] invalid map\n";
			exit(1);
		}

		int x = GetScreenWidth();
		int y = GetScreenHeight();

		auto [map_n, map_m] = m_map->get_dim();
		
		m_map_size_px_x = x / 3;
		m_tile_size = m_map_size_px_x / map_n;
		m_map_size_px_y = map_m * m_tile_size;
		m_path_tile_size = static_cast<int>(static_cast<float>(m_tile_size) * 0.8f);

		{
			auto start = std::chrono::high_resolution_clock::now();
			m_path = m_map->get_path(tile_type_start, tile_type_finish);
			auto stop = std::chrono::high_resolution_clock::now();
			auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
			m_time = static_cast<float>(dur.count()) / 1000000.0f;
		}
		{
			auto start = std::chrono::high_resolution_clock::now();
			m_path_d = m_map->get_path(tile_type_start, tile_type_finish, path_algo_dijkstra);
			auto stop = std::chrono::high_resolution_clock::now();
			auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
			m_time_d = static_cast<float>(dur.count()) / 1000000.0f;
		}
		{
			auto start = std::chrono::high_resolution_clock::now();
			m_path_a = m_map->get_path(tile_type_start, tile_type_finish, path_algo_astar);
			auto stop = std::chrono::high_resolution_clock::now();
			auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
			m_time_a = static_cast<float>(dur.count()) / 1000000.0f;
		}
	}

	void app::draw_map(const map* map, int x0, int y0) const {
		auto [n, m] = map->get_dim();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int x = x0 + i * m_tile_size;
				int y = y0 + j * m_tile_size;

				switch (map->get(i, j)->type) {
				case tile_type_start: {
						DrawRectangle(x, y, m_tile_size, m_tile_size, GREEN);
						break;
				}
				case tile_type_finish: {
						DrawRectangle(x, y, m_tile_size, m_tile_size, RED);
						break;
				}
				case tile_type_rock: {
						DrawRectangle(x, y, m_tile_size, m_tile_size, DARKGRAY);
						break;
				}
				case tile_type_road: {
						DrawRectangle(x, y, m_tile_size, m_tile_size, BEIGE);
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
		for (const auto& tile : p.m_path) {
			int x = x0 + tile.lock()->posx * m_tile_size + (m_tile_size - m_path_tile_size) / 2;
			int y = y0 + tile.lock()->posy * m_tile_size + (m_tile_size - m_path_tile_size) / 2;
			DrawRectangle(x, y, m_path_tile_size, m_path_tile_size, BLUE);
		}
	}
} // namespace core
