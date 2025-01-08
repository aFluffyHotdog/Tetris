#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void startClient(const std::string& serverIp, int serverPort) {
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return;
    }

    // Configure the server address
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);

    // Convert IP address to binary format
    if (inet_pton(AF_INET, serverIp.c_str(), &serverAddress.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        close(sock);
        return;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Connection to server failed");
        close(sock);
        return;
    }

    std::cout << "Connected to server at " << serverIp << ":" << serverPort << std::endl;

    // Communication loop
    char buffer[1024];
    std::string message;
    while (true) {
        std::cout << "Enter message to send: ";
        std::getline(std::cin, message);

        // Send the message to the server
        if (send(sock, message.c_str(), message.length(), 0) < 0) {
            perror("Send failed");
            break;
        }

        // Receive the server's response
        ssize_t bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived < 0) {
            perror("Receive failed");
            break;
        } else if (bytesReceived == 0) {
            std::cout << "Server disconnected" << std::endl;
            break;
        }

        buffer[bytesReceived] = '\0';  // Null-terminate the received data
        std::cout << "Received from server: " << buffer << std::endl;
    }

    // Close the socket
    close(sock);
}

int main() {
    std::string serverIp = "192.168.4.1";  // Replace with your Raspberry Pi's hotspot IP
    int serverPort = 65432;

    startClient(serverIp, serverPort);

    return 0;
}
