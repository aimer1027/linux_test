// my_scanner.h
#ifndef MY_SCANNER_H
#define MY_SCANNER_H

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#include <pthread.h>
#include <vector>


struct _scan_segment 
{
   unsigned short int from_port ;
   unsigned short int to_port ;
   struct in_addr     scan_addr ;	
} ;

typedef _scan_segment scanSegment ;


class Scanner
{
  private :
	std::vector<pthread_t> pthreadList ;
	int            threadNum ; 
	int 	       connfd ;	
	struct in_addr scan_addr ;
	int            scan_max_port ; 
	int		scan_len ;
	
  public :
	Scanner ( int _threadNum , struct in_addr _scan_addr , int _scan_max_port ) ;

//       static	int  do_scan  ( struct sockaddr_in  ) ;
//	void * scanner ( void *) ;	
	void run ( void ) ;

} ;

#endif // my_scanner.h

