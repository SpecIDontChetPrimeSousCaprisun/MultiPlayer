#include "Client.hpp"
#include "Server.hpp"
#include "Window.hpp"

int main(int argc, char** argv) {
    if (Window::init() > 0) return 1;
    Window::mainLoop();

    /*if (argc < 2) {
	Server::init();
	Server::mainLoop();
	Server::deinit();
    } else {
	Client::init();
	Client::connect(argv[1], atoi(argv[2]));
	Client::mainLoop();
	Client::disconnect();
    }*/

    return 0;
}
