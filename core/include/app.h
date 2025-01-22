#pragma once

#include "entity.h"
#include "fsm.h"

#include "button.h"
#include "slider.h"

namespace core {

	class app {
	private:
		static app* s_instance;
		bool is_running;
		bool is_paused;

		fsm* m_fsm;
		entity_manager* m_entity_manager;

		ui::button* m_button;
		ui::slider* m_slider;

		float timer;
		float timer_max;

	public:
		app();
		virtual ~app();

		void run();

	private:
		void init();
		void deinit();
		void update_ui();
		void update();
		void render();

		bool should_quit();
	};

} // namespace core
