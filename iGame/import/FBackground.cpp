// FBackground.cpp: implementation of the FBackground class.
//
//////////////////////////////////////////////////////////////////////

#include "fox.h"
#include <windows.h>
#include "FBackground.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// tutaj od razu wczytuj

FBackground::FBackground(char csFilename[])
{
	unsigned long a1,a2, a3, a4;
	long lDataLen;					// dlugosc pliku
	unsigned char *ucTempBuffer;	// bufor tymczasowy
	

	lDataLen = FOX_filesys_search(csFilename);

	if (lDataLen==0) // tutaj obsluga bledu
		fprintf(stderr,"[FOX]: blad! nie moge wczytac %s,",csFilename); 

	ucTempBuffer=(unsigned char*) malloc(lDataLen);		// alokacja bufora 

	FOX_filesys_load_in(ucTempBuffer);

	image = FOX_CreateRGBSurface(FOX_SWSURFACE,800,600,16,0,0,0,0);	// tutaj obraz

	for (a1=0,a3=0;a1<600;a1++,a3+=3)
	{
		for (a2=0,a4=0; a2<800; a2++,a4+=3)
		{
			
			// tutaj od razu jest ewentualna konwersja
			
			FOX_pixelRGBA(image, (short)a2,(short)a1,		
				ucTempBuffer[(a1*2400)+a4],
				ucTempBuffer[(a1*2400)+a4+1], 
				ucTempBuffer[(a1*2400)+a4+2],
				255);
		}
	}


	free(ucTempBuffer);	

}

// zwalniamy tylko pamiec

FBackground::~FBackground()
{
	free (image);		// surface z obrazem 
}
