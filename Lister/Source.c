#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funkcje.h"
int main( int argc, char **argv )
{

	char *in = NULL, *out = NULL;
	char *napis;
	short flaga = 2;
	int i;
	for( i = 1; i < argc; i++ )
	{
		napis = argv[ i ];
		if( ( strcmp( napis, "-i" ) ) == 0 && ( i + 1<argc ) )
		{
			in = argv[ i + 1 ];
			flaga--;
		}
		else if( ( strcmp( napis, "-o" ) ) == 0 && ( i + 1<argc ) )
		{
			out = argv[ i + 1 ];
			flaga--;
		}
	}
	if( flaga == 0 ) wczytaj( in, out );
	else help();


	system( "pause" );
	return 1;
}