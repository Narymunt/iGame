//=== just pure stuff

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include <FOX.h>
#include <FOX_Audio.h>

#include "Trawa.h"
#include "Henryk.h"
#include "Zagroda.h"
#include "Diament.h"
#include "Dynia.h"
#include "MurekB.h"

// 0 pusto
// 1 trawa
// 2 diament
// 3 dynie
// 4 murek bialy

long h1,h2,h3,h4,h5;

int mx,my;

unsigned long r,g,b;


unsigned char *kursor_r;
unsigned char *kursor_g;
unsigned char *kursor_b;

unsigned char *klawiatura;

int mouse_x, mouse_y;

FOX_Event event;

FOX_Surface *screen;
FOX_Surface *background;	
FOX_Surface *mouse_cursor;
FOX_Surface *mouse_save;

unsigned char *buffer_r;
unsigned char *buffer_g;
unsigned char *buffer_b;

unsigned char	*databuffer;
long datalen;

// tutaj ilosci

#define	ILE_DYNIE	5

// dane gry

Trawa	*trawa;
Henryk	*prosiak;
Zagroda *zagroda;
Diament *diamenty[5];
Dynia	*dynie[ILE_DYNIE];
MurekB	*murek_bialy;

int iTimer;

FILE	*plik;

//=== odswiezanie

void rysuj_dynie(void)
{

	for (h1=0;h1<ILE_DYNIE; h1++)
	{
	
	// czy pod spodem pusto ? 	

	if (zagroda->teren_global[(80*(dynie[h1]->y_global+zagroda->offset_y+1))+dynie[h1]->x_global+zagroda->offset_x]==0)
	dynie[h1]->dst_y_global=dynie[h1]->y_global+1;

	// pchamy w lewo

	if (dynie[h1]->x_global>dynie[h1]->dst_x_global&&
		dynie[h1]->y_global==dynie[h1]->dst_y_global)
	{
		dynie[h1]->x_local-=8;	// w dol

		if (dynie[h1]->x_local==-48)
		{
			dynie[h1]->x_local=0;
			dynie[h1]->x_global--;		// o jedno w lewo
			
			// zapisz na plansze

			zagroda->teren_global[(80*(dynie[h1]->y_global+zagroda->offset_y))+dynie[h1]->x_global+zagroda->offset_x]=3;
			zagroda->teren_global[(80*(dynie[h1]->y_global+zagroda->offset_y))+dynie[h1]->x_global+zagroda->offset_x+1]=0;
		}
	}

	else

	// pchamy w prawo

	if (dynie[h1]->x_global<dynie[h1]->dst_x_global&&
		dynie[h1]->y_global==dynie[h1]->dst_y_global)
	{
		dynie[h1]->x_local+=8;	// w dol

		if (dynie[h1]->x_local==48)
		{
			dynie[h1]->x_local=0;
			dynie[h1]->x_global++;		// o jedno w lewo
			
			// zapisz na plansze

			zagroda->teren_global[(80*(dynie[h1]->y_global+zagroda->offset_y))+dynie[h1]->x_global+zagroda->offset_x]=3;
			zagroda->teren_global[(80*(dynie[h1]->y_global+zagroda->offset_y))+dynie[h1]->x_global+zagroda->offset_x-1]=0;
		}
	}

	else 

	// ruch ?

	if (dynie[h1]->y_global<dynie[h1]->dst_y_global)
	{
		dynie[h1]->y_local+=8;	// w dol
				
		if (dynie[h1]->y_local==48)
		{
			dynie[h1]->y_local=0;
			dynie[h1]->y_global++;		// o jedno w dol
			
			// zapisz na plansze

			zagroda->teren_global[(80*(dynie[h1]->y_global+zagroda->offset_y))+dynie[h1]->x_global+zagroda->offset_x]=3;
			zagroda->teren_global[(80*(dynie[h1]->y_global+zagroda->offset_y-1))+dynie[h1]->x_global+zagroda->offset_x]=0;
		}
			
	}


	// na plansze

	zagroda->teren_global[(80*(dynie[h1]->y_global+zagroda->offset_y))+dynie[h1]->x_global+zagroda->offset_x]=3;
	
	// rysowanie
		dynie[h1]->put((48*dynie[h1]->x_global)+dynie[h1]->x_local+16,
					   (48*dynie[h1]->y_global)+dynie[h1]->y_local+16,
					    background,screen);

	}
}

