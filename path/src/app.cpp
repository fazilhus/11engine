#include "app.h"

#include "raylib.h"
#include <string>

#include "util.h"

namespace core {

	app* app::s_instance = nullptr;

	app::app() {
		InitWindow(1280, 720, "11Engine: Pathfinding");
		SetTargetFPS(60);

		s_instance = this;

		is_running = true;
		is_paused = true;

		timer = 0;
		timer_max = 0.01f;
		cycles = 0;
	}

	app::~app() {
		CloseWindow();
	}

	void app::run() {
		init();

		while (!WindowShouldClose()) {
			update_ui();

			if (!is_paused) {
				update();
			}

			if (cycles >= 1728000) { // roughly 8 hours
				is_paused = true;
			}

			render();
		}

		deinit();
	}

	void app::init() {
		util::init_random();
	}

	void app::deinit() {
	}

	void app::update_ui() {
	}

	void app::update() {
		timer += GetFrameTime();
		
		if (timer >= 0.5f) {
			timer = 0;
			cycles++;
		}
	}

	void app::render() {
		BeginDrawing();
		ClearBackground(DARKGRAY);

		EndDrawing();
	}

} // namespace core
