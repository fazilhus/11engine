#include "include/app.h"

#include "raylib.h"

namespace core {

	app* app::s_instance = nullptr;

	app::app() {
		InitWindow(1280, 720, "11Engine");
		SetTargetFPS(60);
		s_instance = this;
	}

	app::~app() {
		CloseWindow();
	}

	void app::run() {
		while (!WindowShouldClose()) {
			BeginDrawing();
			ClearBackground(DARKGRAY);
			EndDrawing();
		}
	}

} // namespace core
