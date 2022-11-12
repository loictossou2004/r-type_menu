/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** eraser
*/

#include "../includes/server.hpp"

vector<int> eraseVector(vector<int> c, int elem)
{
    std::vector<int>::iterator it;
    for (it = c.begin(); it != c.end();)
        if (*it == elem) {
            it = c.erase(it);
            break;
        }
        else
            ++it;
    return c;
}

string vector_to_str(vector<int> c)
{
    int saver;
    string ret;

    for (std::vector<int>::iterator it = c.begin(); it != c.end();) {
        ret += to_string(*it) + "|";
        ++it;
    }
    return ret;
}