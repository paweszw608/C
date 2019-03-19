#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct drzewo
{
	char * slowo; //zmienna przechowuje sczytane z pliku slowa
	struct lista * glowa; //wskaznik na 1. elem. listy
	struct drzewo * prawy, *lewy;// wskazniki na potomków
}drzewo;
typedef struct lista
{
	struct lista * nast; // wskaznik na nastepny elem. listy
	unsigned int nr_linii;
	// zmianna przechowuje nr. linii, w ktorym wystapilo dane slowo
}lista;
void help()
{
	printf( "\nWystapil blad!\nWprowadz nastepujaca formule z uzyciem przelacznikow:\n-i 'plik wejsciowy' -o 'plik wyjsciowy'\n" );
}
void blad()
{
	printf( "Blad podczas otwarania pliku!\nSprawdz czy plik o podanej nazwie istnieje\n" );
}
void usun_liste( lista * glowa )
{
	lista * tmp = glowa;
	lista * tmp2;
	while( tmp != NULL )
	{
		tmp2 = tmp->nast;
		free( tmp );
		tmp = tmp2;
	}
}
void usun_drzewo( drzewo * korzen )
{
	if( korzen != NULL )
	{
		usun_drzewo( korzen->lewy );
		usun_drzewo( korzen->prawy );
		usun_liste( korzen->glowa );
		free( korzen->slowo );
		free( korzen );
	}

}
void wypisz_lista( lista * glowa, FILE * plik_wyj )
{
	lista * tmp = glowa;
	short flaga = 1;
	while( tmp != NULL )
	{
		if( flaga != 1 )
		{
			fprintf( plik_wyj, ", " );
		}
		fprintf( plik_wyj, "%d", tmp->nr_linii );
		tmp = tmp->nast;
		flaga++;
	}
	fprintf( plik_wyj, "\n" );
}
void wypisz_drzewo( drzewo * korzen, FILE * plik_wyj )
{
	if( korzen != NULL )
	{
		wypisz_drzewo( korzen->lewy, plik_wyj );
		fprintf( plik_wyj, "%s: ", korzen->slowo );
		wypisz_lista( korzen->glowa, plik_wyj );
		wypisz_drzewo( korzen->prawy, plik_wyj );
	}
}

struct lista * lista_dodaj( lista * glowa, unsigned int nr_linii )
{

	lista * tmp = glowa;
	if( tmp != NULL )
	{
		while( tmp->nast != NULL )
		{
			tmp = tmp->nast;
		}
		if( tmp->nr_linii != nr_linii )
		{
			lista * nowy = (lista*) malloc( sizeof( lista ) );
			nowy->nr_linii = nr_linii;
			nowy->nast = NULL;
			tmp->nast = nowy;
		}
	}
	else
	{
		lista * nowy = (lista*) malloc( sizeof( lista ) );
		nowy->nr_linii = nr_linii;
		nowy->nast = NULL;
		glowa = nowy;
	}
	return glowa;
}
void drzewo_dodaj( drzewo **korzen, char * slowo, unsigned int nr_linii )
{
	drzewo * tmp = *korzen;
	if( tmp != NULL )
	{
		if( ( strcmp( slowo, tmp->slowo ) ) > 0 )
		{
			drzewo_dodaj( &( tmp->prawy ), slowo, nr_linii );
		}
		else if( ( strcmp( slowo, tmp->slowo ) ) == 0 )
		{
			tmp->glowa = lista_dodaj( tmp->glowa, nr_linii );
		}
		else
		{
			drzewo_dodaj( &( tmp->lewy ), slowo, nr_linii );
		}
	}
	else
	{
		drzewo * nowy = (drzewo*) malloc( sizeof( drzewo ) );
		nowy->slowo = malloc( strlen( slowo ) + 1 );
		nowy->glowa = NULL;
		strcpy( nowy->slowo, slowo );
		*korzen = nowy;
		nowy->prawy = NULL;
		nowy->lewy = NULL;
		nowy->glowa = lista_dodaj( nowy->glowa, nr_linii );

	}
}
void wczytaj( char * in, char * out )
{
	drzewo * korzen = NULL;
	FILE * plik;
	plik = fopen( in, "r" );
	if( plik != NULL )
	{
		int ch = getc( plik );
		char slowo[ 100 ] = "";
		int i = 0;
		int k = 0;
		unsigned int nr_linii = 1;

		while( ch != EOF )
		{
			if( ( ch >= 65 && ch <= 90 ) || ( ch >= 'A' && ch <= 122 ) )
			{
				slowo[ i ] = ch;
				i++;

			}
			else if( ch == 10 )
			{
				nr_linii++;
			}
			else
			{
				slowo[ i ] = '\0';
				if( slowo[ 0 ] != 0 )
				{
					for( k = 0; k<strlen( slowo ); k++ )
					{
						slowo[ k ] = tolower( slowo[ k ] );
					}
					drzewo_dodaj( &korzen, slowo, nr_linii );
				}
				i = 0;
				memset( slowo, 0, sizeof slowo );

			}

			ch = getc( plik );

		}

	}
	else blad();
	FILE * plik_wyj;
	plik_wyj = fopen( out, "w" );
	if( plik_wyj != NULL )
	{
		wypisz_drzewo( korzen, plik_wyj );
		usun_drzewo( korzen );
	}

	fclose( plik_wyj );
	fclose( plik );

}