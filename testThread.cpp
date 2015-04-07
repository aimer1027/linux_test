#include <stdio.h>
#include <string.h>
#include <pthread.h>

 pthread_t threadList[10] ;


void * myID (void *)
{
	printf ("thread id : %u \n" , (unsigned int)pthread_self() ) ;
}


int main ( int c , char ** v )
{
	//pthread_t threadList[10] ;
	
	for ( int i = 0 ; i < 10 ;i++ )
	{
		pthread_create( &threadList[i] , NULL , myID , NULL ) ;
		pthread_join ( threadList[i] , NULL ) ;
	}
	
	return 0 ;
}
