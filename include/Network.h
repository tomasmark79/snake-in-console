#pragma once
#include <iostream>
#include <string>
#include <cstdint>
#include "enet\enet.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

class Network
{
    bool    isNetworkActive;
    bool    isServerActive;

    ENetHost*   server;
    ENetPeer*   peerServer;

    ENetHost*   client;
    ENetPeer*   peerClient;

    ENetAddress address;
    ENetEvent   event;

    string hostName;
    int port;
    int clients;
    int channels;
    int amountIn;
    int amountOut;
    int outConnections;

    char stream[256];
public:
    Network() :
        isNetworkActive(false), server(nullptr), client(nullptr)
    {};

    ~Network()
    {
        if (server != nullptr)
            enet_host_destroy(server);
        if (client != nullptr)
            enet_host_destroy(client);
    };

    Network (Network& network);
    Network operator= (Network& network);

    int initENet()
    {
        return enet_initialize();
    };

    // server side
    int initServer();
    int hostService();

    // client side
    int initClient();
    int hostServiceOnClient();


    int listenForNewClient();

    int connectToServer();

    // independent
    int sendPacketToPeer(string strPacket);
    int sendPacketToPeerClient(string strPacket);

    string getHostName() const
    {
        return this->hostName;
    }
    void setHostName(string hostName)
    {
        this->hostName = hostName;
    }
    int getPort() const
    {
        return this->port;
    }
    void setPort(int port)
    {
        this->port = port;
    }
    int getClients() const
    {
        return this->clients;
    }
    void setClients(int clients)
    {
        this->clients = clients;
    }
    int getChannels() const
    {
        return this->channels;
    }
    void setChannels(int channels)
    {
        this->channels = channels;
    }
    int getAmountIn() const
    {
        return this->amountIn;
    }
    void setAmountIn(int amountIn)
    {
        this->amountIn = amountIn;
    }
    int getAmountOut() const
    {
        return this->amountOut;
    }
    void setAmountOut(int amountOut)
    {
        this->amountOut = amountOut;
    }
    int getOutConnections() const
    {
        return this->outConnections;
    }
    void setOutConnections(int outConnections)
    {
        this->outConnections = outConnections;
    }
    bool getIsServerActive() const
    {
        return this->isServerActive;
    }
    void setIsServerActive(bool isServerActive)
    {
        this->isServerActive = isServerActive;
    }
    bool getIsNetworkActive() const
    {
        return this->isNetworkActive;
    }
    void setIsNetworkActive(bool isNetworkActive)
    {
        this->isNetworkActive = isNetworkActive;
    }








};
