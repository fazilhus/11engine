#include "fsm_app.h"

#include "raylib.h"
#include <string>

#include "state_provider.h"
#include "timer.h"
#include "hstate.h"
#include "hentity.h"
#include "util.h"
#include "enum.h"

namespace core {

	app* app::s_instance = nullptr;

	app::app() {
		InitWindow(1280, 720, "11Engine: FSM");
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

		while (!WindowShouldClose() && !should_quit()) {
			update_ui();

			if (!m_is_paused) {
				update();
			}

			if (timer_manager::instance()->clock() >= 1728000) { // roughly 8 hours
				m_is_paused = true;
			}

			render();
		}

		deinit();
	}

	void app::init() {
		util::init_random();

		m_fsm = new state_provider();
		m_fsm->set_global_state<global_state>();
		m_fsm->set_state<state>();
		m_timer_manager = new timer_manager();
		m_entity_manager = new entity_manager();
		m_message_dispatch = new message_dispatcher();
		m_graph = new graph(loc_type_num);

#ifdef DEBUG
		for (int i = 0; i < 4; ++i) {
#else
		for (int i = 0; i < 1000; ++i) {
#endif
			m_entity_manager->add_entity(std::make_unique<human>(i, std::to_string(i)));
		}

		m_button = new ui::button("Pause", Vector2{ 1000, 10 }, 20);
		m_slider = new ui::slider(1.0f / 60.0f, 2.0f, Vector2{ 540, 600 }, Vector2{ 200, 20 }, 10);
	}

	void app::deinit() {
		delete m_fsm;
		delete m_timer_manager;
		delete m_entity_manager;
		delete m_message_dispatch;
		delete m_graph;

		delete m_button;
		delete m_slider;
	}

	void app::update_ui() {
		m_button->update();
		m_slider->update();

		if (m_button->is_pressed()) {
			m_is_paused = !m_is_paused;
		}
	}

	void app::update() {
		m_timer += GetFrameTime();
		
		if (m_timer >= m_slider->value()) {
			m_timer = 0;

			std::cout << std::endl;
			m_timer_manager->update();
			m_message_dispatch->update();
			m_entity_manager->update();

		}
	}

	void app::render() {
		BeginDrawing();
		ClearBackground(DARKGRAY);

		DrawText(("Tickrate: " + std::to_string(1.0f / m_slider->value())).c_str(), 10, 10, 20, WHITE);
		DrawText(("Framerate: " + std::to_string(GetFrameTime())).c_str(), 300, 10, 20, WHITE);
		DrawText(("Total Alive: " + std::to_string(m_entity_manager->instance()->entities().size())).c_str(), 600, 10, 20, WHITE);
		
		draw_humans();

		m_button->draw();
		m_slider->draw();

		DrawText(("Cycles: " + std::to_string(timer_manager::instance()->clock())).c_str(), 900, 600, 20, WHITE);

		if (m_is_paused) {
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
			if (i == 4) break;
		}
	}

	void app::draw_human(const human* h, int x, int y) const {
		DrawText(("Name: " + h->name()).c_str(), x, y, 20, WHITE);
		DrawText(("State: " + util::state_to_str(h->curr_state())).c_str(), x, y + 30, 20, WHITE);
		DrawText(("Location: " + util::loc_to_str(h->m_location)).c_str(), x, y + 60, 20, WHITE);
		DrawText(("Money: " + h->m_money.str()).c_str(), x, y + 100, 20, WHITE);
		DrawText(("Hunger: " + h->m_hunger.str()).c_str(), x, y + 130, 20, WHITE);
		DrawText(("Thirst: " + h->m_thirst.str()).c_str(), x, y + 160, 20, WHITE);
		DrawText(("Fatigue: " + h->m_fatigue.str()).c_str(), x, y + 190, 20, WHITE);
		DrawText(("Loneliness: " + h->m_loneliness.str()).c_str(), x, y + 220, 20, WHITE);
	}

} // namespace core
