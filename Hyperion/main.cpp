#include "GameWindow.h"

#include <iostream>

int main() {
    try {
        Configuration::getInstance().load();
		GameWindow app;
    }
    catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
