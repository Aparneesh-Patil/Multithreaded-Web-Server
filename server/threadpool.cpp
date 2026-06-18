#include "threadpool.h"

ThreadPool::ThreadPool(int workerSize){
    // initializes the worker threads so that they are sleeping until one of them is notified
    for(int i = 0; i < workerSize; i++){
        std::thread worker(&ThreadPool::worker_loop, this);
        worker_threads.push_back(move(worker));
    }
}

void ThreadPool::add(SOCKET s){
    // lock guard has the scope of a function so after these curly brackets, the lock is unlocked
    {
        lock_guard<mutex> guard(queue_mutex);
        q.push(s);
    }
    
    
    // alerts one of the worker threads to be awake
    cv.notify_one(); 
}

void ThreadPool::worker_loop(){
    while(true){
        SOCKET current;

        {
            unique_lock<mutex> guard(queue_mutex);
            // while the queue is empty, we wait to be notified
            while(q.empty()){
                cv.wait(guard);
            }
            
            // pop socket
            current = q.front();
            q.pop();

            // unlock the lock on queue
            
        }
        
        handleClient(current);
    }
}

void ThreadPool::handleClient(SOCKET s){
    // read the request
    char recvbuffer[BUFFER_LEN] = {0};

    int iResult = recv(s, recvbuffer, BUFFER_LEN, 0);

    if (iResult <= 0) {
        cout << "Client disconnected or recv failed\n";
        return;
    }

    recvbuffer[iResult] = '\0';

    // parse the request:
    Parser p;
    Request req = p.parse(recvbuffer);

    // Build the response
    Router rt;
    ResponseBuilder rb;
    Response routed = rt.route(req);

    cout << "Received: " << req.method << " " << req.path << " " << req.version << " -> " << routed.status << endl;

    //send the response to client
    string response = rb.build(routed);
    send(s, response.c_str(), response.size(), 0);
    closesocket(s);
}


