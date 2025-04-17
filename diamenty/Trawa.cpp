// Trawa.cpp: implementation of the Trawa class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <FOX.h>
#include "Trawa.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Trawa::Trawa()
{
	image_r = (unsigned char*) malloc(2304);
	image_g = (unsigned char*) malloc(2304);
	image_b = (unsigned char*) malloc(2304);
	image_a = (unsigned char*) malloc(2304);

	FOX_filesys_load(image_r,"trawa.r");
	FOX_filesys_load(image_g,"trawa.g");
	FOX_filesys_load(image_b,"trawa.b");
	FOX_filesys_load(image_a,"trawa.a");

}

Trawa::~Trawa()
{
	free(image_r);
	free(image_g);
	free(image_b);
	free(image_a);

}

// narysuj trawe

Trawa::put_Trawa(unsigned int x, unsigned int y, FOX_Surface *destination)
{
	unsigned int A1,A2;

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			FOX_pixelRGBA(destination,A2+x,A1+y,
				image_r[((A1*48)+A2)],
				image_g[((A1*48)+A2)], 
				image_b[((A1*48)+A2)],
				image_a[((A1*48)+A2)]);
		}
	}
}