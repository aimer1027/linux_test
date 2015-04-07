#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main (int c , char ** v)
{
	struct sockaddr_in server_addr ;
	int sockfd ;
	
	sockfd = socket ( AF_INET , SOCK_STREAM , 0 ) ;

		server_addr.sin_family = AF_INET ;
		server_addr.sin_port = htons (1027) ;
		inet_aton ("127.0.0.1" , &server_addr.sin_addr ) ;

		bind (sockfd ,(struct sockaddr*)&server_addr , sizeof(struct sockaddr_in)  ) ;
		listen ( sockfd , 10 ) ;

	for (;;) {}
	
	return 0 ; 
}
