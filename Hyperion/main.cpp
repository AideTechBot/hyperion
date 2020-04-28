#include "GameWindow.h"
#include "Configuration.h"

#define LOGURU_WITH_STREAMS 1
#include "loguru.cpp"

int main(int argc, char* argv[]) {
    try {
        loguru::init(argc, argv);

        LOG_S(INFO) << "Starting Hyperion...";
    	
        Configuration::getInstance().load();
		GameWindow app;
    }
    catch (const std::exception & e) {
        LOG_F(ERROR, e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