// diamenty

void rysuj_diamenty(void)
{

	for (h1=0;h1<5; h1++)
	{
	
	// czy pod spodem pusto ? 	

	if (zagroda->teren_global[(80*(diamenty[h1]->y_global+zagroda->offset_y+1))+diamenty[h1]->x_global+zagroda->offset_x]==0)
	diamenty[h1]->dst_y_global=diamenty[h1]->y_global+1;
	
	// ruch ?

	if (diamenty[h1]->y_global<diamenty[h1]->dst_y_global)
	{
		diamenty[h1]->y_local+=8;	// w dol
				
		if (diamenty[h1]->y_local==48)
		{
			diamenty[h1]->y_local=0;
			diamenty[h1]->y_global++;		// o jedno w dol
			
			// zapisz na plansze

			zagroda->teren_global[(80*(diamenty[h1]->y_global+zagroda->offset_y))+diamenty[h1]->x_global+zagroda->offset_x]=2;
			zagroda->teren_global[(80*(diamenty[h1]->y_global+zagroda->offset_y-1))+diamenty[h1]->x_global+zagroda->offset_x]=0;
		}
			
	}

	// na plansze

	zagroda->teren_global[(80*(diamenty[h1]->y_global+zagroda->offset_y))+diamenty[h1]->x_global+zagroda->offset_x]=2;

	// rysowanie
		diamenty[h1]->put((iTimer>>1)%4,(48*diamenty[h1]->x_global)+diamenty[h1]->x_local+16,
						  (48*diamenty[h1]->y_global)+diamenty[h1]->y_local+16,
						  background,screen);

		iTimer+=3;
	}
}

void rysuj_zagroda(void)
{

	// rysowanie planszy

	for (h1=0;h1<10;h1++)
	{
		for (h2=0;h2<16;h2++)
		{
			// trawa
			
			if (zagroda->teren_global[(80*(h1+zagroda->offset_y))+h2+zagroda->offset_x]==1)
			trawa->put_Trawa(h2*48+16,h1*48+16,background);

			// murek bialy

			if (zagroda->teren_global[(80*(h1+zagroda->offset_y))+h2+zagroda->offset_x]==5)
			murek_bialy->put(h2*48+16,h1*48+16,background);

			
		}
	}
}


void rysuj_stworzenia(void)
{

		// rusz go
	
	if (prosiak->x_global<prosiak->dst_x_global)	// w prawo
	{
		
		zagroda->teren_global[(80*prosiak->y_global)+prosiak->x_global]=0; // pusto		
		
		prosiak->x_local+=8;
		if (prosiak->x_local==48) 
		{
			prosiak->x_global++;
			prosiak->x_local=0;
		}
	}

	if (prosiak->x_global>prosiak->dst_x_global)	// w lewo
	{
		zagroda->teren_global[(80*prosiak->y_global)+prosiak->x_global]=0; // pusto		
		
		prosiak->x_local-=8;
		if (prosiak->x_local==-48)
		{
			prosiak->x_global--;
			prosiak->x_local=0;
		}
	}

	if (prosiak->y_global<prosiak->dst_y_global)	// w dol
	{
		
		zagroda->teren_global[(80*prosiak->y_global)+prosiak->x_global]=0; // pusto		
		
		prosiak->y_local+=8;
		if (prosiak->y_local==48)
		{
			prosiak->y_global++;
			prosiak->y_local=0;
		}
	}

	if (prosiak->y_global>prosiak->dst_y_global)	// w dol
	{
		zagroda->teren_global[(80*prosiak->y_global)+prosiak->x_global]=0; // pusto		

		prosiak->y_local-=8;
		if (prosiak->y_local==-48)
		{
		prosiak->y_global--;
		prosiak->y_local=0;
		}

	}


	// umiesc prosiaka
	
	zagroda->teren_global[(80*prosiak->y_global)+prosiak->x_global]=255;	

	// rysowanie postaci

	for (h1=0;h1<10;h1++)
	{
		for (h2=0;h2<16;h2++)
		{
			
			// prosiak

			if (zagroda->teren_global[(80*(h1+zagroda->offset_y))+h2+zagroda->offset_x]==255)
			{

//					trawa->put_Trawa(h2*48+16,h1*48+16,background);
					prosiak->put_Henryk(h2*48+prosiak->x_local+16,
										h1*48+prosiak->y_local+16,screen,background);
//					FOX_BlitSurface(prosiak->stoi,&srcrect,screen,&prosiak->image_rectangle);				
			}
			

		}
	}


}

