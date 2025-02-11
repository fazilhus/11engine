#include "path_app.h"


#include "raylib.h"
#include <iostream>
#include <filesystem>

#include "util.h"
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

		m_map = new map(std::filesystem::absolute("./path/res/Map1.txt"));
	}

	void app::deinit() {
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
		ClearBackground(DARKGRAY);

		EndDrawing();
	}

} // namespace core
