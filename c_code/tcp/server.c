#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){

	int socket_desc, client_sock, client_size;
	struct sockaddr_in server_addr, client_addr;
	char server_msg[2000], client_msg[2000];


	// Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc < 0){
		perror("Can;t open socket");
		exit(1);
	}
	printf("Socket created successfully\n");

	// Set port and IP
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Bind the socket descriptor to IP and port
	if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
		perror("Couldn't bind to the port\n");
		exit(1);
	}
	printf("Successfully bind\n");

	// Listen for clients
	if(listen(socket_desc, 5) < 0){
		perror("Error while listening\n");
		exit(1);
	}
	printf("\nListening for incoming connections.....\n");

	// Accept an incoming connection
	client_size = sizeof(client_addr);
	client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, (socklen_t *)&client_size);
	if (client_sock < 0){
		perror("Can't accept \n");
		exit(1);
	}
	printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

	while(1){
		// Clean buffers
		memset(server_msg, '\0', sizeof(server_msg));
		memset(client_msg, '\0', sizeof(client_msg));
		// Receive client's message
		if (recv(client_sock, client_msg, sizeof(client_msg), 0) < 0) {
			perror("Cant' receive msg from client\n");
			exit(1);
		}
		printf("Msg from client: %s\n", client_msg);

		// Respond to client:
		strcpy(server_msg, "This is the server's message.\n");

		if(send(client_sock, server_msg, sizeof(server_msg), 0) < 0 ){
			perror("Can't send\n");
			exit(1);
		}
	}

	// Close the sockets
	close(client_sock);
	close(socket_desc);
	return 0;
}
