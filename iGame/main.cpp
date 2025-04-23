#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>

#ifdef unix
#include <unistd.h>
#endif

#include "iGame.h"

//=== niezbedne, to jest rzeczywisty rozmiar rysowania i renderowania, to co widzimy w oknie moze byc skalowane

#define	APP_SCREEN_X	800
#define APP_SCREEN_Y	600
#define APP_SCREEN_BPP	32

static int audio_open = 0;
static Mix_Music *music = NULL;
static Mix_Chunk *wave = NULL;

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

//=== dodatkowe

CBitmap *pBitmap;	// rysunek
CBitmap	*pKon;	// kon
CEventEVT *pKonEVT;
CXmlFile *pXML;
CEventSND *pSND;

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
	if (wave) // zwalniamy dzwiek
	{
	    Mix_FreeChunk(wave);
	    wave = NULL;
	}

	if (Mix_PlayingMusic())
	{
		Mix_FadeOutMusic(1500);
		SDL_Delay(1500);
	}

	if (music)
	{
		Mix_FreeMusic(music);
		music = NULL;
	}

	if (audio_open)
	{
		Mix_CloseAudio();
		audio_open=0;
	}
	
	SDL_Quit();
}
//=== nasza glowna funkcja odpowiadajaca za wszystko

int AppRender(int iTimer)
{
    switch (eAppState)
    {
	case START:
	break;
    }

	// przerzucanie bufora na ekran	

	for (long h1=0; h1<480000; h1++)
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
	int 	iMouseX, iMouseY;
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
	iXSize = 800;
	iYSize = 600;
	iBpp = 32;

	pBackBuffer = NULL;
	if ((pBackBuffer = new unsigned char [1+((APP_SCREEN_X*APP_SCREEN_Y)*4)])==NULL) 
		printf("Error! Not enought memory for back buffer!\n");

	

	if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO)<0)
	{
		printf("Cannot initialize screen!\n");
		exit(1);
	}

	atexit(SDL_Quit);
	atexit(CleanUp);
	signal(SIGINT,exit);
	signal(SIGTERM,exit);

	/* Open the audio device */
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(2);
	} else {
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		printf("Opened audio at %d Hz %d bit %s, %d bytes audio buffer\n", audio_rate,
			(audio_format&0xFF),
			(audio_channels > 1) ? "stereo" : "mono", 
			audio_buffers );
	}
	audio_open = 1;

	/* Set the external music player, if any */
	Mix_SetMusicCMD(getenv("MUSIC_CMD"));

	/* Load the requested music file */
	music = Mix_LoadMUS("resource/music/music.ogg");
	if ( music == NULL ) {
		fprintf(stderr, "Couldn't load resource/music/music.ogg\n");
		exit(2);
	}

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

	// start timer

	desired=1;
	SDL_SetTimer(desired,ticktock);

	SDL_WM_SetCaption("Main","main");
    
	// ignore motion and mouse events
    
//	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
//	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
//	SDL_ShowCursor(SDL_DISABLE); // blokada standardowego kursora myszy
	SDL_PumpEvents();

	pBitmap = new CBitmap(800,600,"resource/img/pic.bmp");
	/* Play and then exit */
	Mix_FadeInMusic(music,looping,2000);

	pXML = new CXmlFile("spec/seq.xml");
	pXML->iCreateNodes();
    
	pKonEVT = new CEventEVT("resource/evt/bobul.evt","resource/evt/bobul.evt");

	wave = Mix_LoadWAV("resource/wav/wrozka.wav");

    pSND = new CEventSND("grama_sobie",1);
    pSND->Add("resource/wav/s01.wav");
    pSND->Add("resource/wav/s02.wav");
    pSND->Add("resource/wav/s03.wav");
    
    while ((Mix_PlayingMusic() || Mix_PausedMusic()) && sdlkeys[SDLK_ESCAPE]!=SDL_PRESSED)
    {
	SDL_GetMouseState(&iMouseX, &iMouseY);
	if (sdlkeys[SDLK_a]==SDL_PRESSED)  pSND->PlayNo(1);
	if (sdlkeys[SDLK_b]==SDL_PRESSED)  pSND->PlayRandom(ulTimer);

	pBitmap->Render(0,0,pBackBuffer);
	pKonEVT->Put(iMouseX, iMouseY,(unsigned int)(ulTimer/3)%18,(unsigned int)2,pBackBuffer);
	AppRender(0);
	SDL_PumpEvents();
	sdlkeys=(char*)SDL_GetKeyState(NULL);
//	memset(pBackBuffer,0,(APP_SCREEN_X*APP_SCREEN_Y)*4);
	printf("timer: %d\n", ulTimer);

    }
    delete pSND;
    
    delete pBitmap;
	delete pKonEVT;

	delete []pBackBuffer;
	SDL_ShowCursor(SDL_ENABLE);
	SDL_SetTimer(0,NULL);
	printf("timer: %d\n", ulTimer);
	printf("nodes: %d\n",pXML->iGetNodeCount());
	for (int i=0; i<pXML->iGetNodeCount(); i++) printf("::name: %s\n",pXML->cGetNodeName(i));
	delete pXML;
    
    return 0; // koniec programu
}
