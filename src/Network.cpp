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
    /* enet_address_set_host (& address, "x.x.x.x"); */
    enet_address_set_host(&address, const_cast<char*>(hostName.c_str()));
    address.port = port;

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
int Network::connectToServer()
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

int Network::listenForNewClient()
{
    while (enet_host_service (server, &event, 0) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            sprintf ((char*)stream, "A new client connected from %x:%u.\n",
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


    int Network::hostService()
    {
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service (server, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                sprintf ((char*)stream, "A new client connected from %x:%u.\n",
                         event.peer -> address.host,
                         event.peer -> address.port);
                cout << stream << endl;
                /* Store any relevant client information here. */
                event.peer -> data = (void*)"Client";
                peerClient = event.peer;

                // break;
                return 0;
            case ENET_EVENT_TYPE_RECEIVE:
                //sprintf ((char*)stream, "A packet of length %u containing %s was received from %s on channel %u.\n",
                sprintf ((char*)stream, "l%u s %s from %s ch. %u.\n",
                         event.packet -> dataLength,
                         event.packet -> data,
                         event.peer -> data,
                         event.channelID);
                cout << stream << endl;
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy (event.packet);
                return 1;

            case ENET_EVENT_TYPE_DISCONNECT:
                sprintf ((char*)stream, "%s disconnected.\n", (void*)event.peer -> data);
                cout << stream << endl;
                /* Reset the peer's client information. */
                event.peer -> data = NULL;
                return 2;
            }
        }
        return 3;
    }

    int Network::hostServiceOnClient()
    {
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service (client, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                sprintf ((char*)stream, "Tohle se nikdy nestane - A new client connected from %x:%u.\n",
                         event.peer -> address.host,
                         event.peer -> address.port);
                cout << stream << endl;
                /* Store any relevant client information here. */
                event.peer -> data = (void*)"Client information";
                // peerClient = event.peer;
                // break;
                return 0;
            case ENET_EVENT_TYPE_RECEIVE:
                sprintf ((char*)stream, "l%u s %s from %s ch. %u.\n",
                         event.packet -> dataLength,
                         event.packet -> data,
                         event.peer -> data,
                         event.channelID);
                cout << stream << endl;
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy (event.packet);
                return 1;

            case ENET_EVENT_TYPE_DISCONNECT:
                sprintf ((char*)stream, "%s disconnected.\n", (void*)event.peer -> data);
                cout << stream << endl;
                /* Reset the peer's client information. */
                event.peer -> data = NULL;
                return 2;
            }
        }
        return 3;
    }

    int Network::sendPacketToPeer(string strPacket)
    {
        /* Create a reliable packet of size 7 containing "packet\0" */
//    ENetPacket * packet = enet_packet_create ("packet",
//                          strlen ("packet") + 1,
//                          ENET_PACKET_FLAG_RELIABLE);

        ENetPacket * packet = enet_packet_create (strPacket.c_str(),
                              strPacket.length() + 1,
                              ENET_PACKET_FLAG_RELIABLE);
        // peer.incomingPeerID
        /* Extend the packet so and append the string "foo", so it now */
        /* contains "packetfoo\0"                                      */
        //enet_packet_resize (packet, strlen ("packetfoo") + 1);
        //strcpy (reinterpret_cast<char*>(&packet->data [strlen ("packet")]), "foo");
        /* Send the packet to the peer over channel id 0. */
        /* One could also broadcast the packet by         */
        /* enet_host_broadcast (host, 0, packet);         */
        enet_peer_send (peerServer, 0, packet);
        return 0;
    }

    int Network::sendPacketToPeerClient(string strPacket)
    {
        /* Create a reliable packet of size 7 containing "packet\0" */
//    ENetPacket * packet = enet_packet_create ("packet",
//                          strlen ("packet") + 1,
//                          ENET_PACKET_FLAG_RELIABLE);

        ENetPacket * packet = enet_packet_create (strPacket.c_str(),
                              strPacket.length() + 1,
                              ENET_PACKET_FLAG_RELIABLE);
        // peer.incomingPeerID
        /* Extend the packet so and append the string "foo", so it now */
        /* contains "packetfoo\0"                                      */
        //enet_packet_resize (packet, strlen ("packetfoo") + 1);
        //strcpy (reinterpret_cast<char*>(&packet->data [strlen ("packet")]), "foo");
        /* Send the packet to the peer over channel id 0. */
        /* One could also broadcast the packet by         */
        /* enet_host_broadcast (host, 0, packet);         */
        enet_peer_send (peerClient, 0, packet);
        return 0;
    }
