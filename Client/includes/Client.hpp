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
#include <mutex>
#include <map>
#include <SFML/Audio.hpp>
#include <condition_variable>

using namespace std;

struct all_connexions
{
    int connected;
    std::mutex myMutex;
    std::condition_variable cv;
    std::map<int, sf::Vector2f> OtherPlayers;
};

/**
 * @brief Class for NetWork Client
 *
 */
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

        /**
         * @brief
         *
         * @param timezone
         * @return int
         */
        int Host_service(int timezone) {
            return (enet_host_service(client, &event, timezone));
        };

        /**
         * @brief Disconnect peer
         *
         */
        void disconnect_peer() {
            return (enet_peer_disconnect(peer, 0));
        };

        /**
         * @brief Get the CLient object
         *
         * @return ENetHost*
         */
        ENetHost *get_CLient() {
            return (client);
        };

        /**
         * @brief Get the Number Client object
         *
         * @return int
         */
        int getNumberClient(void) {
            return (ClientNumber);
        }
        /**
         * @brief Connection and intiliaziation of variables
         *
         * @return int
         */
        int Connection_and_initialize();

        /**
         * @brief loop to get Message
         *
         */
        void MsgLoop ();
        /**
         * @brief start Client loop
         *
         */
        void Client_LoopStart();

        /**
         * @brief message when you disconnect
         *
         */
        void DeconnectionHost();

        /**
         * @brief Get the Peer object
         *
         * @return ENetPeer*
         */
        ENetPeer *getPeer() {
            return (peer);
        }

        /**
         * @brief split string
         *
         * @param myStr string to split
         * @param delimit string to delimit myStr
         * @return vector<string>
         */
        vector<string> mySplit(string myStr, string delimit) {
            vector<string> vector_split;
            int start, end = -1 * delimit.size();
            do {
                start = end + delimit.size();
                end = myStr.find(delimit, start);
                vector_split.push_back(myStr.substr(start, end - start));
            } while (end != -1);
            return (vector_split);
        }
        int id_others;
        float posX_others;
        float posY_others;

    private:
        ENetHost *client;
        ENetAddress address;
        ENetEvent event;
        ENetPeer *peer;
        int ClientNumber = 0;
        char const *address_Name;

};

#endif /* !CLIENT_HPP_ */
