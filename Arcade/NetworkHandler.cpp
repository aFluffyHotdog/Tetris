//
// Created by Thitwut Pattanasuttinont on 2024-11-08.
//
#include "Networking.h"
// C++ program to illustrate the client application in the
// socket programming with error checking
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> // For inet_addr()

Networking::Networking(int port_no, char* ip_address) {
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port_no);
    serverAddress.sin_addr.s_addr = inet_addr(ip_address); // Specify server IP here
}

int main()
{
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Error: Could not create socket" << std::endl;
        return 1;
    }

    // specifying address


    // sending connection request
    std::cout << "connecting to server..." << std::endl;
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error: Connection failed" << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Connected to server successfully." << std::endl;

    // sending data
    const char* message = "Hello, server!";
    if (send(clientSocket, message, strlen(message), 0) < 0) {
        std::cerr << "Error: Failed to send message" << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Message sent to server: " << message << std::endl;

    // closing socket
    close(clientSocket);
    return 0;
}
