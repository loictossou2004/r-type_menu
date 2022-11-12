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

                int numberC =  0;
                ENetPeer *currentPeer;
                ENetPeer *peer_new;
                for (currentPeer = server -> peers; currentPeer < & server -> peers [server -> peerCount]; ++ currentPeer) {
                    if (currentPeer -> state != ENET_PEER_STATE_CONNECTED)
                        continue;
                    numberC++;
                }
                vector<ENetPeer*> VecPeer;
                for (currentPeer = server -> peers; currentPeer < & server -> peers [server -> peerCount]; ++ currentPeer) {
                    if (currentPeer -> state != ENET_PEER_STATE_CONNECTED)
                        continue;
                    peer_new = currentPeer;
                    std::string message_Send = "Players Connected: " + std::to_string(numberC);
                    ENetPacket *packet = enet_packet_create(message_Send.c_str(), message_Send.length(), ENET_PACKET_FLAG_RELIABLE);
                    VecPeer.push_back(peer_new);
                    enet_peer_send(currentPeer, 0, packet);
                }
                if (id_Client.size() == 0)
                    id_Client.insert(pair<int, ENetPeer*>(numberC, peer_new));
                else {
                    bool check = 0;
                    map<int, ENetPeer*>::iterator itr;
                    for (itr = id_Client.begin(); itr != id_Client.end(); ++itr)
                        if (itr->second == nullptr) {
                            check= true;
                            break;
                        }
                    if (check == true)
                        id_Client[itr->first] = VecPeer[itr->first-1];
                    else
                        id_Client.insert(pair<int, ENetPeer*>(id_Client.end()->first + 1, peer_new));
                }
                break;
            }
            else if (event.type == ENET_EVENT_TYPE_RECEIVE) {
                unsigned char *str = (unsigned char *) event.packet->data;
                const char* test = (const char*) str;
                string myData = (string) test;
                enet_packet_destroy(event.packet);
                if (strncmp(myData.c_str(), "Position", strlen("Position")) == 0) {
                    ENetPeer *currentPeer;
                    map<int, ENetPeer*>::iterator itr;
                    for (itr = id_Client.begin(); itr != id_Client.end(); ++itr)
                        if (itr->second == event.peer) {
                            break;
                        }
                    myData +=  "__" + to_string(itr->first);
                    //cout << myData << "\n";
                    for (currentPeer = server -> peers; currentPeer < & server -> peers [server -> peerCount]; ++ currentPeer) {
                        if (currentPeer -> state != ENET_PEER_STATE_CONNECTED || event.peer == currentPeer)
                            continue;
                        ENetPacket *packet = enet_packet_create(myData.c_str(), myData.length(), ENET_PACKET_FLAG_RELIABLE);
                        enet_peer_send(currentPeer, 0, packet);
                    }
                }
                break;
            }
            else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
                printf ("[508]: %x:%u disconnected\n",
                event.peer->address.host,
                event.peer->address.port);

                map<int, ENetPeer*>::iterator itr;
                for (itr = id_Client.begin(); itr != id_Client.end(); ++itr)
                    if (itr->second == event.peer)
                        break;
                id_Client[itr->first] = nullptr;
                for (itr = id_Client.begin(); itr != id_Client.end(); ++itr) {
                    cout << '\t' << itr->first << '\t' << itr->second
                        << '\n';
                }
                cout << endl;

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