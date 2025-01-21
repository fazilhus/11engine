#pragma once

#include "entity.h"
#include "button.h"

namespace core {

	class fsm;

	class app {
	private:
		static app* s_instance;
		bool is_running;
		bool is_paused;

		fsm* m_fsm;

		human* m_human;

		ui::button* m_button;

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
	};

} // namespace core
