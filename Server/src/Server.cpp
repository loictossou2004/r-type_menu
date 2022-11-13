/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** Server
*/

#include "Server/includes/server.hpp"

NetWorkServer::NetWorkServer(int port, char const *HostName)
{
    address.host = ENET_HOST_ANY;
    address.port = port;
    Host_Name = HostName;
}

NetWorkServer::~NetWorkServer()
{
    Serv_Destroy_Host();
}

int NetWorkServer::initializeEnet()
{
    if (Initialize_enet_Server() != 0) {
        fprintf (stderr, "An error occurred while initializing ENet!\n");
        return 84;
    }
    atexit(enet_deinitialize);
    return (0);
}

int NetWorkServer::CreateHostEnet()
{
    server = Create_Host_Server();

    if (server == NULL) {
        fprintf (stderr, "An error occurred while trying to create an ENet server!\n");
        return 84;
    }
    return (0);
}

void NetWorkServer::SetHostEnet()
{
    Set_address_Host_Server();
}

void NetWorkServer::ManageHostEnet()
{
    while (true) {
        while(Host_Service_Server(1000) > 0) {
            if (event.type == ENET_EVENT_TYPE_CONNECT) {
                printf ("A new client connected from %x:%u.\n",
                event.peer->address.host,
                event.peer->address.port);
                break;
            }
            else if (event.type == ENET_EVENT_TYPE_RECEIVE) {
                printf ("A packet of length %lu containing %s was received from %x:%u on channel %u.\n",
                        event.packet -> dataLength,
                        event.packet -> data,
                        event.peer -> address.host,
                        event.peer -> address.port,
                        event.channelID);
                enet_packet_destroy(event.packet);
                break;
            }
            else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
                printf ("%x:%u disconnected\n",
                event.peer->address.host,
                event.peer->address.port);
                break;
            }
        }
    }
}

void NetWorkServer::RunServerEnet()
{
    initializeEnet();
    CreateHostEnet();
    SetHostEnet();
    ManageHostEnet();
}