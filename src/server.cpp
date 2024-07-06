#include <cstdlib>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){

    int port = atoi(argv[1]);
    char message[2100];
    //Struct for internet syscall n functions
    sockaddr_in serverAddress;
    memset(&serverAddress, '\0', sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    //Convert to big endian
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    listen(serverSocket, 2);
    
    sockaddr_in clientAddress;
    int clientDescriptor = accept(serverSocket, (sockaddr *)&clientAddress, (socklen_t *) sizeof(clientAddress));
    while(true){
        memset(&message, 0, sizeof(message));
        recv(clientDescriptor, (char *)&message, sizeof(message), 0);
        cout << "Client: " << message << endl;
        memset(&message, 0, sizeof(message));
    }
    close(clientDescriptor);
    close(serverSocket);
}