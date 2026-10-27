#include <enet/enet.h>

class Server {
public:
    static int init();
    static int mainLoop();
    static void deinit();
private:
    static int maxClients;
    static ENetHost* server;
    static ENetAddress address;
    static ENetEvent event;
};
