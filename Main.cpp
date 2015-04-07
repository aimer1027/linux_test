#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "my_scanner.h"

using namespace std ;

void usage_info ( void )
{
	printf ("method usage : \n") ;
	printf ("[-m][max port ]\t [-a][server address \"xxx.xxx.xxx.xxx\"]\t [-n][-thread number] \n") ;
}


int main ( int argc , char *argv[] )
{
  int i ; 
  int max_port ;  // -m 
  int thread_num ;  // -n
  struct in_addr destAddr ; // -a
 
  Scanner *myScanner ;
   

  for ( i = 0 ; i < argc ; i++ )
  {
	 if ( strcmp ( "-m" , argv[i] ) == 0 )
	 {
		max_port = atoi (argv[i+1]) ;
 		if ( max_port < 0 || max_port > 65536 )
		{
			perror (" invalid port number ") ;
			return -1 ;	
		}
	 }
		
	if ( strcmp ( "-a" , argv[i] ) == 0 )
	{
		printf ("input ip address  : %s \n", argv[i+1]) ;
	
		if ( inet_aton (argv[i+1] , &destAddr ) < 0 ) 
		{
			perror (" invalid ip address ") ;
			return -1 ;
		}
	}
	
	if ( strcmp ( "-n" , argv[i] ) == 0 )
	{
		thread_num = atoi (argv[i+1]) ;
	
		if ( thread_num <= 0 )
		{
			perror (" invalid threadnum ") ;
			return -1 ;	
		}
	}
  } 
  
  printf ("here is the info you input\n") ;
  printf ("max port : %d \n" , max_port ) ;
 // printf ("address ip : %s\n", inet_nota (destAddr) ) ;
  printf ("thread number : %d \n" , thread_num) ;
	
 
  myScanner = new Scanner (thread_num , destAddr , max_port ) ;	
  myScanner->run () ;  


  goto success ;

  error :
	printf ("main error") ;
	goto success ;
 success:
	return 0 ;
}
