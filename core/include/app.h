#pragma once

namespace core {

	class app {
	public:
		app();
		virtual ~app();

		void run();

	private:
		static app* s_instance;
	};

} // namespace core
