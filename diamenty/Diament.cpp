// Diament.cpp: implementation of the Diament class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <FOX.h>
#include "Diament.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Diament::Diament()
{
	unsigned char *buffer;
	int g1,g2;
	
	// 5 klatek animacji

	for (g1=0;g1<5;g1++)
	{
		image_r[g1] = (unsigned char*) malloc(2304);
		image_g[g1] = (unsigned char*) malloc(2304);
		image_b[g1] = (unsigned char*) malloc(2304);
		image_a[g1] = (unsigned char*) malloc(2304);
	}


	// wczytaj po kolei

	buffer = (unsigned char*) malloc(9216);

	FOX_filesys_load(buffer,"diam0.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[0][g1]=buffer[g2];
		image_g[0][g1]=buffer[g2+1];
		image_r[0][g1]=buffer[g2+2];
		image_a[0][g1]=buffer[g2+3];
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216);

	FOX_filesys_load(buffer,"diam1.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[1][g1]=buffer[g2];
		image_g[1][g1]=buffer[g2+1];
		image_r[1][g1]=buffer[g2+2];
		image_a[1][g1]=buffer[g2+3];
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216);

	FOX_filesys_load(buffer,"diam2.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[2][g1]=buffer[g2];
		image_g[2][g1]=buffer[g2+1];
		image_r[2][g1]=buffer[g2+2];
		image_a[2][g1]=buffer[g2+3];
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216);

	FOX_filesys_load(buffer,"diam3.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[3][g1]=buffer[g2];
		image_g[3][g1]=buffer[g2+1];
		image_r[3][g1]=buffer[g2+2];
		image_a[3][g1]=buffer[g2+3];
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216);

	FOX_filesys_load(buffer,"diam4.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[4][g1]=buffer[g2];
		image_g[4][g1]=buffer[g2+1];
		image_r[4][g1]=buffer[g2+2];
		image_a[4][g1]=buffer[g2+3];
	}

	free(buffer);


	x_local=0; y_local=0;
	dst_x_global=0; dst_y_global=0;

}

Diament::~Diament()
{
	int g1;
	
	for (g1=0;g1<5;g1++)
	{
	free(image_r[g1]);
	free(image_g[g1]);
	free(image_b[g1]);
	free(image_a[g1]);
	}
}

Diament::put(int frame,unsigned int x, unsigned int y, FOX_Surface *destination, FOX_Surface *back)
{
	unsigned int A1,A2;

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
	//		FOX_pixelRGBA(back,A2+x,A1+y,0,0,0,255);
			FOX_pixelRGBA(destination,A2+x,A1+y,0,0,0,255);
			FOX_pixelRGBA(back,A2+x,A1+y,
				image_r[frame][(A1*48)+A2],
				image_g[frame][(A1*48)+A2], 
				image_b[frame][(A1*48)+A2],
				image_a[frame][(A1*48)+A2]);

		}
	}
}

