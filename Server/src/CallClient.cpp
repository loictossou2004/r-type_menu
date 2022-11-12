/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** CallClient
*/

#include "../includes/server.hpp"

    // if (rfc == 401 || rfc == 402) 
    //     logoutPlayer(params);
    // if (rfc == 403) movePlayer(params);
    // if (rfc == 405) shotPlayer(params);
    // if (rfc == 406) addPlayer(params);
    // if (rfc == 407) enemyDown(params);
    // if (rfc == 408) playerDown(params);

void NetWorkServer::logoutPlayer(vector<int> params)
{
    string rfc = "508|";
    if (params.size() != 1) {
        cout << "logoutPlayer: not enough or too much params" << endl;
        return;
    }
//    send_message(0, rfc + to_string(params[0]));
    _id_list = eraseVector(_id_list, params[0]);
}

void NetWorkServer::gameJoined(vector<int> params)
{
    string rfc = "506|";
    if (params.size() != 1) {
        cout << "gameJoined: not enough or too much params" << endl;
        return;
    }
    if (_game_id.size() >= 4) {
        cout << "gameJoined: Maximum number for players reached" << endl;
        return;
    }
    _game_id.push_back(params[0]);
//    send_message(0, rfc + vector_to_str(_game_id));
}

void NetWorkServer::movePlayer(vector<int> params)
{
    string rfc = "503|";
    if (params.size() != 2) {
        cout << "logoutPlayer: not enough or too much params" << endl;
        return;
    }
    rfc += to_string(params[0]);
    rfc += "|";
    rfc += to_string(params[1]);
//    send_message(0, rfc);
}

void NetWorkServer::shotPlayer(std::vector<int> params)
{
    string rfc = "505|";
    if (params.size() != 2) {
        cout << "shotPlayer: not enough or too much params" << endl;
        return;
    }
    rfc += to_string(params[0]);
    rfc += "|";
    rfc += to_string(params[1]);
//    send_message(0, rfc);
}

void NetWorkServer::enemyDown(std::vector<int> params)
{
    string rfc = "507|";
    if (params.size() != 2) {
        cout << "enemyDown: not enough or too much params" << endl;
        return;
    }
    eraseVector(_enemy_id, params[0]);
    rfc += to_string(params[0]);
    rfc += "|";
    rfc += to_string(params[1]);
//    send_message(0, rfc);
}

void NetWorkServer::playerDown(std::vector<int> params)
{
    string rfc = "508|";
    if (params.size() != 1) {
        cout << "playerDown: not enough or too much params" << endl;
        return;
    }
    //killPlayer();
    rfc += params[0];
//    send_message(0, rfc);
}