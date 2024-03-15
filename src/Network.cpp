#include "Network.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int Network::initServer()
{
    if (!isNetworkActive)
        return 0;

    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */

    enet_address_set_host(&address, const_cast<char*>(hostName.c_str()));
    address.port = port;
    server = enet_host_create (&address  /* the address and port to bind the server host to */,
                               clients   /* allow up to 32 clients and/or outgoing connections */,
                               channels  /* allow up to 2 channels to be used, 0 and 1 */,
                               amountIn  /* assume any amount of incoming bandwidth */,
                               amountOut /* assume any amount of outgoing bandwidth */);
    if (server == nullptr)
    {
        cerr << "An error occurred while trying to create an ENet server host." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        cout << "ENet server started sucessfuly" << endl;
    }
    return 0;
}

int Network::initClient()
{
    /* A specific host address can be specified by   */
    enet_address_set_host(&address, const_cast<char*>(hostName.c_str()));
    address.port = port;
    /* enet_address_set_host (& address, "x.x.x.x"); */

    client = enet_host_create (NULL /* create a client host */,
                               outConnections /* only allow 1 outgoing connection */,
                               channels /* allow up 2 channels to be used, 0 and 1 */,
                               amountIn /* assume any amount of incoming bandwidth */,
                               amountOut /* assume any amount of outgoing bandwidth */);
    if (client == nullptr)
    {
        cerr << "An error occurred while trying to create an ENet client host." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        cout << "ENet client started sucessfuly" << endl;
    }
    return 0;
}


//! \brief Client is trying to connect to a peer (server host)
//!
//! \param
//! \param
//! \return 0 connected, 1 no available peers, 2 connection failed
//!
//!
int Network::clientIsConnectingServer()
{
    /* Initiate the connection, allocating the two channels 0 and 1. */
    peerServer = enet_host_connect (client, &address, 2, 0);
    if (peerServer == NULL)
    {
        fprintf (stderr,
                 "No available peers for initiating an ENet connection.\n");
        return 1;
    }

    /* Wait up to 10 seconds for the connection attempt to succeed. */
    if (enet_host_service (client, & event, 10000) > 0 &&
            event.type == ENET_EVENT_TYPE_CONNECT)
    {
        cout << "Connection to " << this->hostName << ":" << this->port << " succeeded." << endl;
        peerServer = event.peer;
        event.peer -> data = (void*)"Server";
    }
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset (peerServer);
        cout << "Connection to " << this->hostName << ":" << this->port << " failed." << endl;
        return 2;
    }
    return 0;
}

//! \brief Server is trying to listen client peer connection event
//!
//! \param
//! \param
//! \return 0 registered, 1 no client detected
//!
//!
int Network::serverIsRegisteringClient()
{
    while (enet_host_service (server, &event, 10000) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            sprintf ((char*)stream, "A new client registered from %x:%u.\n",
                     event.peer -> address.host,
                     event.peer -> address.port);
            cout << stream << endl;

            /* Store any relevant client information here. */
            peerClient = event.peer;
            event.peer -> data = (void*)"Client";
            return 0;
        }
        return 1;
    }
}











//! \brief event handler at Server side
//!
//! \param
//! \param
//! \return 0 received data, 1 disconnected, 2 no event
//!
//!
int Network::serverHostService()
{
    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service (server, &event, 0) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            sprintf ((char*)stream, "len %u s %s from %s ch. %u.\n",
                     event.packet -> dataLength,
                     event.packet -> data,
                     event.peer -> data,
                     event.channelID);
            cout << stream << endl;

            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy (event.packet);
            return 0;

        case ENET_EVENT_TYPE_DISCONNECT:
            sprintf ((char*)stream, "%s disconnected.\n", (void*)event.peer -> data);
            cout << stream << endl;
            /* Reset the peer's client information. */
            event.peer -> data = NULL;
            return 1;
        }
    }
    return 2;
}

//! \brief event handler at Client side
//!
//! \param
//! \param
//! \return 0 received data, 1 disconnected, 2 no event
//!
//!
int Network::clientHostService()
{
    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service (client, &event, 0) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            sprintf ((char*)stream, "len %u s %s from %s ch. %u.\n",
                     event.packet -> dataLength,
                     event.packet -> data,
                     event.peer -> data,
                     event.channelID);
            cout << stream << endl;
            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy (event.packet);
            return 0;

        case ENET_EVENT_TYPE_DISCONNECT:
            sprintf ((char*)stream, "%s disconnected.\n", (void*)event.peer -> data);
            cout << stream << endl;
            /* Reset the peer's client information. */
            event.peer -> data = NULL;
            return 1;
        }
    }
    return 2;
}

