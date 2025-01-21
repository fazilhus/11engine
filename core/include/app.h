#pragma once

#include "entity.h"

namespace core {

	class fsm;

	class app {
	private:
		static app* s_instance;
		bool is_running;

		fsm* m_fsm;

		human* m_human;

		float timer;
		float timer_max;

	public:
		app();
		virtual ~app();

		void run();

	private:
		void init();
		void deinit();
		void update();
		void render();
	};

} // namespace core
