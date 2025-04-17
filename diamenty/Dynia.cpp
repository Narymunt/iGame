// Dynia.cpp: implementation of the Dynia class.
//
//////////////////////////////////////////////////////////////////////

#include "Dynia.h"
#include <fox.h>
#include <windows.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Dynia::Dynia()
{
	int iH1;
	unsigned char *buffer;
	int g1,g2;

	for (iH1=0; iH1<6; iH1++)
	{
		image_r[iH1]= (unsigned char*) malloc(2304);
		image_g[iH1]= (unsigned char*) malloc(2304);
		image_b[iH1]= (unsigned char*) malloc(2304);
		image_a[iH1]= (unsigned char*) malloc(2304);
	}

	// wczytaj 6 klatek

	buffer = (unsigned char*) malloc(9216);  // 1

	FOX_filesys_load(buffer,"dynia0.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[0][g1]=buffer[g2];
		image_g[0][g1]=buffer[g2+1];
		image_r[0][g1]=buffer[g2+2];
		image_a[0][g1]=buffer[g2+3];
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216);  // 2

	FOX_filesys_load(buffer,"dynia1.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[1][g1]=buffer[g2];
		image_g[1][g1]=buffer[g2+1];
		image_r[1][g1]=buffer[g2+2];
		image_a[1][g1]=buffer[g2+3];
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216);  // 3

	FOX_filesys_load(buffer,"dynia2.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[2][g1]=buffer[g2];
		image_g[2][g1]=buffer[g2+1];
		image_r[2][g1]=buffer[g2+2];
		image_a[2][g1]=buffer[g2+3];
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216);  // 4

	FOX_filesys_load(buffer,"dynia3.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[3][g1]=buffer[g2];
		image_g[3][g1]=buffer[g2+1];
		image_r[3][g1]=buffer[g2+2];
		image_a[3][g1]=buffer[g2+3];
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216);  // 5

	FOX_filesys_load(buffer,"dynia4.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[4][g1]=buffer[g2];
		image_g[4][g1]=buffer[g2+1];
		image_r[4][g1]=buffer[g2+2];
		image_a[4][g1]=buffer[g2+3];
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216);  // 6

	FOX_filesys_load(buffer,"dynia5.bin");

	for (g1=0, g2=0; g1<2304; g1++,g2+=4)
	{
		image_b[5][g1]=buffer[g2];
		image_g[5][g1]=buffer[g2+1];
		image_r[5][g1]=buffer[g2+2];
		image_a[5][g1]=buffer[g2+3];
	}

	free(buffer);

	x_local=0; y_local=0;
	dst_x_global=0; dst_y_global=0;


}


Dynia::~Dynia()
{

	for (int i=0; i<6; i++)
	{
		free(image_r[i]);
		free(image_g[i]);
		free(image_b[i]);
		free(image_a[i]);
	}

}

Dynia::put(unsigned int x, unsigned int y, FOX_Surface *destination, FOX_Surface *back)
{
	unsigned int A1,A2;

	char frame=0;
	
	if (x_local>0) frame=x_local%5;
	if (x_local<0) frame=-x_local%5;

	if (y_local>0) frame=y_local%5;
	if (y_local<0) frame=-y_local%5;


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

