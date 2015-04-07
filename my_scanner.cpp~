#include "my_scanner.h"

using namespace std ;

static void log_info ( const char *err_info , int location )
{
	fprintf (stderr, "[error]: %s, [line]: %d\n" , 	err_info , location) ;
	perror ("exit function errinfo ") ;
	exit ( 1 ) ;
}


Scanner::Scanner ( int _threadNum , struct in_addr _scan_addr , int _scan_max_port )
{
	
	threadNum = _threadNum ;
	scan_max_port = _scan_max_port ;
	

	if ( threadNum > scan_max_port  )
		threadNum = scan_max_port ;

	scan_len = scan_max_port / threadNum ;
	

	// copy addr 
	scan_addr = _scan_addr ;	
	
	for ( int i = 0 ; i < threadNum ; i++ )
	{	
		pthread_t thread ;
		pthreadList.push_back ( thread ) ;
	}
}


int  do_scan (  struct sockaddr_in dest_addr )
{
	int ret , conn_fd = socket ( AF_INET , SOCK_STREAM , 0 ) ;
	
	if ( conn_fd < 0 ) 
         log_info ("socket" , __LINE__) ; 

	ret = connect ( conn_fd , (struct sockaddr *)&dest_addr ,
				sizeof ( struct sockaddr_in )) ;
	 if ( ret < 0 )
	 {
		if ( errno == ECONNREFUSED )
		{
			close (conn_fd ) ;
			return -1;  // target port refused service
		}
		else 
		{
			close ( conn_fd ) ;
			return -2;  // other error type 
		}

	 }
	else
	{
		
		printf ("port %d found in %s \n" , ntohs(dest_addr.sin_port) , inet_ntoa(dest_addr.sin_addr)) ;
		close (conn_fd) ;
		return 1 ;
	}
	return 0  ;
}


void* scanner ( void *arg )
{
	unsigned short int i ;
	scanSegment scan_segment ;
	struct sockaddr_in dest_addr ;
	
	memcpy ( &scan_segment , arg , sizeof ( scanSegment )) ;
	
	dest_addr.sin_family 	  = AF_INET ;
	dest_addr.sin_addr = scan_segment.scan_addr ;	
	
	for ( i = scan_segment.from_port ; i != scan_segment.to_port ; i++ )
	{
		dest_addr.sin_port  = htons ( i ) ; 
		
		printf ("detected by   thread %lu , results :\n"  , pthread_self() ) ;
	
		switch ( do_scan ( dest_addr ) )
		{
			case -1 :
				printf ("refused service\n" ,i ) ;
			break ;
			
			case -2 :
				printf ("other type error \n" , i ) ;
			break ;
			
			case 1:
				printf ("check port %d free " , i ) ;			
			break ;
			default :
				printf ("unknown error \n") ;	
		}
			
	}
	
}

void Scanner::run ()
{
	scanSegment segment ;
	segment.scan_addr = scan_addr ;
	
	
	for ( int i = 0 ; i < threadNum ; i++  )
	{
		segment.from_port = i*scan_len + 1 ;
		
		if ( i == threadNum -1 )
		{
			segment.to_port = scan_max_port ;	
		}
		else
		{
			segment.to_port = segment.from_port + scan_len -1 ;
		}
		
		if ( pthread_create ( &pthreadList[i] , NULL , scanner , (void *)&segment )  ) 
		{
			log_info ("pthread_create" , __LINE__) ;
		}
		
		pthread_join ( pthreadList[i] , NULL ) ;
	}
}
