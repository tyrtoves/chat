#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include <netinet/in.h>

int main(int argc, char** argv) {

	
    int sock;
    struct sockaddr_in addr;
	if (argc != 2) {
		printf("Wrong number of arg");
		exit(0);
	}
    sock = socket(AF_INET, SOCK_STREAM, 0);
 	if(sock < 0) {
        perror("SOCKET");
        exit(0);
    }
	fd_set rset;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3448);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("CONNECT");
        exit(0);
    }
    
	//reading
	char* recvline;
	char* sendline;
	char buf[1024];
	int bytes_read;
	while(1) {
		if ((bytes_read = recv(sock, buf, 1024, 0)) <= 1024) {
			write(1, buf, bytes_read);
			break;
		}
		write(1, buf, bytes_read);
	}

	while(fgets(sendline, 200, stdin) != NULL) {
		send(sock, sendline, strlen(sendline), 0);
	}	
	
    return 0;
}
