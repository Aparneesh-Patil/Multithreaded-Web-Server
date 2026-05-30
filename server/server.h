#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include "parser.h"
#include "response.h"
#include "router.h"

using namespace std;

#define BUFFER_LEN 512


class Server{
    private:
        SOCKET sock;
        int port;

    public:
        // constructor
        Server(int port);
        bool start();
        void run();
        void stop();

    private:
        bool setUpSocket();
        SOCKET acceptClient();
        void handleClient(SOCKET clientSocket);

};


#endif