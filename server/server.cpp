#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector> 
#include "server.h"

Server::Server(int port){
    this->port = port;
    sock = INVALID_SOCKET;
};


bool Server::start(){
    if(!setUpSocket()){
        return false;
    }

    cout << "Server running on port " << port << endl;
    return true; 
};

void Server::run(){
    SOCKET client;

    while(true){
        client = acceptClient();

        if(client == INVALID_SOCKET){
            cout << "Accept function failed";
            continue;
        }

        handleClient(client);
        closesocket(client);
    }
};

void Server::stop(){
    closesocket(this->sock);
    WSACleanup();
};


bool Server::setUpSocket(){
    // initialize winsock
    WSADATA wsaData;
    int iResult = 0;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        cout << "Error at WSAStartup()";
        return false;
    }

    // create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == INVALID_SOCKET){
        cout << "Socket function failed";
    }

    // bind the socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(this->port);

    if(bind(this->sock, (SOCKADDR *) &service, sizeof(service)) == SOCKET_ERROR){
        cout << "Bind function failed";
        return false;
    }

    // listen for client
    if(listen(this->sock, SOMAXCONN) == SOCKET_ERROR){
        cout << "Listen function failed";
        return false;
    }

    return true;
};

SOCKET Server::acceptClient(){
    SOCKET client = accept(this->sock, nullptr, nullptr);
    return client;
};

void Server::handleClient(SOCKET clientSocket){

    // read the request
    char recvbuffer[BUFFER_LEN] = {0};

    int iResult = recv(clientSocket, recvbuffer, BUFFER_LEN, 0);

    if (iResult <= 0) {
        cout << "Client disconnected or recv failed\n";
        return;
    }

    recvbuffer[iResult] = '\0';

    // parse the request:
    Parser p;
    Request req = p.parse(recvbuffer);

    // Build the response
    Router rt;
    ResponseBuilder rb;
    Response routed = rt.route(req);

    cout << "Received: " << req.method << " " << req.path << " " << req.version << " -> " << routed.status << endl;

    string response = rb.build(routed);

    
    
    //send the response to client
    send(clientSocket, response.c_str(), response.size(), 0);
};

