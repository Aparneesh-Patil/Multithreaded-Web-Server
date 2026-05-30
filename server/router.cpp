#include "router.h"

Response Router::route(Request req){
    Response res;

    if (req.path == "" || req.method == "" || req.version == "") {
        res.status = "400 Bad Request";
        res.contentType = "text/html";
        res.body = "<h1>400 Bad Request</h1>";
        return res;
    }

    if (req.path == "/api") {
        res.status = "200 OK";
        res.contentType = "application/json";
        res.body =
            "{"
            "\"message\":\"Hello from the C++ server API\","
            "\"status\":\"success\""
            "}";
        return res;
    }

    // if .. is in the path, we throw a 403 Forbidden, since we don't want them to access files beyond the public folder
    if (req.path.find("..") != string::npos) {
        res.status = "403 Forbidden";
        res.contentType = "text/html";
        res.body = "<h1>403 Forbidden</h1>";
        return res;
    }

    string filePath;

    // if / then index, if it's just /name, then name.html, else if it's /_.html/css/js then _.html/_.css/_.js, etc
    if (req.path == "/") {
        filePath = "public/index.html";
    }
    else if (req.path.find('.') == string::npos) {
        filePath = "public" + req.path + ".html";
    }
    else {
        filePath = "public" + req.path;
    }

    res.body = read_file(filePath);
    if (res.body == "") {
        res.status = "404 Not Found";
        res.contentType = "text/html";
        res.body = "<h1>404 Not Found</h1>";
        return res;
    }

    res.status = "200 OK";
    res.contentType = type_detection(filePath);

    return res;
}

// reads the file
string Router::read_file(string fileName){
    ifstream file(fileName);

    if(!file.is_open()){
        cout << "File not found" << endl;
        return "";
    }

    stringstream buff;
    buff << file.rdbuf();
    file.close();

    return buff.str();
};

// MIME type detection
string Router::type_detection(string filePath) {
    if(ends_with(filePath, ".html")) {
        return "text/html";
    }
    else if (ends_with(filePath, ".css")) {
        return "text/css";
    }
    else if (ends_with(filePath, ".js")) {
        return "application/javascript";
    }
    else if (ends_with(filePath, ".json")) {
        return "application/json";
    }
    else if (ends_with(filePath, ".png")) {
        return "image/png";
    }
    else if (ends_with(filePath, ".jpg") || ends_with(filePath, ".jpeg")) {
        return "image/jpeg";
    }
    else if (ends_with(filePath, ".ico")) {
        return "image/x-icon";
    }

    return "text/plain";
}

// helper method for MIME Type Detection to find the suitable type
bool Router::ends_with(const string& text, const string& suffix) {
    if (suffix.size() > text.size()) {
        return false;
    }

    return text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}