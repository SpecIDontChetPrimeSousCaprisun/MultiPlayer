#include <iostream>
#include "Client.hpp"

ENetHost* Client::client;
ENetAddress Client::address;
ENetEvent Client::event;
ENetPeer* Client::peer;

int Client::init() {
    if (enet_initialize() != 0) {
	std::cout << "Error while initializing enet\n";
	return 1;
    }
    
    atexit(enet_deinitialize);
    client = enet_host_create(NULL, 1, 1, 0, 0);

    if (client == NULL) {
	std::cout << "Error while initializing clien\n";
	return 1;
    }

    return 0;
}

int Client::connect(std::string addr, int port) {
    address.port = port;
    enet_address_set_host(&address, addr.c_str());
    peer = enet_host_connect(client, &address, 1, 0);
    
    if (peer == NULL) {
	std::cout << "Error while connecting to peer\n";
	return 1;
    }

    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
	std::cout << "Connection success\n";
    } else {
	enet_peer_reset(peer);
	std::cout << "Connection failed\n";
	return 0;
    }

    return 0;
}

int Client::mainLoop() {
    while (enet_host_service(client, &event, 1000) > 0) {
	std::cout << "sefsdf\n";
	switch(event.type) {
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
	}
    }

    return 0;
}

void Client::disconnect() {
    enet_peer_disconnect(peer, 0);
    std::cout << "initiating disconnection\n";

    while (enet_host_service(client, &event, 3000) > 0) {
	switch(event.type) {
	    case ENET_EVENT_TYPE_RECEIVE:
		enet_packet_destroy(event.packet);
		break;
	    case ENET_EVENT_TYPE_DISCONNECT:
		std::cout << "Disconnection succeeded\n";
		break;
	}
    }
}
