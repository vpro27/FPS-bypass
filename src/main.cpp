#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>
#include <chrono>
#include <thread>

using namespace geode::prelude;

static double targetInterval() {
	auto fps = Mod::get()->getSettingValue<int64_t>("fps");
	if (fps < 1) fps = 60;
	return 1.0 / static_cast<double>(fps);
}

class $modify(FPSDirector, CCDirector) {
	void drawScene() {
		using clock = std::chrono::steady_clock;
		static auto last = clock::now();
		auto interval = std::chrono::duration<double>(targetInterval());
		auto elapsed = clock::now() - last;
		if (elapsed < interval) {
			std::this_thread::sleep_for(interval - elapsed);
		}
		last = clock::now();
		CCDirector::drawScene();
	}
};
