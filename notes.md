# Server using Winsock

### Every server has the following functions:
    - create sockets
    - bind the sockets
    - listen for clients
    - accept a client
    - read the request
    - send HTTP response
    - close connection


## Initialize Winsock
First, initialize Winsock to use Window's socket API and to turn it on use WSAStartup():

    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0) {
        // Winsock failed to initialize
        return 1;
    }  
    


## TCP Sockets
Socket is the foundation of a webserver. It sets up the communication endpoint that allows network communication between a client and server. To create one:

<p style="text-align: center;"> socket(int af, int type, int protocol) </p> 

where: 
- __af__: The address family specification
- __type__: The type specification for the new socket
- __protocol__: The protocol to be used



## Bind the socket to port
Binding gives the server endpoint an address/port. To do so:

<p style="text-align: center;"> bind(SOCKET s, const sockaddr *name, int namelen) </p> 

where:
- **s**: The socket to be binded
- **name**: A pointer to structure of the local address to assign to the bound socket
- **namelen**: The length of the name parameter



## Listen for clients
A listening function allows for the communcation endpoint to be open for clients to connect. To use it:

<p style="text-align: center;"> listen(SOCKET s, int backlog) </p>

where:
- **s**: The socket (or communcation endpoint) that is to be open for clients to connect to
- **backlog**: The maximum length of the queue of pending connections



## Accept clients
Accept function accepts one incoming client connection on a server's listening socket. To use this: 

<p style="text-align: center;"> accept(SOCKET s, sockaddr *addr, int *addrlen) </p>

where:
- **s**: The listening socket
- **addr**: An optional pointer to a buffer that receives the address of the connecting entity
- **addrlen**: An optional pointer to an integer that contains the length of the addr parameter


## Reading Requests
The read function reads data from the client sent through the socket. The way this works is:

<p style="text-align: center;"> recv(SOCKET s, char* buf, int len, int flags) </p>


## Sending Responses
The send function sends a HTTP response back to client. If your client is another socket program, then it is fine to send raw text but if it is a browser or curl, it expects a HTML response. To do so:

<p style="text-align: center;"> send(SOCKET s, char* buf, int len, int flags) </p>


## Closing sockets
We close listening/client sockets at the end of the file, using the following function:

<p style="text-align: center;"> closesocket(SOCKET s) </p>








## Tasks:
    [X] Learn Winsock basics/TCP setup
    [X] Create a TCP server
    [X] HTTP response
    [X] HTTP Request Parsing
    [X] Basic Routing
    [X] Static File Serving
    [X] MIME Type Detection
    [X] Basic Error Handling
    [ ] Custom Thread Pool
    
