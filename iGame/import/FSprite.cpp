// FSprite.cpp: implementation of the FSprite class.
//
//////////////////////////////////////////////////////////////////////

#include <fox.h>
#include <windows.h>
#include "FSprite.h"

// czy wszystkie informacje maja ladowac w dzienniku
// jezeli nie to wystarczy zakomentowac ta linie

#define debug_FSprite


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FSprite::FSprite(char csFilename[])
{

	long lDataLen;					// dlugosc pliku
	unsigned long ulOffset;			// offset w buforze
	unsigned char *ucTempBuffer;	// bufor tymczasowy
	unsigned long ulLicznikKlatek;	// licznik klatek do rozkodowania
	
	unsigned long a1,a2,a3;

	fprintf(stderr,"FSprite::new  csFilename=%s\n",csFilename);

	lDataLen = FOX_filesys_search(csFilename);

	if (lDataLen==0) // tutaj obsluga bledu
		fprintf(stderr,"[FOX]: blad! nie moge wczytac %s,\n",csFilename); 

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: alokacja FSprite:ucTempBuffer %d\n",lDataLen);
#endif

	ucTempBuffer=(unsigned char*) malloc(lDataLen);		// alokacja bufora 

#ifdef debug_FSprite
	if (!ucTempBuffer) fprintf(stderr,"[FOX]: za malo pamieci!\n");
#endif

	FOX_filesys_load_in(ucTempBuffer);

	ulIloscKlatek = (unsigned long)((ucTempBuffer[3]<<24)+(ucTempBuffer[2]<<16)+
					(ucTempBuffer[1]<<8)+(ucTempBuffer[0]));		// hmmm...ok!

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: ilosc klatek: %d\n",ulIloscKlatek);	// do sprawdzenia
#endif

	//=== alokacja tyle razy ile mamy klatek

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: alokacja wysokosci klatek...");
#endif
	
	uiWysokoscKlatki = (unsigned int*) malloc(ulIloscKlatek*sizeof(unsigned int));	// dla kazdej z osobna

#ifdef debug_FSprite
	fprintf(stderr,"ok!\n");
	fprintf(stderr,"[FOX]: alokacja szerokosci klatek...");
#endif

	uiSzerokoscKlatki = (unsigned int*) malloc(ulIloscKlatek*sizeof(unsigned int));

#ifdef debug_FSprite
	fprintf(stderr,"ok!\n");
	fprintf(stderr,"[FOX]: alokacja surface dla obrazu..");
#endif

	fsObrazKlatki = new FOX_Surface* [ulIloscKlatek];	// alokacja wskaznikow

#ifdef debug_FSprite
	fprintf(stderr,"ok!\n");
#endif

	ulOffset=4;		// przeskok 

	for (ulLicznikKlatek=0; ulLicznikKlatek<ulIloscKlatek; ulLicznikKlatek++)
	{

#ifdef debug_FSprite
	fprintf(stderr,"Klatka : %d\n",ulLicznikKlatek);
	fprintf(stderr,"Offset : %d\n",ulOffset);
#endif
		

		uiWysokoscKlatki[ulLicznikKlatek] = (unsigned int)
			( (ucTempBuffer[ulOffset+3]<<24) + (ucTempBuffer[ulOffset+2]<<16) + 
			  (ucTempBuffer[ulOffset+1]<<8) + (ucTempBuffer[ulOffset]) );

#ifdef debug_FSprite
	fprintf(stderr,"Wysokosc klatki: %d\n",uiWysokoscKlatki[ulLicznikKlatek]);
#endif


		uiSzerokoscKlatki[ulLicznikKlatek] = (unsigned int)
			( (ucTempBuffer[ulOffset+7]<<24) + (ucTempBuffer[ulOffset+6]<<16) +
			  (ucTempBuffer[ulOffset+5]<<8) + (ucTempBuffer[ulOffset+4]));

#ifdef debug_FSprite
	fprintf(stderr,"Szerokosc klatki: %d\n",uiSzerokoscKlatki[ulLicznikKlatek]);
#endif

		ulOffset+=8;	// zwiekszony o 2x unsigned int

		// tutaj alokuj surface

#ifdef debug_FSprite
	fprintf(stderr,"Alokacja surface...\n");
	fprintf(stderr,"	Szerokosc klatki: %d\n",uiSzerokoscKlatki[ulLicznikKlatek]);
	fprintf(stderr,"	Wysokosc klatki: %d\n",uiWysokoscKlatki[ulLicznikKlatek]);
#endif

		fsObrazKlatki[ulLicznikKlatek] = 	
			FOX_CreateRGBSurface(FOX_SWSURFACE,
			uiSzerokoscKlatki[ulLicznikKlatek],
			uiWysokoscKlatki[ulLicznikKlatek],16,0,0,0,0);	// tutaj obraz

#ifdef debug_FSprite
	fprintf(stderr,"ok!\n");
	fprintf(stderr,"	Szerokosc klatki: %d\n",uiSzerokoscKlatki[ulLicznikKlatek]);
	fprintf(stderr,"	Wysokosc klatki: %d\n\n",uiWysokoscKlatki[ulLicznikKlatek]);
	fprintf(stderr,"Kopiowanie na surface...\n");
#endif

		// skopiuj z bufora tymczasowego na surface

		for (a1=0; a1<uiWysokoscKlatki[ulLicznikKlatek]; a1++)
		{
			for (a2=0,a3=0; a3<uiSzerokoscKlatki[ulLicznikKlatek]; a2+=4,a3++)
			{
				if (ucTempBuffer[ulOffset+(a1*(4*uiSzerokoscKlatki[ulLicznikKlatek]))+a2+3]!=0)
				FOX_pixelRGBA(fsObrazKlatki[ulLicznikKlatek], (short)a3,(short)a1,		
					ucTempBuffer[ulOffset+(a1*(4*uiSzerokoscKlatki[ulLicznikKlatek]))+a2+2],
					ucTempBuffer[ulOffset+(a1*(4*uiSzerokoscKlatki[ulLicznikKlatek]))+a2+1], 
					ucTempBuffer[ulOffset+(a1*(4*uiSzerokoscKlatki[ulLicznikKlatek]))+a2],
					ucTempBuffer[ulOffset+(a1*(4*uiSzerokoscKlatki[ulLicznikKlatek]))+a2+3]);
			}
		}

#ifdef debug_FSprite
	fprintf(stderr,"	Szerokosc klatki: %d\n",uiSzerokoscKlatki[ulLicznikKlatek]);
	fprintf(stderr,"	Wysokosc klatki: %d\n\n",uiWysokoscKlatki[ulLicznikKlatek]);
#endif


#ifdef debug_FSprite
	fprintf(stderr,"ok!\n\n");
#endif

		ulOffset+= (uiWysokoscKlatki[ulLicznikKlatek]*uiSzerokoscKlatki[ulLicznikKlatek])*4;

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: ulOffset ADD\n");
	fprintf(stderr,"	Szerokosc klatki: %d\n",uiSzerokoscKlatki[ulLicznikKlatek]);
	fprintf(stderr,"	Wysokosc klatki: %d\n\n",uiWysokoscKlatki[ulLicznikKlatek]);
#endif

	}

#ifdef debug_FSprite

	for (a1=0;a1<ulIloscKlatek; a1++)
	{
	fprintf(stderr,"Klatka : %d\n",a1);
	fprintf(stderr,"Szerokosc klatki: %d\n",uiSzerokoscKlatki[a1]);
	fprintf(stderr,"Wysokosc klatki: %d\n",uiWysokoscKlatki[a1]);
	}
#endif

		// tutaj eventy

		ulIloscZdarzen = (unsigned long)
			( (ucTempBuffer[ulOffset+3]<<24) + (ucTempBuffer[ulOffset+2]<<16) +
			  (ucTempBuffer[ulOffset+1]<<8) + (ucTempBuffer[ulOffset]));

#ifdef debug_FSprite
		fprintf(stderr,"[FOX]: ilosc zdarzen: %d\n",ulIloscZdarzen);
#endif

		// zwieksz offset

		ulOffset+=4;

	// zaalokuj tyle pamieci ile jest potrzebne na zdarzenia

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: alokacja pamieci na zdarzenia...");
#endif

	fevZdarzenia = new FEvent* [ulIloscZdarzen];

#ifdef debug_FSprite
	fprintf(stderr,"ok!\n");
#endif

	// petla odczytu zdarzen


	for (a1=0; a1<ulIloscZdarzen; a1++)
	{

#ifdef debug_FSprite
	fprintf(stderr,"Offset : %d\n",ulOffset);
#endif
	
	fevZdarzenia[a1]= new FEvent;
	fevZdarzenia[a1]->sNazwaZdarzeniaGFX=(unsigned char*)malloc(256);	// alokuj 

			
	memcpy(fevZdarzenia[a1]->sNazwaZdarzeniaGFX,&ucTempBuffer[ulOffset],256); 

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: Nazwa zdarzenia #%d:	%s\n",a1,fevZdarzenia[a1]->sNazwaZdarzeniaGFX);
#endif

	ulOffset+=256;	// zwieksz o nazwa zdarzenia

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: Offset : %d\n",ulOffset);
#endif

	// odczytaj ilosc klatek w zdarzeniu

		fevZdarzenia[a1]->ulLiczbaKlatek = (unsigned long)
			( (ucTempBuffer[ulOffset+3]<<24) + (ucTempBuffer[ulOffset+2]<<16) +
			  (ucTempBuffer[ulOffset+1]<<8) + (ucTempBuffer[ulOffset]));

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: ilosc klatek : %d\n",fevZdarzenia[a1]->ulLiczbaKlatek);
#endif

	ulOffset+=4;	// przeskok o unsigned long

	// zaalokuj pamiec na klatki

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: alokacja pamieci na wspolrzedne...");
#endif

	fevZdarzenia[a1]->iXKlatki = 
		(int*) malloc (fevZdarzenia[a1]->ulLiczbaKlatek*sizeof(int));

	fevZdarzenia[a1]->iYKlatki = 
		(int*) malloc (fevZdarzenia[a1]->ulLiczbaKlatek*sizeof(int));

#ifdef debug_FSprite
	fprintf(stderr,"ok!\n");
#endif

//	ulOffset+=8;	// x i y klatki

	// zaalokuj na liste animacji

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: alokacja pamieci na liste klatek...");
#endif

	fevZdarzenia[a1]->uiNrKlatki = 
		(unsigned int*) malloc (fevZdarzenia[a1]->ulLiczbaKlatek*sizeof(unsigned int));

#ifdef debug_FSprite
	fprintf(stderr,"ok!\n");
#endif

	for (a2=0; a2<fevZdarzenia[a1]->ulLiczbaKlatek; a2++)
	{

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: Offset : %d\n",ulOffset);
#endif

		fevZdarzenia[a1]->iXKlatki[a2]= (int)
			( (ucTempBuffer[ulOffset+3]<<24) + (ucTempBuffer[ulOffset+2]<<16) +
			  (ucTempBuffer[ulOffset+1]<<8) + (ucTempBuffer[ulOffset]));

		fevZdarzenia[a1]->iYKlatki[a2]= (int)
			( (ucTempBuffer[ulOffset+7]<<24) + (ucTempBuffer[ulOffset+6]<<16) +
			  (ucTempBuffer[ulOffset+5]<<8) + (ucTempBuffer[ulOffset+4]));

		fevZdarzenia[a1]->uiNrKlatki[a2]= (unsigned int)
			( (ucTempBuffer[ulOffset+11]<<24) + (ucTempBuffer[ulOffset+10]<<16) +
			  (ucTempBuffer[ulOffset+9]<<8) + (ucTempBuffer[ulOffset+8]));

		ulOffset+=12;	// x,y, nr

#ifdef debug_FSprite
	fprintf(stderr,"[FOX]: Klatka %d X:%d Y:%d Nr:%d\n",
		a2,
		fevZdarzenia[a1]->iXKlatki[a2],
		fevZdarzenia[a1]->iYKlatki[a2],
		fevZdarzenia[a1]->uiNrKlatki[a2]);
#endif

		// sprawdz czy to tej klatki jest dzwiek

		fevZdarzenia[a1]->ucCzyOdtwarzac=ucTempBuffer[ulOffset];	// czy odtwarzac
		
		ulOffset++;
	
	}
}
	
	// zwolnij bufor na samym koncu

#ifdef debug_FSprite
	fprintf(stderr,"ok!\n");
#endif

	free(ucTempBuffer);

}

FSprite::~FSprite()
{
	free (uiSzerokoscKlatki);
	free (uiWysokoscKlatki);

}

void FSprite::Put(FOX_Surface *fsDestination, 
			 unsigned long ulXScreen, unsigned long ulYScreen, 
			 unsigned long ulFrame)
{

	FOX_Rect	frRectangle;

	frRectangle.x=(short)ulXScreen; frRectangle.y=(short)ulYScreen;
	
	frRectangle.w=uiSzerokoscKlatki[ulFrame];
	frRectangle.h=uiWysokoscKlatki[ulFrame];

#ifdef debug_FSprite
	fprintf(stderr,"ulFrame: %d\n",ulFrame);
	
	fprintf(stderr,"frRectangle.x: %d\n",frRectangle.x);
	fprintf(stderr,"frRectangle.y: %d\n",frRectangle.y);
	fprintf(stderr,"frRectangle.h: %d\n",frRectangle.h);
	fprintf(stderr,"frRectangle.w: %d\n",frRectangle.w);
#endif

	FOX_BlitSurface((FOX_Surface*)fsObrazKlatki[ulFrame],NULL,fsDestination,&frRectangle);


}