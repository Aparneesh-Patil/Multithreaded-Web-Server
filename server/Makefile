server: main.cpp server.cpp parser.cpp response.cpp router.cpp threadpool.cpp
	g++ main.cpp server.cpp parser.cpp response.cpp router.cpp threadpool.cpp -o server.exe -std=c++17 -pthread -lws2_32

clean:
	del /Q server.exe