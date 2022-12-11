#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_un server;

    // creating a buffer to read data
    char buf[1024];

    // creating a new socket
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    // checking if an error occurred while creating a socket
    if (sock < 0) {
        perror("opening stream socket");
        exit(1);
    }
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, "/tmp/sock");

    // connecting to the socket created in the server
    // the file name is used to specify the correct socket
    if (connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) < 0) {
        close(sock);
        perror("connecting stream socket");
        exit(1);
    }

    int rval;
    while(1){
        // fills the first n bytes of the object pointed to by dst (buf) with zero (NUL) bytes.
        bzero(buf, sizeof(buf));
        if ((rval = read(sock, buf, 1024)) < 0)
            perror("reading stream message");
        else if(rval==0){
            printf("Server has closed the connection hence exiting");
            break;
        }
        else
        {
            if(strcmp(buf,"Sleep")==0){
                printf("The client is going to sleep for 5 seconds\n");
                sleep(5);
                printf("\n Enter your message: ");
                /*scanf("%s", &buf);*/
                fgets(buf,1024,stdin);
                if(write(sock, buf, sizeof(buf))<0){
                  perror("writing on upstream socket");
                  exit(1);
                }

            }
            else if(strcmp(buf,"Quit")==0){
                printf("The client is quitting\n");
                break;
            }
            else{
                /*printf("Invalid Command Sent By The Server\n");*/
                printf("server responded with: ");
                printf("%s", buf);
                printf("\n Enter your message: ");
                /*scanf("%s",&buf);*/
                fgets(buf,1024,stdin);
                if(write(sock, buf, sizeof(buf))<0){
                  perror("writing on upstream socket");
                  exit(1);
                }
            }
        }
    }
    close(sock);
}
