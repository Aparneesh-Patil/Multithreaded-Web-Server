#ifndef ROUTER_H
#define ROUTER_H

#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include "response.h"
#include "parser.h"

using namespace std;

class Router{
    public:
        Response route(Request req);

    private:
        string read_file(string fileName);
        string type_detection(string name);
        bool ends_with(const string& text, const string& suffix);
};

#endif