#include "Configuration.h"


void Configuration::load()
{
	LOG_S(INFO) << "Loading configuration file at: " << CONFIG_PATH;
	
	const auto data = toml::parse(CONFIG_PATH);

	const auto& window = toml::find(data, "window");

	const auto& resolution = toml::find(window, "resolution");
	
	windowWidth_ = toml::find<int>(resolution, "width");
	windowHeight_ = toml::find<int>(resolution, "height");
}

int Configuration::getWindowWidth()
{
	return windowWidth_;
}

int Configuration::getWindowHeight()
{
	return windowHeight_;
}
