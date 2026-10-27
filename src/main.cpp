#define ENET_IMPLEMENTATION
#include <enet/enet.h>
#include <iostream>

#include "Client.hpp"
#include "Server.hpp"

int main(int argc, char** argv) {
    std::cout << argv[1] << "a\n";

    if (std::string(argv[1]) == "client") {
	std::cout << "qdfsrfsdfs\n";
	Client::init();
	Client::connect(argv[2], atoi(argv[3]));
	Client::mainLoop();
	Client::disconnect();
    } else {
	Server::init();
	Server::mainLoop();
	Server::deinit();
    }

    enet_deinitialize();
    return 0;
}
