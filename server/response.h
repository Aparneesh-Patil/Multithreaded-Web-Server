#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <cstring>
#include <sstream>

using namespace std;

struct Response{
    string status;
    string body;
    string contentType;    
};

class ResponseBuilder{
    public:
        string build(const Response& res);
};

#endif