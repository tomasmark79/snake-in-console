#include "Network.h"

Network::Network()
{

}

Network::~Network()
{

}

int Network::init()
{
    return enet_initialize();
}
