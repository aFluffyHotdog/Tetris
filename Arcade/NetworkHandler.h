//
// Created by Thitwut Pattanasuttinont on 2024-11-08.
//

#ifndef NETWORKING_H
#define NETWORKING_H
#include "Networking.h"
// C++ program to illustrate the client application in the
// socket programming with error checking
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> // For inet_addr()


class Networking {
    sockaddr_in serverAddress{};
    Networking(int port_no, char *ip_address);
};



#endif //NETWORKING_H
