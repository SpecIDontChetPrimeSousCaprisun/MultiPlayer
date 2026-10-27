#include <iostream>
#include "Server.hpp"

ENetHost* Server::server;
ENetAddress Server::address;
ENetEvent Server::event;

int Server::init() {
    if (enet_initialize() != 0) {
	std::cout << "Error while initializing enet\n";
	return 1;
    }
    
    atexit(enet_deinitialize);
    address.host = ENET_HOST_ANY;
    address.port = 7777;

    server = enet_host_create(&address, 5, 1, 0, 0);

    if (server == NULL) {
	std::cout << "Error while initializing server\n";
	return 1;
    }

    return 0;
}

int Server::mainLoop() {
    while (true) {
	while (enet_host_service(server, &event, 1000) > 0) {
	    switch(event.type) {
		case ENET_EVENT_TYPE_CONNECT:
		    //std::cout << "New connection from " + event.peer->address.host + ":" + event.peer->address.port + "\n";
		    std::cout << "New connection\n";
		    break;
		case ENET_EVENT_TYPE_RECEIVE:
		    std::cout << "A packet of len " 
			      << event.packet->dataLength 
			      << " containing " 
			      << event.packet->data
			      << " was received from "
			      << event.peer->data
			      << " on channel "
			      << event.channelID
			      << ".\n";
		    break;
		case ENET_EVENT_TYPE_DISCONNECT:
		    //std::cout << event.peer->address.host + ":" + event.peer->address.port + " disconnected\n";
		    std::cout << "disconnected\n";
		    break;
	    }
	}
    }

    return 0;
}

void Server::deinit() {
    enet_host_destroy(server);
}
