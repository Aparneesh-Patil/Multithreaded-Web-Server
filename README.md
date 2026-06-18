# Multithreaded HTTP Server in C++

A mulithreaded HTTP server built from scratch in C++ using Winsock. This project handles basic HTTP requests, serves static files, supports simple routing, and uses a custom thread pool to handle multiple clients at the same time.

## Overview

The goal of this project was to understand how web servers work (especially the concept of concurrency) without relying on a framework. The server opens a TCP socket, listens for client connections, parses HTTP requests, routes them to the correct response, and sends back valid HTTP/1.1 responses.

I also added a custom thread pool so the server can process multiple client requests at once instead of handling one request at a time.

## Features

* TCP server using Winsock
* Basic HTTP request parsing
* HTTP/1.1 response building
* Simple routing system
* JSON API endpoint
* MIME type detection
* Custom thread pool with worker threads
* Concurrent client handling
* Basic error responses:

  * `400 Bad Request`
  * `403 Forbidden`
  * `404 Not Found`

## How It Works

The server starts by creating a listening socket on `127.0.0.1:8080`. When a client connects, the server accepts the client socket and adds it to the thread pool’s queue.

Worker threads wait until a socket is available. Once a client socket is added, one worker wakes up, removes the socket from the queue, handles the request, sends the response, and then goes back to waiting for more work.

```text
Client connects
      ↓
Server accepts socket
      ↓
Socket is added to the thread pool queue
      ↓
A worker thread wakes up
      ↓
Worker handles the request
      ↓
Response is sent back to the client
```

The queue is protected with a mutex (locks) so multiple worker threads do not change the queue at the same time. The lock is only for pushing and popping out of the queue, so concurrency still works outside of this. 

## Routes

| Route        | Description                            |
| ------------ | -------------------------------------- |
| `/`          | `index.html`                           |
| `/about`     | `about.html`                           |
| `/api`       | Returns a JSON response                |
| `/style.css` | CSS file                               |
| `/script.js` | JavaScript file                        |
| `/slow`      | Test route for checking multithreading |
| Other routes | Returns `404 Not Found`                |

## Build and Run

Compile with:

```bash
g++ main.cpp server.cpp parser.cpp router.cpp response.cpp threadpool.cpp -o server.exe -std=c++17 -pthread -lws2_32
```

Run the server:

```bash
./server.exe
```

Then test it with:

```bash
curl http://127.0.0.1:8080/
```

## Testing Multithreading

The `/slow` route waits 5 seconds before responding. This makes it easier to test whether multiple requests are being handled at the same time.

Run four requests at the same time:

```bash
curl http://127.0.0.1:8080/slow &
curl http://127.0.0.1:8080/slow &
curl http://127.0.0.1:8080/slow &
curl http://127.0.0.1:8080/slow &
wait
```

With four worker threads, all requests should finish in about 5 seconds. If the server was single-threaded, it would instead take 20 seconds

## What I Learned

This project helped me understand how sockets, HTTP requests, routing, and responses work at a lower level. I also learned how concurrency works using threads and also how to build a basic thread pool using the threads, mutex, and conditions libraries

## Future Improvements

* Add graceful shutdown for worker threads
* Improve HTTP parsing
* Add support for POST request bodies
* Add better logging
* Add unit tests
* Support larger file responses
* Add configuration for port and worker count

## Tech Stack

* C++
* Winsock2
* HTTP/1.1
* C++ Standard Library threads
* HTML/CSS/JavaScript

