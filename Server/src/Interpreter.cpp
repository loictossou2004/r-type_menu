/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** Interpreter
*/

#include "../includes/server.hpp"

vector<int> NetWorkServer::getRfcArgs(int rfc, string sms)
{
    vector<int> ret;
    ret.push_back(atoi(sms.c_str()));
    if (rfc == 403 || rfc == 407)
        ret.push_back(atoi(sms.substr(sms.find('|') + 1, sms.length()).c_str()));
    return ret;
}

void NetWorkServer::Interpreter(string sms)
{
    int rfc = atoi(sms.c_str());
    vector<int> params;
    sms = (sms.substr(3, sms.length())).c_str();

    if (rfc != 400 && rfc != 404)
        params = getRfcArgs(rfc, sms);
    if (rfc == 400 || rfc == 404) 
        return;
    if (rfc == 401 || rfc == 402) 
        logoutPlayer(params);
    if (rfc == 403) movePlayer(params);
    if (rfc == 405) shotPlayer(params);
    if (rfc == 406) gameJoined(params);
    if (rfc == 407) enemyDown(params);
    if (rfc == 408) playerDown(params);
}