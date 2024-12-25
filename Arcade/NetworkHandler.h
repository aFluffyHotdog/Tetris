//
// Created by Thitwut Pattanasuttinont on 2024-11-08.
//

#ifndef NETWORKING_H
#define NETWORKING_H
#include <netinet/in.h>


class NetworkHandler {
public:
    sockaddr_in serverAddress{};
    int clientSocket;

    NetworkHandler(int port_no, char *ip_address);
    void Connect();
    void SendMessage();
    void Close();
};



#endif //NETWORKING_H
