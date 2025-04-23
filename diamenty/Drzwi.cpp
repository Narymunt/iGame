// Drzwi.cpp: implementation of the Drzwi class.
//
//////////////////////////////////////////////////////////////////////

#include "Drzwi.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Drzwi::Drzwi()
{
	unsigned char *buffer;
	int g1,g2;
	
	// 3 klatek animacji

	for (g1=0;g1<3;g1++)
	{
		image_r[g1] = (unsigned char*) malloc(2304);
		image_g[g1] = (unsigned char*) malloc(2304);
		image_b[g1] = (unsigned char*) malloc(2304);
		image_a[g1] = (unsigned char*) malloc(2304);
	}


	// wczytaj po kolei

	buffer = (unsigned char*) malloc(9216);

	FOX_filesys_load(buffer,"drzwi0.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[0][g1]=buffer[g2];
		image_g[0][g1]=buffer[g2+1];
		image_r[0][g1]=buffer[g2+2];
		image_a[0][g1]=buffer[g2+3];
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216);

	FOX_filesys_load(buffer,"drzwi1.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[1][g1]=buffer[g2];
		image_g[1][g1]=buffer[g2+1];
		image_r[1][g1]=buffer[g2+2];
		image_a[1][g1]=buffer[g2+3];
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216);

	FOX_filesys_load(buffer,"drzwi2.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[2][g1]=buffer[g2];
		image_g[2][g1]=buffer[g2+1];
		image_r[2][g1]=buffer[g2+2];
		image_a[2][g1]=buffer[g2+3];
	}

	free(buffer);

	x_global=14;
	y_global=8;

}

Drzwi::~Drzwi()
{
	int g1;
	
	for (g1=0;g1<3;g1++)
	{
	free(image_r[g1]);
	free(image_g[g1]);
	free(image_b[g1]);
	free(image_a[g1]);
	}

}

Drzwi::put(int frame,unsigned int x, unsigned int y, FOX_Surface *destination)
{
	unsigned int A1,A2;

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
	//		FOX_pixelRGBA(back,A2+x,A1+y,0,0,0,255);
			FOX_pixelRGBA(destination,A2+x,A1+y,0,0,0,255);
			FOX_pixelRGBA(destination
				,A2+x,A1+y,
				image_r[frame][(A1*48)+A2],
				image_g[frame][(A1*48)+A2], 
				image_b[frame][(A1*48)+A2],
				image_a[frame][(A1*48)+A2]);

		}
	}
}
