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

#ifndef SERVER_HPP_
#define SERVER_HPP_

using namespace std;

vector<int> eraseVector(vector<int> c, int elem);
string vector_to_str(vector<int> c);


class NetWorkServer {
    public:
        NetWorkServer(int port, char const *HostName);
        ~NetWorkServer();
        
        int Initialize_enet_Server() {
            return (enet_initialize());
        }
        int Call_exit() {
            return(atexit(enet_deinitialize));
        }
        ENetHost *Create_Host_Server() {
            return (enet_host_create(&address, 32, 1, 0, 0));
        }
        int Set_address_Host_Server() {
            return (enet_address_set_host(&address, Host_Name));
        }
        int Host_Service_Server(int timezone) {
            return(enet_host_service(server, &event, timezone));
        }
        void Serv_Packet_Destroy_() {
            enet_packet_destroy(event.packet);
        }
        void Serv_Destroy_Host() {
            enet_host_destroy(server);
        }

        int initializeEnet();
        int CreateHostEnet();
        void SetHostEnet();
        void ManageHostEnet();
        void RunServerEnet();

        void Interpreter(string sms);
        vector<int> getRfcArgs(int rfc, string sms);

        void logoutPlayer(vector<int> params);
        void movePlayer(std::vector<int> params);
        void shotPlayer(std::vector<int> params);
        void gameJoined(std::vector<int> params);
        void enemyDown(std::vector<int> params);
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
};

#endif /* !SERVER_HPP_ */
