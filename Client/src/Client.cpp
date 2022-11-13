/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** Client
*/

#include "../includes/Client.hpp"

NetWorkClient::NetWorkClient(int port, char const *addressName)
{
    address.port = port;
    address_Name = addressName;
}

NetWorkClient::~NetWorkClient()
{
    disconnect_peer();
}

int NetWorkClient::Connection_and_initialize()
{
    if (enet_initialized() != 0) {
        fprintf (stderr, "An error occurred while initializing ENet!\n");
        return EXIT_FAILURE;
    }
    call_exit();

    client =  create_Host();

    if (client == NULL) {
        fprintf (stderr, "An error occurred while trying to create client Host!\n");
        return EXIT_FAILURE;
    }

    address_set_host_Client();

    peer = connect_host_Client();
    if (peer == NULL) {
        fprintf (stderr, "No available peers for iniating an ENet connection\n");
        return EXIT_FAILURE;
    }

    if (Host_service(5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
        std::cout << "Connection to 127.0.0.1 succeeded." << std::endl;
    else {
        enet_peer_reset(peer);
        std::cout << "Connection to 127.0.0.1 failed" << std::endl;
        return EXIT_FAILURE;
    }
    return (EXIT_SUCCESS);
}

void  NetWorkClient::MsgLoop () {
    while (true) {
        ENetEvent event;
        while (enet_host_service(client, &event, 0) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_RECEIVE:
                    printf ("A packet length %lu containing %s was received from on channel",
                    event.packet->dataLength,
                    event.packet->data);
                    enet_packet_destroy(event.packet);
                    break;
            }
        }
    }
}

void NetWorkClient::Client_LoopStart()
{
    while (Host_service(1000) > 0) {
        if (event.type == ENET_EVENT_TYPE_RECEIVE) {
            printf ("A packet length %lu containing %s was received from on channel",
            event.packet->dataLength,
            event.packet->data);
            break;
        }
    }
}

// int main(int ac, char **av)
// {
//     if (ac != 3) {
//         printf ("You must to use 2 arguments after binary to run server:\n");
//         printf ("Usage:\n");
//         printf ("First argument: Port (Number)\n");
//         printf ("Second argument: address ip\n");
//         return (84);
//     }
//     else {
//         NetWorkClient myClient(atoi(av[1]), av[2]);
//         myClient.Connection_and_initialize();
//         myClient.Send_to_Client("It's time to send packet");
//         myClient.Client_LoopStart();

//         std::thread myThread_2(&NetWorkClient::MsgLoop, &myClient);
//         bool running = true;
//         while (running) {
//             std::string message;
//             std::cout << "Your message: ";
//             std::getline(std::cin, message);

//             myClient.Send_to_Client(message.data());
//         }
//         myThread_2.join();
//     }
// }
