/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** Main
*/

#include "Server/includes/server.hpp"

int main(int ac, char **av)
{
    if (ac != 3) {
        printf ("You must to use 2 arguments after binary to run server:\n");
        printf ("Usage:\n");
        printf ("First argument: Port (Number)\n");
        printf ("Second argument: address ip\n");
        return (84);
    }
    else {
        NetWorkServer myServer(std::atoi(av[1]), av[2]);
        myServer.RunServerEnet();
        return (0);
    }
}