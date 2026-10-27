#pragma once

#include <string>
#include <enet/enet.h>

class Client {
public:
    static int init();
    static int connect(std::string address, int port);
    static int mainLoop();
    static void disconnect();
    static void sendPacket(std::string data);
private:
    static ENetHost* client;
    static ENetAddress address;
    static ENetEvent event;
    static ENetPeer* peer;
};
