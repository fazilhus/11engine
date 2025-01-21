#include "app.h"

#include "raylib.h"

#include "state.h"

namespace core {

	app* app::s_instance = nullptr;

	app::app() {
		InitWindow(1280, 720, "11Engine");
		SetTargetFPS(60);
		s_instance = this;
		timer = 0;
	}

	app::~app() {
		CloseWindow();
	}

	void app::run() {
		init();

		while (!WindowShouldClose()) {
			update();

			render();
		}

		deinit();
	}

	void app::init() {
		m_human = new human(0);
		m_human->change_state(new working());
	}

	void app::deinit() {
		delete m_human;
	}

	void app::update() {
		timer += GetFrameTime();
		if (timer >= 5) {
			timer = 0;
			m_human->update();
		}
	}

	void app::render() {
		BeginDrawing();
		ClearBackground(DARKGRAY);
		EndDrawing();
	}

} // namespace core
