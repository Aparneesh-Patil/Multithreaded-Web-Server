#include "parser.h"


Request Parser::parse(char recvbuffer[]){
    stringstream ss{string(recvbuffer)};

    Request req;
    ss >> req.method >> req.path >> req.version;

    return req;
}