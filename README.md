#### UNIX vs TCP socket
- C implementation of unix and tcp socket
	- To run the code for server and client (For unix).
		- gcc -o server.out c_code/unix/server.c
		- gcc -o client.out c_code/unix/client.c
		- In one terminal run server executable (./server.out)
		- In other terminal run client executable (./client.out)
		- In this version one server can connect to multiple client.
				- We can run one server and multiple clients and pass messages.
- Python implementation of unix and tcp socket
