#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>

#ifdef unix
#include <unistd.h>
#endif

#include "/iGame/iGame.h"

//=== niezbedne, to jest rzeczywisty rozmiar rysowania i renderowania, to co widzimy w oknie moze byc skalowane

#define	APP_SCREEN_X	1024
#define APP_SCREEN_Y	768
#define APP_SCREEN_BPP	32

//=== dla myszki

int 	iMouseX, iMouseY;
bool 	bLeft, bRight, bCenter;	// przyciski myszy
bool	bLastLeft, bLastRight, bLastCenter;	// do okreslenia, czy przycisk zostal zwolniony

//=== aktualne wymiary okna 

int iXSize;
int iYSize;
int iBpp;

SDL_Surface *pMainSurface;
bool bFullscreen;	// czy aplikacja na calym ekranie

// to jest wskaznik do naszego bufora, ktorzy przerzucamy na ekran
// tablica i wszystkie operacje zawsze sa w formacie RGBA, natomiast jezeli tryb graficzny jest inny to w locie dokonujemy konwersji np. na 16bpp
// oraz skalowania np do 1024x512

unsigned char	*pBackBuffer;	

//=== niezbedne, ale trzeba dodac wlasne

enum APP_STAT
{
    START,
    END
} eAppState;

//=== moduly aplikacji

int iReturnVal;	// podreczne, do przenoszenia wyniku pomiedzy modulami

//=== dodatkowe

CBitmap *pGrid;	// tlo

CBitmap *pKursorMyszy;

int 	iX, iY;
double	dA, dB;

//=== odliczanie sekund

unsigned long ulTimer;
unsigned long ulTimer10; 
unsigned long ulTimer100;

static Uint32 ticktock(Uint32 interval)
{
	ulTimer++;
	ulTimer10 = (unsigned long)(ulTimer/10);
	ulTimer100= (unsigned long)(ulTimer10/10);
	return (interval);
}

//=== callback

static Uint32 callback(Uint32 interval, void *param)
{
	ulTimer++;
	return (interval);
}

//=== to na koncu, zamyka muzyke etc

void CleanUp(void)
{
	SDL_Quit();
}
//=== nasza glowna funkcja odpowiadajaca za wszystko

int AppRender(int iTimer)
{
    switch (eAppState)
    {

	//=== plansza tytulowa ===

	case START:

	    pGrid->Render(0,0,pBackBuffer);
	    pKursorMyszy->Render(iMouseX,iMouseY,pBackBuffer);

	    if (!bLeft&&bLastLeft) 
		{
			eAppState = END;
			bLeft = bLastLeft = false;	// resetowanie stanu myszy
		}

	break;

	} // eAppState

	// przerzucanie bufora na ekran	

	for (long h1=0; h1<786432; h1++)
	{

	((int*)pMainSurface->pixels)[h1] = (unsigned int)
	((pBackBuffer[(h1<<2)]<<16)+
	 (pBackBuffer[(h1<<2)+1]<<8)+
	 (pBackBuffer[(h1<<2)+2]));

	}

	SDL_Flip(pMainSurface);

}


//=== nasz glowny program ktorego nie zmieniamy

int main(int gArgc, char **gArgv)
{
	int	audio_rate=22050;
	Uint16	audio_format=AUDIO_S16;
	int	audio_channels=2;
	int	audio_buffers=4096;
	int	looping=0;
	int	interactive=0;
	int	i,desired;
	char 	*sdlkeys;		// hook do klawiatury

	eAppState = START;

	bFullscreen = false;
	iXSize = 1024;
	iYSize = 768;
	iBpp = 32;

	pBackBuffer = NULL;
	if ((pBackBuffer = new unsigned char [1+((APP_SCREEN_X*APP_SCREEN_Y)*4)])==NULL) 
		printf("Error! Not enought memory for back buffer!\n");

	

	if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO)<0)
	{
		printf("Cannot initialize screen!\n");
		exit(1);
	}

	atexit(SDL_Quit);
	atexit(CleanUp);
	signal(SIGINT,exit);
	signal(SIGTERM,exit);

	if (bFullscreen)
	{    
		pMainSurface = SDL_SetVideoMode(iXSize, iYSize, iBpp, SDL_FULLSCREEN);
	}
	else
	{
		pMainSurface = SDL_SetVideoMode(iXSize, iYSize, iBpp, SDL_SWSURFACE);
	}

	if (pMainSurface==NULL)
	{
		printf("Cannot set video mode : %d\n",SDL_GetError());
	}

	// inicjalizacji modulow
	
//	pMainMenu = new CMainMenu();
//	pSelectMenu = new CSelectMenu();
//	pEditMenu = new CEditMenu();

	// start timer

	desired=1;
	SDL_SetTimer(desired,ticktock);
	SDL_ShowCursor(SDL_DISABLE);	// nie wyswietlaj standardowego kursora myszy
	SDL_WM_SetCaption("Main","main");
    
	// ignore motion and mouse events
    
	SDL_PumpEvents();

	pGrid = new CBitmap("resource/img/grid.tga",TGA);

	// inicjalizacja kursorow myszki

	pKursorMyszy = new CBitmap("resource/img/myszka/cursor3.tga",TGA);

	/* Play and then exit */

    while (eAppState!=END)
    {

	// pobierz parametry myszki

	SDL_GetMouseState(&iMouseX, &iMouseY);
	if (SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(1)) bLeft = true; else bLeft = false;
	if (SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(2)) bCenter = true; else bCenter = false;
	if (SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(3)) bRight = true; else bRight = false;

	AppRender(0);

	SDL_PumpEvents();

	sdlkeys=(char*)SDL_GetKeyState(NULL);
//	memset(pBackBuffer,0,(APP_SCREEN_X*APP_SCREEN_Y)*4);
	printf("timer: %d\n", ulTimer);

	// sprawdzenie, czy nacisnieto esc w etapie edycji obrazu
	
	if (sdlkeys[SDLK_ESCAPE]==SDL_PRESSED) 
	{
		eAppState=END;
	}
	
	// zapamietaj stan myszki
	
	bLastLeft = bLeft;
	bLastCenter = bCenter;
	bLastRight = bRight;
    }
   
    delete pGrid;
    delete pKursorMyszy;

	// kasowanie tego przycisku wywala program na maku, dziala na linuxie

    delete []pBackBuffer;

	// deinicjalizacja modulow
	
//	delete pMainMenu;
//	delete pSelectMenu;
//	delete pEditMenu;
	
    SDL_ShowCursor(SDL_ENABLE);
    SDL_SetTimer(0,NULL);
    printf("timer: %d\n", ulTimer);
    
    return 0; // koniec programu
}
