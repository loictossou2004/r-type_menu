/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** server
*/

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
#include <map>

#ifndef SERVER_HPP_
#define SERVER_HPP_

using namespace std;

vector<int> eraseVector(vector<int> c, int elem);
string vector_to_str(vector<int> c);

/**
 * @brief Class for NetWork Server
 * 
 */
class NetWorkServer {
    public:
        /**
         * @brief Construct a new Net Work Server object
         * 
         * @param port 
         * @param HostName 
         */
        NetWorkServer(int port, char const *HostName);
        
        /**
         * @brief Destroy the Net Work Server object
         * 
         */
        ~NetWorkServer();
        
        /**
         * @brief Initialize enet Server
         * 
         * @return int 
         */
        int Initialize_enet_Server() {
            return (enet_initialize());
        }

        /**
         * @brief Register a function to be called when `exit' is called.
         * 
         * @return int 
         */
        int Call_exit() {
            return(atexit(enet_deinitialize));
        }

        /**
         * @brief create Host Enet
         * 
         * @return ENetHost* 
         */
        ENetHost *Create_Host_Server() {
            return (enet_host_create(&address, 32, 1, 0, 0));
        }

        /**
         * @brief Attempts to resolve the host named by the parameter hostName and sets the host field in the address parameter if successful.
         * 
         * @return int 
         */
        int Set_address_Host_Server() {
            return (enet_address_set_host(&address, Host_Name));
        }

        /**
         * @brief Enet Host Service
         * 
         * @param timezone 
         * @return int 
         */
        int Host_Service_Server(int timezone) {
            return(enet_host_service(server, &event, timezone));
        }

        /**
         * @brief Destroy Packet
         * 
         */
        void Serv_Packet_Destroy_() {
            enet_packet_destroy(event.packet);
        }

        /**
         * @brief Destroy Host From server
         * 
         */
        void Serv_Destroy_Host() {
            enet_host_destroy(server);
        }

        /**
         * @brief Initialize Enet
         * 
         * @return int 
         */
        int initializeEnet();

        /**
         * @brief Create a Host Enet object
         * 
         * @return int 
         */
        int CreateHostEnet();

        /**
         * @brief Set the Host Enet object
         * 
         */
        void SetHostEnet();

        /**
         * @brief Manage Host Server
         * 
         */
        void ManageHostEnet();

        /**
         * @brief Run server enet
         * 
         */
        void RunServerEnet();

        /**
         * @brief Interpreter
         * 
         * @param sms 
         */
        void Interpreter(string sms);
        vector<int> getRfcArgs(int rfc, string sms);
        
        /**
         * @brief Logout Player
         * 
         * @param params 
         */
        void logoutPlayer(vector<int> params);

        /**
         * @brief Move player
         * 
         * @param params 
         */
        void movePlayer(std::vector<int> params);

        /**
         * @brief Shot player
         * 
         * @param params 
         */
        void shotPlayer(std::vector<int> params);

        /**
         * @brief Game join
         * 
         * @param params 
         */
        void gameJoined(std::vector<int> params);

        /**
         * @brief Enemy Down
         * 
         * @param params 
         */
        void enemyDown(std::vector<int> params);

        /**
         * @brief Player down
         * 
         * @param params 
         */
        void playerDown(std::vector<int> params);

    private:
        ENetHost *server;
        ENetAddress address;
        ENetEvent event;
        ENetPeer *peer;
        char const *Host_Name;
        vector<int> _id_list;
        vector<int> _game_id;
        vector<int> _enemy_id; //map with positions
        map<int, ENetPeer*> id_Client;
};

#endif /* !SERVER_HPP_ */
