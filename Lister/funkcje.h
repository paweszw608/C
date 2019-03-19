#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

void help();
void blad();
void usun_liste( lista * glowa );
void usun_drzewo( drzewo * korzen );
void wypisz_lista( lista * glowa, FILE * plik_wyj );
void wypisz_drzewo( drzewo ** korzen, FILE * plik_wyj );
struct lista * lista_dodaj( lista * glowa, unsigned int nr_linii );
void drzewo_dodaj( drzewo **korzen, char * slowo, unsigned int nr_linii );
void wczytaj( char * in, char * out );
