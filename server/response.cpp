#include "response.h"

string ResponseBuilder::build(const Response& res){
    string response = 
        string("HTTP/1.1 ") + res.status + "\r\n" +
        "Content-Type: " + res.contentType + "\r\n" +
        "Content-Length: " + to_string(res.body.size()) + "\r\n" +
        "Connection: close\r\n" +
        "\r\n" + string(res.body);

    return response;
};