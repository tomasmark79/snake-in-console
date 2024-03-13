#pragma once
#include <iostream>
#include <string>
#include "enet\enet.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

class Network
{

    ENetHost* server;
    ENetHost* client;
    ENetPeer* peer;
    ENetEvent event;
    ENetAddress address;

    bool isServerActive;

    string hostName;

    int port;
    int clients;
    int channels;
    int amountIn;
    int amountOut;
    int outConnections;

public:
    Network();
    Network (Network& network);
    Network operator= (Network& network);
    virtual ~Network();

    int initENet();

    int initServer(string hostName,
                   int port,
                   int clients,
                   int channels,
                   int amountIn,
                   int amountOut);

    int initClient(string hostName,
                   int port,
                   int outConnections,
                   int channels,
                   int amountIn,
                   int amountOut);

    int connectToHost();

    int sendPacketToHost();

    int hostService();


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







};
