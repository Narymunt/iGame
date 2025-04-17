// MurekB.cpp: implementation of the MurekB class.
//
//////////////////////////////////////////////////////////////////////

#include "MurekB.h"
#include <fox.h>
#include <windows.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MurekB::MurekB()
{
	unsigned char *buffer;
	int g1,g2;

	image_r = (unsigned char*) malloc(2304);
	image_g = (unsigned char*) malloc(2304);
	image_b = (unsigned char*) malloc(2304);
	image_a = (unsigned char*) malloc(2304);

	// wczytaj 6 klatek

	buffer = (unsigned char*) malloc(9216);  // 1

	FOX_filesys_load(buffer,"murekb.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[g1]=buffer[g2];
		image_g[g1]=buffer[g2+1];
		image_r[g1]=buffer[g2+2];
		image_a[g1]=buffer[g2+3];
	}

	free(buffer);

}

MurekB::~MurekB()
{

	free(image_b);
	free(image_g);
	free(image_r);
	free(image_a);
}

MurekB::put(unsigned int x, unsigned int y, FOX_Surface *destination)
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