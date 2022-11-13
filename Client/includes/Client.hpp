/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <cstdio>
#include <memory>
#include <iostream>
#include <string>
#include <iterator>
#include <filesystem>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <enet/enet.h>
#include <stdio.h>
#include <thread>

using namespace std;

class NetWorkClient {
    public:
        /**
         * @brief Construct a new Net Work Client object
         * 
         * @param port the port of ip address
         * @param addressName address ip to connect client 
         */
        NetWorkClient(int port, char const *addressName);
        /**
         * @brief Destroy the Net Work Client object
         * 
         */
        ~NetWorkClient();

        void Send_to_Client(char const *data) {
            ENetPacket *packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(peer, 0, packet);
        };

        /**
         * @brief initializes ENet globally. Must be called prior to using any functions in ENet.
         * 
         * @return int 0 for success or < 0 for failure
         */
        int enet_initialized() {
            return (enet_initialize());
        };

        /**
         * @brief Register a function to be called when `exit' is called.
         * 
         * @return int 
         */
        int call_exit() {
            return (atexit(enet_deinitialize));
        };

        /**
         * @brief Create a Client Host enet with number outgoing connection,
         * number channels to be used. 
         * 
         * @return ENetHost* 
         */
        ENetHost *create_Host() {
            return (enet_host_create(NULL, 1, 1, 0, 0));
        };

        /**
         * @brief Attempts to resolve the host named by the parameter hostName and sets
         * the host fieldin the address parameter if successful.
         * 
         * @return int 0 on success, 
         * < 0 on failure
         */
        int address_set_host_Client() {
            return (enet_address_set_host(&address, address_Name));
        };

        /**
         * @brief It accepts the address of a foreign host to connect to, and the number of channels that should be allocated for communication
         * If N channels are allocated for use, their channel ids will be numbered 0 through N-1.
         * 
         * @return ENetPeer* 
         */
        ENetPeer *connect_host_Client() {
            return (enet_host_connect(client, &address, 1, 0));
        };
        int Host_service(int timezone) {
            return (enet_host_service(client, &event, timezone));
        };
        void disconnect_peer() {
            return (enet_peer_disconnect(peer, 0));
        };
        ENetHost *get_CLient() {
            return (client);
        };
        int Connection_and_initialize();
        void MsgLoop ();
        void Client_LoopStart();

    private:
        ENetHost *client;
        ENetAddress address;
        ENetEvent event;
        ENetPeer *peer;
        char const *address_Name;

};

#endif /* !CLIENT_HPP_ */
