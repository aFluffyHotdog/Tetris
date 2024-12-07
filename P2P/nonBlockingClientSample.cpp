#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
int main(){
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	
	const char* message = "Hi server";
	
	int flags = fcntl(clientSocket, F_GETFL, 0);
	
	if (flags == -1) {
		return -1;
	}
	
	if (fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK) == -1) {
		return -1;
	} 
	else 
	{
		cout << "it's non blocking now?" << endl;
	}
	
	cout << "initializing server" << endl;
	int i = 0;
	char buffer[1024] = {0};

	while (true) {
		send(clientSocket, message, strlen(message), 0);
		
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
		
		if (bytesReceived < 0) {
			continue;
		}	
		buffer[bytesReceived] = '\0';
		cout << "received " << buffer << endl;
	}
	close(clientSocket);
	return 0;
}