//! send int
int Network::sendPacketToClient(int value)
{
    ENetPacket * packet = enet_packet_create (&value,
                          sizeof(int) + 1,
                          ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (peerClient, 0, packet);
    return 0;
}

////! send string
//int Network::sendPacketToClient(string strPacket)
//{
//    ENetPacket * packet = enet_packet_create (strPacket.c_str(),
//                          strPacket.length() + 1,
//                          ENET_PACKET_FLAG_RELIABLE);
//    enet_peer_send (peerClient, 0, packet);
//    return 0;
//}
//
////! send vector of ints
//int Network::sendPacketToClient(vector<int> serialized)
//{
//    /* Create a reliable packet of size 7 containing "packet\0" */
//    ENetPacket * packet = enet_packet_create (&serialized[0],
//                          serialized.size() * sizeof(int),
//                          ENET_PACKET_FLAG_RELIABLE);
//    enet_peer_send (peerClient, 0, packet);
//    return 0;
//}

//! send int
int Network::sendPacketToServer(int value)
{
    ENetPacket * packet = enet_packet_create (&value,
                          sizeof(int) + 1,
                          ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (peerServer, 0, packet);
    return 0;
}

////! send string
//int Network::sendPacketToServer(string strPacket)
//{
//    ENetPacket * packet = enet_packet_create (strPacket.c_str(),
//                          strPacket.length() + 1,
//                          ENET_PACKET_FLAG_RELIABLE);
//    enet_peer_send (peerServer, 0, packet);
//    return 0;
//}
//
////! send vector of ints
//int Network::sendPacketToServer(vector<int> serialized)
//{
//    /* Create a reliable packet of size 7 containing "packet\0" */
//    ENetPacket * packet = enet_packet_create (&serialized[0],
//                          serialized.size() * sizeof(int),
//                          ENET_PACKET_FLAG_RELIABLE);
//    enet_peer_send (peerServer, 0, packet);
//    return 0;
//}

////! receive vector of ints from server
//vector<int> Network::receivePacketFromServer()
//{
//    vector<int> receivedData{0};
//    /* Wait up to 1000 milliseconds for an event. */
//    while (enet_host_service (client, &event, 0) > 0)
//    {
//        switch (event.type)
//        {
//        case ENET_EVENT_TYPE_RECEIVE:
//            sprintf ((char*)stream, "received len %u s %s from %s ch. %u.\n",
//                     event.packet -> dataLength,
//                     event.packet -> data,
//                     event.peer -> data,
//                     event.channelID);
//            cout << stream << endl;
//
//            receivedData.reserve(event.packet -> dataLength);
//            receivedData = static_cast<vector<int>>(*event.packet->data);
//
//            /* Clean up the packet now that we're done using it. */
//            enet_packet_destroy (event.packet);
//            break;
//        case ENET_EVENT_TYPE_DISCONNECT:
//            sprintf ((char*)stream, "%s disconnected.\n", (void*)event.peer -> data);
//            cout << stream << endl;
//            /* Reset the peer's client information. */
//            event.peer -> data = NULL;
//            break;
//        }
//    }
//
//    return receivedData;
//}


//! receive int value
//! return 0 no data, -1 disconnected, >0 value received
int Network::receivePacketFromClient()
{
    int receivedValue = 0;
    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service (server, &event, 0) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            sprintf ((char*)stream, "len %u s %d from %s ch. %u.\n",
                     event.packet -> dataLength,
                     event.packet -> data,
                     event.peer -> data,
                     event.channelID);
            cout << stream << endl;

            receivedValue = static_cast<int>(*event.packet->data);

            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy (event.packet);
            return receivedValue;

        case ENET_EVENT_TYPE_DISCONNECT:
            sprintf ((char*)stream, "%s disconnected.\n", (void*)event.peer -> data);
            cout << stream << endl;
            /* Reset the peer's client information. */
            event.peer -> data = NULL;
            return -1;
        }
    }
    return 0;
}


   //! receive int value
//! return 0 no data, -1 disconnected, >0 value received
int Network::receivePacketFromServer()
{
    int receivedValue = 0;
    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service (client, &event, 0) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            sprintf ((char*)stream, "len %u Cmd %u from %s ch. %u.\n",
                     event.packet -> dataLength,
                     event.packet -> data,
                     event.peer -> data,
                     event.channelID);
            cout << stream << endl;

            receivedValue = static_cast<int>(*event.packet->data);

            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy (event.packet);
            return receivedValue;

        case ENET_EVENT_TYPE_DISCONNECT:
            sprintf ((char*)stream, "%s disconnected.\n", (void*)event.peer -> data);
            cout << stream << endl;
            /* Reset the peer's client information. */
            event.peer -> data = NULL;
            return -1;
        }
    }
    return 0;
}


////! receive vector of ints from server
//vector<int> Network::receivePacketFromClient()
//{
//    vector<int> receivedData{0};
//    /* Wait up to 1000 milliseconds for an event. */
//    while (enet_host_service (server, &event, 0) > 0)
//    {
//        switch (event.type)
//        {
//        case ENET_EVENT_TYPE_RECEIVE:
//            sprintf ((char*)stream, "len %u s %s from %s ch. %u.\n",
//                     event.packet -> dataLength,
//                     event.packet -> data,
//                     event.peer -> data,
//                     event.channelID);
//            cout << stream << endl;
//
//            receivedData.reserve(event.packet -> dataLength);
//            receivedData = static_cast<vector<int>>(*event.packet->data);
//
//            /* Clean up the packet now that we're done using it. */
//            enet_packet_destroy (event.packet);
//            break;
//        case ENET_EVENT_TYPE_DISCONNECT:
//            sprintf ((char*)stream, "%s disconnected.\n", (void*)event.peer -> data);
//            cout << stream << endl;
//            /* Reset the peer's client information. */
//            event.peer -> data = NULL;
//            break;
//        }
//    }
//
//    return receivedData;
//}


//int Network::clientHostService()
//{
//    /* Wait up to 1000 milliseconds for an event. */
//    while (enet_host_service (client, &event, 1000) > 0)
//    {
//        switch (event.type)
//        {
//        case ENET_EVENT_TYPE_RECEIVE:
//            sprintf ((char*)stream, "l%u s %s from %s ch. %u.\n",
//                     event.packet -> dataLength,
//                     event.packet -> data,
//                     event.peer -> data,
//                     event.channelID);
//            cout << stream << endl;
//            /* Clean up the packet now that we're done using it. */
//            enet_packet_destroy (event.packet);
//            return 0;
//
//        case ENET_EVENT_TYPE_DISCONNECT:
//            sprintf ((char*)stream, "%s disconnected.\n", (void*)event.peer -> data);
//            cout << stream << endl;
//            /* Reset the peer's client information. */
//            event.peer -> data = NULL;
//            return 1;
//        }
//    }
//    return 2;
//}
