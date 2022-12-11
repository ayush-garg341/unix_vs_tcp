#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define NAME "/tmp/sock"

void sigintHandler(int);

int main(){
	int sock, msgsocket, rval;
	struct sockaddr_un server;

 // creating a buffer to read data
 char buf[1024];

 // creating a new socket
 sock = socket(AF_UNIX, SOCK_STREAM, 0);
 if(sock < 0){
	 perror("error opening stream socket");
	 exit(1);
 }
 server.sun_family = AF_UNIX;
 strcpy(server.sun_path, NAME);

 // Bind the socket to file
 if(bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_un))){
	 perror("Error binding socket");
	 exit(1);
 }
 printf("Socket has name %s\n", server.sun_path);
 listen(sock, 5);
	signal(SIGINT, sigintHandler);

 // waiting for the client to connect after listen() function call
	printf("WAITING FOR THE CLIENT\n");
	int pid;
		while(1){
			msgsocket = accept(sock, 0, 0);
			printf("server: accept()\n");
			if (msgsocket == -1){
				perror("accept");
			}	else{
				char msg1[] = "Sleep";
				if(write(msgsocket, msg1, sizeof(msg1))<0){
					perror("writing on upstream socket");
					exit(1);
				}
				printf("The server requests the client to sleep\n");
			}
			if (msgsocket < 0){
				perror("Error on accept");
			}
			pid = fork();
			if (pid < 0) {
          perror("ERROR in new process creation");
      }
			if (pid==0){
				printf("Child Process\n");
				while(1){
					bzero(buf, sizeof(buf));
					if((rval = read(msgsocket, buf, 1024))<0){
						perror("reading stream message");
					}
					else if(rval==0){
						continue;
					}
					else{
						if(strcmp("Done\n", buf)==0){
							printf("Message from the client : %s\n",buf);
							break;
						}
						else{
							printf("Message from the client : %s\n", buf);
							char ok_msg[] = "Ok, got it";
							if(write(msgsocket, ok_msg, sizeof(ok_msg))<0){
								perror("writing on upstream socket");
								exit(1);
							}
						}
						continue;
					}
				}
				char msg2[]="Quit";
				if (write(msgsocket, msg2, sizeof(msg2)) < 0)
					perror("writing on stream socket");
				printf("The server requests the client to quit\n");
				close(msgsocket);
			}
		}
		close(sock);
		unlink(NAME);
}

void sigintHandler(int sig){
	printf("%d\n", sig);
	printf("Ctrl+C pressed, Unlinking sock file");
	unlink(NAME);
	exit(0);
}
