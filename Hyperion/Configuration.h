#pragma once
#include "toml.hpp"
#define LOGURU_WITH_STREAMS 1
#include "loguru.hpp"

#include <string>

const std::string CONFIG_PATH = "config.toml";

class Configuration
{
private:
	Configuration() = default;
	~Configuration() = default;
	Configuration(const Configuration&) = delete;
	Configuration operator&(const Configuration&) = delete;
public:
	static Configuration& getInstance()
	{
		static Configuration instance;
		return instance;
	}

	void load();

	int getWindowWidth();
	int getWindowHeight();
private:

	int windowWidth_, windowHeight_;
};
