#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <condition_variable>
#include "parser.h"
#include "response.h"
#include "router.h"
#define BUFFER_LEN 512

class ThreadPool{
public:
    ThreadPool(int workerSize);
    void add(SOCKET s);


private:
    std::vector<std::thread> worker_threads;
    std::queue<SOCKET> q;
    std::mutex queue_mutex;
    condition_variable cv;

    void worker_loop();
    void handleClient(SOCKET s);

};





#endif