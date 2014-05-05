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
#include <stdio.h>
#include <readline/readline.h>



int main() {
    int sock, listener;
    struct sockaddr_in addr;
    struct sockaddr_in cli_addr;
    char buf[1024];
    int len;
    pid_t childpid;
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0){
        perror("SOCKET");
        exit(0);
    }

    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3448);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("BIND");
        exit(0);
    }

    listen(listener, 10);
    
    while(1) {
    
    	len = sizeof(cli_addr);
        sock = accept(listener, (struct sockaddr *)&cli_addr, &len);
        if(sock < 0) {
            perror("ACCEPT");
            exit(3);
        }
		if ((childpid = fork()) == 0) {
        	close(listener);
    	    int fd = open( "history", O_RDWR | O_CREAT | O_APPEND, 0777);	
			if ( fd < 0 ) {
				perror("HISTORY");
				exit(0);
			}
        	while( (bytes_read = read(fd, buf, 1024)) > 0) {
        		send(sock, buf, strlen(buf), 0);
        	}
        	
		    char line[200];
		    int n;
        	while(1) {
        		if((n = recv(sock, line, 200, 0)) == 0) 
        			break;
        		write(fd, line, n);	
        	}
        	close(fd);
        	exit(0);
		}
 		close(sock);       
    }   
    return 0;
}
