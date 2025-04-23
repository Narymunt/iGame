//=== just pure stuff

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include <FOX.h>
#include <FOX_Audio.h>

#include "FGame.h"
#include "FBackground.h"
#include "FSprite.h"
#include "FEvent.h"

long h1,h2,h3,h4,h5;

unsigned long r,g,b;

unsigned char *klawiatura;		// handler

FOX_Event event;

FOX_Surface *screen;			// to jest juz nasz bufor

//=== tutaj dane dla modu³u ===

FGame	*gra;
FBackground *fbKomnata;	

FSprite	*smokul;

//=== dla zegarka ===

unsigned long ulTimer;
int iDesired;

//=== zapis bitmapy 

FILE	*plik;

//=== to dla timera

static Uint32 tiktak(Uint32 interval)
{
	++ulTimer;

	return (interval);
}

//=== callback

static Uint32 callback(Uint32 interval, void *param)
{
	++ulTimer;
	return (interval);
}


//=== funkcja glowna

main (int argc, char **argv)
{

	if ( FOX_Init(FOX_INIT_VIDEO|FOX_INIT_TIMER) < 0 ) {
		
		fprintf(stderr, "Nie mozna zainicjalizowac... %s\n",FOX_GetError());
		exit(2);
	}

	atexit(FOX_Quit);

	screen = FOX_SetVideoMode(800, 600, 16,
			(FOX_FULLSCREEN|FOX_HWSURFACE|FOX_ASYNCBLIT|FOX_DOUBLEBUF));
	
	if ( screen == NULL ) 
	{
		fprintf(stderr, "Nie mozna ustawic trybu graficznego %dx%d: %s\n",
				800, 600, FOX_GetError());
		exit(3);
	}

	// wystartuj zegar

	iDesired=1;

	FOX_SetTimer(iDesired, tiktak);	// titak zwieksza 

	FOX_WM_SetCaption("Import", "Import");	// tytul okienka

	// ignoruj mysz i zmiane okna
	
	FOX_EventState(FOX_ACTIVEEVENT, FOX_ENABLE);
	FOX_EventState(FOX_MOUSEMOTION, FOX_IGNORE);
	
	FOX_ShowCursor(0);	// schowaj mysz

	FOX_filesys_archive("resource.fox");   

	//=== liczniki gry

	gra = new FGame;

	// wczytaj smokula

	smokul = new FSprite("smokul.evt");

	// handler klawiatury

	klawiatura = FOX_GetKeyState(NULL);	// przypisz 

	// == panel 

	fbKomnata = new FBackground("back001.raw");

	// 2buf

	FOX_BlitSurface(fbKomnata->image,0,screen,0);
	FOX_Flip(screen);
	FOX_BlitSurface(fbKomnata->image,0,screen,0);


//=== l o o p ===

	while (klawiatura[FOXK_ESCAPE]!=FOX_PRESSED) 
	{
		
//	if ( FOX_LockSurface(screen) < 0 ) 	continue;

	FOX_PollEvent(&event);

	FOX_BlitSurface(fbKomnata->image,0,screen,0);

//	smokul->Put(screen,100,100,    ulTimer%72);

	h3 = smokul->fevZdarzenia[0]->ulLiczbaKlatek;

	smokul->Put(screen,
		smokul->fevZdarzenia[0]->iXKlatki[ulTimer%h3], 
		smokul->fevZdarzenia[0]->iYKlatki[ulTimer%h3],
		smokul->fevZdarzenia[0]->uiNrKlatki[ulTimer%h3]); 

	FOX_Flip(screen);

//	FOX_UnlockSurface(screen);


	FOX_PumpEvents();	// odswiez eventy
	klawiatura = FOX_GetKeyState(NULL);	// odswiez

	}

//=== etap 3 wyjscie

	FOX_SetTimer(0,NULL);	// wylacz wszystkie 

	FOX_Quit();	// wyjscie 

	exit(0);
	return 0;

}
