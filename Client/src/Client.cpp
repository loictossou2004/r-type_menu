/*
** EPITECH PROJECT, 2022
** B-CPP-500-COT-5-1-rtype-prunella.dousso
** File description:
** Client
*/

#include "Client/includes/Client.hpp"

/*extern int connected;
extern std::mutex myMutex;
extern std::condition_variable cv;*/
all_connexions c_connect;

NetWorkClient::NetWorkClient(int port, char const *addressName)
{
    address.port = port;
    address_Name = addressName;
}

NetWorkClient::~NetWorkClient()
{
    disconnect_peer();
}

void NetWorkClient::DeconnectionHost()
{
    std::cout << "[401]: Disconnection" << std::endl;
}

int NetWorkClient::Connection_and_initialize()
{
    if (enet_initialized() != 0) {
        fprintf (stderr, "[404]: An error occurred while initializing ENet!\n");
        exit (84);
    }
    call_exit();

    client =  create_Host();

    if (client == NULL) {
        fprintf (stderr, "[404]: An error occurred while trying to create client Host!\n");
        exit (84);
    }

    address_set_host_Client();

    peer = connect_host_Client();
    if (peer == NULL) {
        fprintf (stderr, "[404]: No available peers for iniating an ENet connection\n");
        exit (84);
    }

    if (Host_service(5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
        std::cout << "[400]: Connection to " << address_Name << " succeeded." << std::endl;
    else {
        enet_peer_reset(peer);
        std::cout << "[404]: Connection to " << address_Name << " failed" << std::endl;
        exit (84);
    }
    return (EXIT_SUCCESS);
}

void NetWorkClient::MsgLoop() {
    while (true) {
        ENetEvent event;
        while (enet_host_service(client, &event, 0) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_RECEIVE:
                    unsigned char *str = (unsigned char *) event.packet->data;
                    const char* test = (const char*) str;
                    string myData = (string) test;
                    if (strncmp(myData.c_str(), "Players Connected", strlen("Players Connected")) == 0) {
                        ClientNumber = atoi(myData.substr(strlen("Players Connected: "), 1).c_str());
                        printf ("%d\n", ClientNumber);
                        // std::lock_guard lk(c_connect.myMutex);
                        c_connect.connected = ClientNumber;
                        c_connect.cv.notify_one();
                    }
                    if (strncmp(myData.c_str(), "Position", strlen("Position")) == 0) {
                        vector<string> getVec = mySplit(myData, "__");
                        cout << "myData=  " + myData << "\n";
                        id_others = stoi(getVec[3]);
                        posX_others = stof(getVec[1].substr(2, getVec[1].size() - 2));
                        posY_others = stof(getVec[2].substr(2, getVec[2].size() - 2));
                        cout << "ID= " << id_others << " | poX_= " << posX_others << " && posY_= " << posY_others << endl;
                    }
                    enet_packet_destroy(event.packet);
                    break;
            }
        }
    }
}

void NetWorkClient::Client_LoopStart()
{
    while (true) {
        while (enet_host_service(client, &event, 0) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_RECEIVE:
                    printf ("A packet of length %lu containing %s was received from %x:%u on channel %u.\n",
                    event.packet -> dataLength,
                    event.packet -> data,
                    event.peer -> address.host,
                    event.peer -> address.port,
                    event.channelID);
                    enet_packet_destroy(event.packet);
                    break;
            }
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