//=== do myszy

void get_bg(FOX_Surface *surface, int x, int y) 
{
	FOX_Rect src; 
	FOX_Rect dst; 
	 
	src.x = x; 
	src.y = y; 
	src.w = surface->w; 
	src.h = surface->h; 
 
	dst.x = 0; 
	dst.y = 0; 
	dst.w = surface->w; 
	dst.h = surface->h; 
	FOX_BlitSurface(screen, &src, surface, &dst); 
}

void RS_Blit(FOX_Surface *bitmap, Sint16 x, Sint16 y) 
{
	
	FOX_Rect dest; 
 
	dest.x = x; 
	dest.y = y; 
	dest.w = bitmap->w; 
	dest.h = bitmap->h; 
	FOX_BlitSurface(bitmap, NULL, screen, &dest); 
} 

//=== funkcja glowna

main (int argc, char **argv)
{

	if ( FOX_Init(FOX_INIT_VIDEO) < 0 ) {
		
		fprintf(stderr, "Couldn't initialize FOX: %s\n",FOX_GetError());
		exit(2);
	}

	atexit(FOX_Quit);

	screen = FOX_SetVideoMode(800, 600, 16,
			(FOX_FULLSCREEN|FOX_SWSURFACE|FOX_ASYNCBLIT));
	
	if ( screen == NULL ) {
		fprintf(stderr, "Couldn't set video mode %dx%d: %s\n",
				800, 600, FOX_GetError());
		exit(3);
	}
	
	FOX_WM_SetCaption("Henryk", "Henryk");	// tytul okienka

	// ignoruj mysz i zmiane okna
	
	FOX_EventState(FOX_ACTIVEEVENT, FOX_ENABLE);
	FOX_EventState(FOX_MOUSEMOTION, FOX_IGNORE);
	
	FOX_ShowCursor(0);	// schowaj mysz

	FOX_filesys_archive("henryk.fox");   

	// === prosiak stoi

	prosiak = new Henryk;

	// trawa

	trawa = new Trawa;

	// murek bialy

	murek_bialy = new MurekB;

	// == diamenty

	for (h1=0;h1<5;h1++) diamenty[h1] = new Diament;

	diamenty[0]->x_global=1; diamenty[0]->y_global=1;
	diamenty[1]->x_global=1; diamenty[1]->y_global=3;
	diamenty[2]->x_global=1; diamenty[2]->y_global=5;
	diamenty[3]->x_global=7; diamenty[3]->y_global=1;
	diamenty[4]->x_global=9; diamenty[4]->y_global=1;

	// === dynie

	for (h1=0;h1<ILE_DYNIE;h1++) dynie[h1] = new Dynia;

	dynie[0]->x_global=5; dynie[0]->y_global=1;
	dynie[0]->dst_x_global=5; dynie[0]->dst_y_global=1;
	
	dynie[1]->x_global=5; dynie[1]->y_global=2;
	dynie[1]->dst_x_global=5; dynie[1]->dst_y_global=2;

	dynie[2]->x_global=5; dynie[2]->y_global=3;	
	dynie[2]->dst_x_global=5; dynie[2]->dst_y_global=3;	
	
	dynie[3]->x_global=5; dynie[3]->y_global=4;
	dynie[3]->dst_x_global=5; dynie[3]->dst_y_global=4;
	
	dynie[4]->x_global=5; dynie[4]->y_global=5;
	dynie[4]->dst_x_global=5; dynie[4]->dst_y_global=5;

	// == panel - od razu ladowany jako tlo

	background = FOX_CreateRGBSurface(FOX_HWSURFACE,800,600,16,0,0,0,0);

	buffer_r = (unsigned char*) malloc(480000);
	buffer_g = (unsigned char*) malloc(480000);
	buffer_b = (unsigned char*) malloc(480000);

	FOX_filesys_load(buffer_r,"panel.r");
	FOX_filesys_load(buffer_g,"panel.g");
	FOX_filesys_load(buffer_b,"panel.b");

	for (h1=0;h1<600;h1++)
	{
		for (h2=0; h2<800; h2++)
		{
			FOX_pixelRGBA(background, h2,h1,buffer_r[(h1*800)+h2],
				buffer_g[(h1*800)+h2], buffer_b[(h1*800)+h2],255);
		}
	}

	free(buffer_r);
	free(buffer_g);
	free(buffer_b);


	
	zagroda = new Zagroda;



	klawiatura = FOX_GetKeyState(NULL);	// przypisz 

	zagroda->offset_x=0;
	zagroda->offset_y=0;


	rysuj_zagroda();

	while (klawiatura[FOXK_ESCAPE]!=FOX_PRESSED) 
	{

		if (klawiatura[FOXK_LEFT]==FOX_PRESSED)		// w lewo
		{
			
			// jezeli pusto albo trawa to idzie

			if (prosiak->x_global>0&&
				prosiak->x_local==0&&
				prosiak->y_local==0&&
				zagroda->teren_global[(80*(prosiak->y_global+zagroda->offset_y))+prosiak->x_global+zagroda->offset_x-1]<3)
			{
				// czy tutaj nie spada dynia 
					
				bool cos_leci=false;

				for (h1=0;h1<ILE_DYNIE;h1++)
				{
					if (dynie[h1]->dst_x_global==prosiak->x_global-1&&
						dynie[h1]->dst_y_global==prosiak->y_global)
						cos_leci=true;
				}

				if (!cos_leci) prosiak->dst_x_global--;
			}

			else

			// jest tam dynia i mozna ja pchac

			if (prosiak->x_global>0&&
				prosiak->x_local==0&&
				prosiak->y_local==0&&
				zagroda->teren_global[(80*(prosiak->y_global+zagroda->offset_y))+prosiak->x_global+zagroda->offset_x-1]==3&&
				zagroda->teren_global[(80*(prosiak->y_global+zagroda->offset_y))+prosiak->x_global+zagroda->offset_x-2]==0)
			{
				
				for (h1=0;h1<ILE_DYNIE;h1++)	// ktora popchamy ?
				{
					if (dynie[h1]->x_global==prosiak->x_global-1&&
						dynie[h1]->y_global==prosiak->y_global&&
						dynie[h1]->dst_x_global==dynie[h1]->x_global&&
						dynie[h1]->dst_y_global==dynie[h1]->y_global&&
						zagroda->teren_global[(80*(dynie[h1]->y_global+zagroda->offset_y+1))+dynie[h1]->x_global+zagroda->offset_x]!=0&&
						dynie[h1]->y_local==0)
					{
						prosiak->dst_x_global--;
						dynie[h1]->dst_x_global--;
					}
				}
			}

		}
		
		else
		
		if (klawiatura[FOXK_RIGHT]==FOX_PRESSED)	// w prawo
		{

			// jezeli pusto, albo trawa lub diament to idzie

			if (prosiak->x_global<15&&
				prosiak->x_local==0&&
				prosiak->y_local==0&&
				zagroda->teren_global[(80*(prosiak->y_global+zagroda->offset_y))+prosiak->x_global+zagroda->offset_x+1]<3)
			{
				// czy tutaj nie spada dynia 
					
				bool cos_leci=false;

				for (h1=0;h1<ILE_DYNIE;h1++)
				{
					if (dynie[h1]->dst_x_global==prosiak->x_global+1&&
						dynie[h1]->dst_y_global==prosiak->y_global)
						cos_leci=true;
				}

				if (!cos_leci) prosiak->dst_x_global++;
			}

			else

			// jest tam dynia i mozna ja pchac

			if (prosiak->x_global<15&&
				prosiak->x_local==0&&
				prosiak->y_local==0&&
				zagroda->teren_global[(80*(prosiak->y_global+zagroda->offset_y))+prosiak->x_global+zagroda->offset_x+1]==3&&
				zagroda->teren_global[(80*(prosiak->y_global+zagroda->offset_y))+prosiak->x_global+zagroda->offset_x+2]==0)
			{
				
				for (h1=0;h1<ILE_DYNIE;h1++)	// ktora popchamy ?
				{
					if (dynie[h1]->x_global==prosiak->x_global+1&&
						dynie[h1]->y_global==prosiak->y_global&&
						dynie[h1]->dst_x_global==dynie[h1]->x_global&&
						dynie[h1]->dst_y_global==dynie[h1]->y_global&&
						zagroda->teren_global[(80*(dynie[h1]->y_global+zagroda->offset_y+1))+dynie[h1]->x_global+zagroda->offset_x]!=0&&
						dynie[h1]->y_local==0)
					{
						prosiak->dst_x_global++;
						dynie[h1]->dst_x_global++;
					}
				}
			}

		
		}
		
		else
		
		if (klawiatura[FOXK_UP]==FOX_PRESSED)
		{
			
			// jezeli pusto, albo trawa lub diament to idzie
			
			if (prosiak->y_global>0&&
				prosiak->x_local==0&&
				prosiak->y_local==0&&
				zagroda->teren_global[(80*(prosiak->y_global+zagroda->offset_y-1))+prosiak->x_global+zagroda->offset_x]<3)
			{
				// czy tutaj nie spada dynia 
					
				bool cos_leci=false;

				for (h1=0;h1<ILE_DYNIE;h1++)
				{
					if (dynie[h1]->dst_x_global==prosiak->x_global&&
						dynie[h1]->dst_y_global==prosiak->y_global-1)
						cos_leci=true;
				}

				if (!cos_leci) prosiak->dst_y_global--;
			}

		
		}

		else
		
		if (klawiatura[FOXK_DOWN]==FOX_PRESSED)
		{
			if (prosiak->y_global<9&&
				prosiak->x_local==0&&
				prosiak->y_local==0&&
				zagroda->teren_global[(80*(prosiak->y_global+zagroda->offset_y+1))+prosiak->x_global+zagroda->offset_x]<3)
				prosiak->dst_y_global++;
		}

		FOX_PollEvent(&event);
	
		FOX_BlitSurface(background,0,screen,0);	
	
		rysuj_stworzenia();	
		rysuj_diamenty();
		rysuj_dynie();


//		plik=fopen("plansza.bin","wb");
//		fwrite(&zagroda->teren_global,1,4000,plik);
//		fclose(plik);

	FOX_UpdateRect(screen,0,0,0,0);

	FOX_PumpEvents();	// odswiez eventy
	klawiatura = FOX_GetKeyState(NULL);	// odswiez

	}




	FOX_Quit();

	exit(0);
	return 0;

}
