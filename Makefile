server: server.cpp
	g++ server.cpp -o server.exe -lws2_32

clean:
	del /Q server.exe