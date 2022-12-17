#### UNIX vs TCP socket
- C implementation of unix and tcp socket
	- To run the code for server and client.
		- gcc -o server.out c_code/unix/server.c
		- gcc -o client.out c_code/unix/client.c
		- In one terminal run server executable (./server.out)
		- In other terminal run client executable (./client.out)
- Python implementation of unix and tcp socket
		- python3 server.py
		- python3 client.py

- Different branches
	- unix_socket_c -> unix socket imeplementation in c
	- unix_socket_c_multiclient -> multiple clients can connect to same server.
	- tcp_socket -> tcp socket implementation in c
	- unix_socket_python -> unix socket in python
	- tcp_socket_python -> tcp socket in python
