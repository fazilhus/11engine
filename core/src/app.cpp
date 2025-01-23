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
		m_timer_manager = new timer_manager();
		m_entity_manager = new entity_manager();
		m_message_sender = new message_sender();

		m_entity_manager->add_entity(std::make_unique<human>(0, "Bob"));
		m_entity_manager->add_entity(std::make_unique<human>(1, "Alice"));
		m_entity_manager->add_entity(std::make_unique<human>(2, "Clark"));
		m_entity_manager->add_entity(std::make_unique<human>(3, "Diana"));

		m_button = new ui::button("Pause", Vector2{ 1000, 10 }, 20);
		m_slider = new ui::slider(1.0f / 60.0f, 2.0f, Vector2{ 540, 600 }, Vector2{ 200, 20 }, 10);
	}

	void app::deinit() {
		delete m_fsm;
		delete m_timer_manager;
		delete m_entity_manager;
		delete m_message_sender;

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

			std::cout << std::endl;
			m_timer_manager->update();
			m_entity_manager->update();
		}
	}

	void app::render() {
		BeginDrawing();
		ClearBackground(DARKGRAY);

		DrawText(("Tickrate: " + std::to_string(1.0f / m_slider->value())).c_str(), 10, 10, 20, WHITE);
		
		draw_humans();

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

	void app::draw_humans() const {
		int i = 0;
		for (const auto& e : entity_manager::instance()->entities()) {
			int x = 10;
			int y = 40;

			if (i == 1) y += 280;
			if (i == 2) x += 400;
			if (i == 3) {
				x += 400; y += 280;
			}

			auto h = dynamic_cast<human*>(e.get());
			if (!h) continue;

			draw_human(h, x, y);

			i++;
		}
	}

	void app::draw_human(const human* h, int x, int y) const {
		DrawText(("Name: " + h->name()).c_str(), x, y, 20, WHITE);
		DrawText(("State: " + util::str(h->m_fsm_state)).c_str(), x, y + 30, 20, WHITE);
		DrawText(("Location: " + util::str(h->m_location)).c_str(), x, y + 60, 20, WHITE);
		DrawText(("Money: " + h->m_money.str()).c_str(), x, y + 100, 20, WHITE);
		DrawText(("Hunger: " + h->m_hunger.str()).c_str(), x, y + 130, 20, WHITE);
		DrawText(("Thirst: " + h->m_thirst.str()).c_str(), x, y + 160, 20, WHITE);
		DrawText(("Fatigue: " + h->m_fatigue.str()).c_str(), x, y + 190, 20, WHITE);
		DrawText(("Loneliness: " + h->m_loneliness.str()).c_str(), x, y + 220, 20, WHITE);
	}

} // namespace core
