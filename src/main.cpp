#include <Geode/Geode.hpp>
#include <Geode/modify/CCApplication.hpp>

using namespace geode::prelude;

static void applyFPS() {
	auto fps = Mod::get()->getSettingValue<int64_t>("fps");
	if (fps < 1) fps = 60;
	CCDirector::get()->setAnimationInterval(1.0 / static_cast<double>(fps));
}

class $modify(FPSApplication, CCApplication) {
	void setAnimationInterval(double interval) {
		auto fps = Mod::get()->getSettingValue<int64_t>("fps");
		if (fps < 1) fps = 60;
		CCApplication::setAnimationInterval(1.0 / static_cast<double>(fps));
	}
};

$execute {
	listenForSettingChanges<int64_t>("fps", [](int64_t) {
		applyFPS();
	});
}

$on_mod(Loaded) {
	applyFPS();
}
