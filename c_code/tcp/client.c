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
	int socket_desc;
	struct sockaddr_in server_addr;
	char client_msg[2000], server_msg[2000];

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc < 0){
		perror("Can't open socket\n");
		exit(1);
	}
	printf("Socket created successfully\n");


	// Set port and IP
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
		perror("Can't connect to server\n");
		exit(1);
	}
	printf("Connected with server successfully\n");
	// Get input from the user:
  while(1){
      // Clean the buffers
      memset(server_msg, '\0', sizeof(server_msg));
      memset(client_msg, '\0', sizeof(client_msg));

      printf("Enter message : ");
      gets(client_msg);

      // Send the message to server
      if(send(socket_desc, client_msg, strlen(client_msg), 0) < 0){
          printf("Can't send msg to server\n");
          return -1;
        }

      // Recv the msg from server
      if(recv(socket_desc, server_msg, sizeof(server_msg), 0) < 0){
          printf("Can't receive the msg from server\n");
          return -1;
        }
      printf("Len of message returned by server : %ld\n", strlen(server_msg));
      printf("Size of message returned by server : %ld\n", sizeof(server_msg));
      printf("Server's response: %s\n",server_msg);
  }
	// Close the socket
	close(socket_desc);
	return 0;
}


/*
 * Difference between sizeof and strlen
 * strlen method is used to find the length of null terminated string.
 * sizeof method is used to find the actual size of data.
 * In the above example if in recv call we change sizeof to strlen, we will get nothing in server_msg. The reason being strlen(server_msg) is 0 as it's null terminated but sizeof(server_msg) is 
 * 2000 as it contains 2000 bytes of data. So in recv we will read 0 bytes in buffer and hence empty server_msg.
 */
