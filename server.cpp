#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <cstring>

#define BUFFER_LEN 512
using namespace std;

int main(){
    // initialize winsock
    WSADATA wsaData;
    int iResult = 0;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        cout << "Error at WSAStartup()";
        return 1;
    }

    // create the socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET){
        cout << "Socket function failed";
        WSACleanup();
        return 1;
    }

    // bind the socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(8080);

    if(bind(sock, (SOCKADDR *) &service, sizeof(service)) == SOCKET_ERROR){
        cout << "Bind function failed";
        WSACleanup();
        return 1;
    }

    // listen for client
    if(listen(sock, SOMAXCONN) == SOCKET_ERROR){
        cout << "Listen function failed";
        WSACleanup();
        return 1;
    }

    cout << "Server running. Waiting for client...\n";

    // accept a client
    SOCKET acceptsocket;
    acceptsocket = accept(sock, nullptr, nullptr);

    if(acceptsocket == INVALID_SOCKET){
        cout << "Accept function failed";
        WSACleanup();
        return 1;
    }
    else{
        cout << "Client connected" << endl;
    }
    
    // read request
    char recvbuffer[BUFFER_LEN] = {0};

    iResult = recv(acceptsocket, recvbuffer, BUFFER_LEN, 0);
    cout << "Received: " << recvbuffer << endl;


    // send HTTP response
    const char* body = 
    "<!DOCTYPE html>"
    "<html>"
    "<head><title>My Server</title></head>"
    "<body style='background:white; color:black;'>"
    "<h1>Hello from my server</h1>"
    "<p>You connected successfully.</p>"
    "</body>"
    "</html>";


    string response =  
        string("HTTP/1.1 200 OK\r\n") +
        "Content-Type: text/html\r\n" +
        "Content-Length: " + to_string(strlen(body)) + "\r\n" +
        "Connection: close\r\n" +
        "\r\n" + string(body);

    send(acceptsocket, response.c_str(), response.size(), 0);
    

    // close sockets
    if(closesocket(acceptsocket) == SOCKET_ERROR){
        cout << "Closing sockets failed";
        WSACleanup();
        return 1;
    }

    if(closesocket(sock) == SOCKET_ERROR){
        cout << "Closing sockets failed";
        WSACleanup();
        return 1;
    }


    WSACleanup();
    return 0;
}
