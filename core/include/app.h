#pragma once

#include "entity.h"

namespace core {

	class app {
	private:
		static app* s_instance;

		human* m_human;

		float timer;

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
