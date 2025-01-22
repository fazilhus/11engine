#include "app.h"

#include "raylib.h"
#include <string>

#include "fsm.h"
#include "timer.h"
#include "state.h"
#include "util.h"

namespace core {

	app* app::s_instance = nullptr;

	app::app() {
		InitWindow(1280, 720, "11Engine");
		SetTargetFPS(60);

		s_instance = this;

		is_running = true;
		is_paused = true;

		timer = 0;
		timer_max = 0.01f;
	}

	app::~app() {
		CloseWindow();
	}

	void app::run() {
		init();

		while (!WindowShouldClose() && !should_quit()) {
			update_ui();

			if (!is_paused) {
				update();
			}

			render();
		}

		deinit();
	}

	void app::init() {
		util::init_random();

		m_fsm = new fsm();
		m_entity_manager = new entity_manager();

		m_entity_manager->add_entity(std::make_unique<human>(0, "Bob"));
		m_entity_manager->add_entity(std::make_unique<human>(0, "Alice"));
		m_entity_manager->add_entity(std::make_unique<human>(0, "Clark"));
		m_entity_manager->add_entity(std::make_unique<human>(0, "Diana"));

		m_button = new ui::button("Pause", Vector2{ 1000, 10 }, 20);
		m_slider = new ui::slider(1.0f / 60.0f, 2.0f, Vector2{ 540, 600 }, Vector2{ 200, 20 }, 10);
	}

	void app::deinit() {
		delete m_fsm;
		delete m_entity_manager;

		delete m_button;
	}

	void app::update_ui() {
		m_button->update();
		m_slider->update();

		if (m_button->is_pressed()) {
			is_paused = !is_paused;
		}
	}

	void app::update() {
		timer += GetFrameTime();
		
		if (timer >= m_slider->value()) {
			timer = 0;
			m_entity_manager->update();

			// if (m_human->is_dead()) {
			// 	std::cout << "Human is dead :(" << std::endl;
			// 	std::cout << "Human lived for " << m_human->m_cycles << " cycles" << std::endl;
			// 	std::cout << "Wealth: " << m_human->m_money.str() << std::endl;
			// 	std::cout << "Hunger: " << m_human->m_hunger.str() << std::endl;
			// 	std::cout << "Thirst: " << m_human->m_thirst.str() << std::endl;
			// 	std::cout << "Fatigue: " << m_human->m_fatigue.str() << std::endl;
			// 	std::cout << "Loneliness: " << m_human->m_loneliness.str() << std::endl;
			// 	is_running = false;
			// }
		}
	}

	void app::render() {
		BeginDrawing();
		ClearBackground(DARKGRAY);

		DrawText(("Tickrate: " + std::to_string(1.0f / m_slider->value())).c_str(), 10, 10, 20, WHITE);
		// DrawText(("State: " + util::str(m_human->m_fsm_state)).c_str(), 10, 40, 20, WHITE);
		// DrawText(("Location: " + util::str(m_human->m_location)).c_str(), 10, 70, 20, WHITE);
		// DrawText(("Money: " + m_human->m_money.str()).c_str(), 10, 100, 20, WHITE);
		// DrawText(("Hunger: " + m_human->m_hunger.str()).c_str(), 10, 130, 20, WHITE);
		// DrawText(("Thirst: " + m_human->m_thirst.str()).c_str(), 10, 160, 20, WHITE);
		// DrawText(("Fatigue: " + m_human->m_fatigue.str()).c_str(), 10, 190, 20, WHITE);
		// DrawText(("Loneliness: " + m_human->m_loneliness.str()).c_str(), 10, 220, 20, WHITE);

		m_button->draw();
		m_slider->draw();

		if (is_paused) {
			Vector2 label_size = MeasureTextEx(GetFontDefault(), "PAUSED", 30, 1);
			DrawText("PAUSED", 640 - static_cast<int>(label_size.x) / 2, 360 - static_cast<int>(label_size.y) / 2, 30, RED);
		}

		EndDrawing();
	}

	bool app::should_quit() {
		return entity_manager::instance()->entities().empty();
	}

} // namespace core
