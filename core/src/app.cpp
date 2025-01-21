#include "app.h"

#include "raylib.h"
#include <string>

#include "fsm.h"
#include "state.h"
#include "util.h"

namespace core {

	app* app::s_instance = nullptr;

	app::app() {
		InitWindow(1280, 720, "11Engine");
		SetTargetFPS(60);
		s_instance = this;
		is_running = true;
		timer = 0;
		timer_max = 5;
	}

	app::~app() {
		CloseWindow();
	}

	void app::run() {
		init();

		while (!WindowShouldClose() && is_running) {
			update();

			render();
		}

		deinit();
	}

	void app::init() {
		m_fsm = new fsm();
		m_human = new human(0);
		m_human->change_state(fsm_state::working);
	}

	void app::deinit() {
		delete m_fsm;
		delete m_human;
	}

	void app::update() {
		timer += GetFrameTime();
		if (timer >= timer_max) {
			timer = 0;
			m_human->update();

			if (m_human->is_dead()) {
				std::cout << "Human is dead :(" << std::endl;
				std::cout << "Human lived for " << m_human->m_cycles << " cycles" << std::endl;
				is_running = false;
			}
		}
	}

	void app::render() {
		BeginDrawing();
		ClearBackground(DARKGRAY);

		DrawText(util::str(m_human->m_location).c_str(), 10, 10, 20, WHITE);
		DrawText(util::str(m_human->m_fsm_state).c_str(), 10, 40, 20, WHITE);
		DrawText(m_human->m_money.str().c_str(), 10, 70, 20, WHITE);
		DrawText(m_human->m_hunger.str().c_str(), 10, 100, 20, WHITE);
		DrawText(m_human->m_thirst.str().c_str(), 10, 130, 20, WHITE);
		DrawText(m_human->m_fatigue.str().c_str(), 10, 160, 20, WHITE);
		DrawText(m_human->m_loneliness.str().c_str(), 10, 190, 20, WHITE);

		EndDrawing();
	}

} // namespace core
