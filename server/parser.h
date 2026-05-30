#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

using namespace std;

struct Request{
    string method;
    string path;
    string version;
};

class Parser{
    public:
        Request parse(char recvbuffer[]);
};


#endif

