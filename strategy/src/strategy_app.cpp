#include "strategy_app.h"

#include "raylib.h"
#include <iostream>
#include <filesystem>
#include <chrono>

#include "util.h"
#include "enum.h"
#include "smap.h"


namespace core {

	app* app::s_instance = nullptr;

	app::app() {
		InitWindow(1920, 1080, "11Engine: Pathfinding");
		SetTargetFPS(60);

		s_instance = this;

		m_is_running = true;
		m_timer = 0.0f;

		m_map = nullptr;
	}

	app::~app() {
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
	}

	void app::deinit() {
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

		EndDrawing();
	}

} // namespace core
