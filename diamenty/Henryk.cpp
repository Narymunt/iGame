// Henryk.cpp: implementation of the Henryk class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <FOX.h>
#include "Henryk.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Henryk::Henryk()
{
	
	int A1,A2;

	unsigned char *buffer;

	// wczytaj jak stoi

	buffer = (unsigned char*) malloc(9216);

	stoi_r = (unsigned char*) malloc(2304);
	stoi_g = (unsigned char*) malloc(2304);
	stoi_b = (unsigned char*) malloc(2304);
	stoi_a = (unsigned char*) malloc(2304);

	FOX_filesys_load(buffer,"stoi.bin");

	for (A1=0,A2=0;A1<2304;A1++,A2+=4)
	{
		stoi_r[A1]=buffer[A2];
		stoi_g[A1]=buffer[A2+1];
		stoi_b[A1]=buffer[A2+2];
		stoi_a[A1]=buffer[A2+3];
	}

	free(buffer);

	// wczytaj 4 klatki idzie do gory i w dol

	for (A1=0;A1<4; A1++)	// zaalokuj na wszystkie klatki
	{
	gora_r[A1] = (unsigned char*) malloc(2304);
	gora_g[A1] = (unsigned char*) malloc(2304);
	gora_b[A1] = (unsigned char*) malloc(2304);
	gora_a[A1] = (unsigned char*) malloc(2304);

	dol_r[A1] = (unsigned char*) malloc(2304);
	dol_g[A1] = (unsigned char*) malloc(2304);
	dol_b[A1] = (unsigned char*) malloc(2304);
	dol_a[A1] = (unsigned char*) malloc(2304);
	}

	buffer = (unsigned char*) malloc(9216);	// 1 

	FOX_filesys_load(buffer,"gora1.bin");
	
	for (A1=0,A2=0;A1<2304;A1++,A2+=4)
	{
		gora_r[0][A1]=buffer[A2];
		gora_g[0][A1]=buffer[A2+1];
		gora_b[0][A1]=buffer[A2+2];
		gora_a[0][A1]=buffer[A2+3];
	}

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			dol_r[0][48*(47-A1)+A2]=gora_r[0][48*A1+A2];		
			dol_g[0][48*(47-A1)+A2]=gora_g[0][48*A1+A2];	
			dol_b[0][48*(47-A1)+A2]=gora_b[0][48*A1+A2];	
			dol_a[0][48*(47-A1)+A2]=gora_a[0][48*A1+A2];	
		}
	}

	free(buffer);
	
	buffer = (unsigned char*) malloc(9216); // 2

	FOX_filesys_load(buffer,"gora2.bin");
	
	for (A1=0,A2=0;A1<2304;A1++,A2+=4)
	{
		gora_r[1][A1]=buffer[A2];
		gora_g[1][A1]=buffer[A2+1];
		gora_b[1][A1]=buffer[A2+2];
		gora_a[1][A1]=buffer[A2+3];
	}

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			dol_r[1][48*(47-A1)+A2]=gora_r[1][48*A1+A2];		
			dol_g[1][48*(47-A1)+A2]=gora_g[1][48*A1+A2];	
			dol_b[1][48*(47-A1)+A2]=gora_b[1][48*A1+A2];	
			dol_a[1][48*(47-A1)+A2]=gora_a[1][48*A1+A2];	
		}
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216); // 3

	FOX_filesys_load(buffer,"gora3.bin");
	
	for (A1=0,A2=0;A1<2304;A1++,A2+=4)
	{
		gora_r[2][A1]=buffer[A2];
		gora_g[2][A1]=buffer[A2+1];
		gora_b[2][A1]=buffer[A2+2];
		gora_a[2][A1]=buffer[A2+3];
	}

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			dol_r[2][48*(47-A1)+A2]=gora_r[2][48*A1+A2];		
			dol_g[2][48*(47-A1)+A2]=gora_g[2][48*A1+A2];	
			dol_b[2][48*(47-A1)+A2]=gora_b[2][48*A1+A2];	
			dol_a[2][48*(47-A1)+A2]=gora_a[2][48*A1+A2];	
		}
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216); // 4

	FOX_filesys_load(buffer,"gora4.bin");
	
	for (A1=0,A2=0;A1<2304;A1++,A2+=4)
	{
		gora_r[3][A1]=buffer[A2];
		gora_g[3][A1]=buffer[A2+1];
		gora_b[3][A1]=buffer[A2+2];
		gora_a[3][A1]=buffer[A2+3];
	}

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			dol_r[3][48*(47-A1)+A2]=gora_r[3][48*A1+A2];		
			dol_g[3][48*(47-A1)+A2]=gora_g[3][48*A1+A2];	
			dol_b[3][48*(47-A1)+A2]=gora_b[3][48*A1+A2];	
			dol_a[3][48*(47-A1)+A2]=gora_a[3][48*A1+A2];	
		}
	}

	free(buffer);


	// wczytaj 6 klatek idzie w lewo i w prawo

	for (A1=0;A1<6;A1++)
	{

	prawo_r[A1] = (unsigned char*) malloc(2304);
	prawo_g[A1] = (unsigned char*) malloc(2304);
	prawo_b[A1] = (unsigned char*) malloc(2304);
	prawo_a[A1] = (unsigned char*) malloc(2304);

	lewo_r[A1] = (unsigned char*) malloc(2304);
	lewo_g[A1] = (unsigned char*) malloc(2304);
	lewo_b[A1] = (unsigned char*) malloc(2304);
	lewo_a[A1] = (unsigned char*) malloc(2304);
	}

	buffer = (unsigned char*) malloc(9216); // 1 

	FOX_filesys_load(buffer,"prawo1.bin");

	for (A1=0,A2=0;A1<2304;A1++,A2+=4)
	{
		prawo_r[0][A1]=buffer[A2];
		prawo_g[0][A1]=buffer[A2+1];
		prawo_b[0][A1]=buffer[A2+2];
		prawo_a[0][A1]=buffer[A2+3];
	}

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			lewo_r[0][48*A1+47-A2]=prawo_r[0][48*A1+A2];	// b
			lewo_g[0][48*A1+47-A2]=prawo_g[0][48*A1+A2];	// g
			lewo_b[0][48*A1+47-A2]=prawo_b[0][48*A1+A2];	// r
			lewo_a[0][48*A1+47-A2]=prawo_a[0][48*A1+A2];	// a			
		}
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216); // 2

	FOX_filesys_load(buffer,"prawo2.bin");

	for (A1=0,A2=0;A1<2304;A1++,A2+=4)
	{
		prawo_r[1][A1]=buffer[A2];
		prawo_g[1][A1]=buffer[A2+1];
		prawo_b[1][A1]=buffer[A2+2];
		prawo_a[1][A1]=buffer[A2+3];
	}

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			lewo_r[1][48*A1+47-A2]=prawo_r[1][48*A1+A2];	// b
			lewo_g[1][48*A1+47-A2]=prawo_g[1][48*A1+A2];	// g
			lewo_b[1][48*A1+47-A2]=prawo_b[1][48*A1+A2];	// r
			lewo_a[1][48*A1+47-A2]=prawo_a[1][48*A1+A2];	// a			
		}
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216); // 3

	FOX_filesys_load(buffer,"prawo3.bin");

	for (A1=0,A2=0;A1<2304;A1++,A2+=4)
	{
		prawo_r[2][A1]=buffer[A2];
		prawo_g[2][A1]=buffer[A2+1];
		prawo_b[2][A1]=buffer[A2+2];
		prawo_a[2][A1]=buffer[A2+3];
	}

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			lewo_r[2][48*A1+47-A2]=prawo_r[2][48*A1+A2];	// b
			lewo_g[2][48*A1+47-A2]=prawo_g[2][48*A1+A2];	// g
			lewo_b[2][48*A1+47-A2]=prawo_b[2][48*A1+A2];	// r
			lewo_a[2][48*A1+47-A2]=prawo_a[2][48*A1+A2];	// a			
		}
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216); // 4

	FOX_filesys_load(buffer,"prawo4.bin");

	for (A1=0,A2=0;A1<2304;A1++,A2+=4)
	{
		prawo_r[3][A1]=buffer[A2];
		prawo_g[3][A1]=buffer[A2+1];
		prawo_b[3][A1]=buffer[A2+2];
		prawo_a[3][A1]=buffer[A2+3];
	}

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			lewo_r[3][48*A1+47-A2]=prawo_r[3][48*A1+A2];	// b
			lewo_g[3][48*A1+47-A2]=prawo_g[3][48*A1+A2];	// g
			lewo_b[3][48*A1+47-A2]=prawo_b[3][48*A1+A2];	// r
			lewo_a[3][48*A1+47-A2]=prawo_a[3][48*A1+A2];	// a			
		}
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216); // 5

	FOX_filesys_load(buffer,"prawo5.bin");

	for (A1=0,A2=0;A1<2304;A1++,A2+=4)
	{
		prawo_r[4][A1]=buffer[A2];
		prawo_g[4][A1]=buffer[A2+1];
		prawo_b[4][A1]=buffer[A2+2];
		prawo_a[4][A1]=buffer[A2+3];
	}

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			lewo_r[4][48*A1+47-A2]=prawo_r[4][48*A1+A2];	// b
			lewo_g[4][48*A1+47-A2]=prawo_g[4][48*A1+A2];	// g
			lewo_b[4][48*A1+47-A2]=prawo_b[4][48*A1+A2];	// r
			lewo_a[4][48*A1+47-A2]=prawo_a[4][48*A1+A2];	// a			
		}
	}

	free(buffer);

	buffer = (unsigned char*) malloc(9216); // 6

	FOX_filesys_load(buffer,"prawo6.bin");

	for (A1=0,A2=0;A1<2304;A1++,A2+=4)
	{
		prawo_r[5][A1]=buffer[A2];
		prawo_g[5][A1]=buffer[A2+1];
		prawo_b[5][A1]=buffer[A2+2];
		prawo_a[5][A1]=buffer[A2+3];
	}

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			lewo_r[5][48*A1+47-A2]=prawo_r[5][48*A1+A2];	// b
			lewo_g[5][48*A1+47-A2]=prawo_g[5][48*A1+A2];	// g
			lewo_b[5][48*A1+47-A2]=prawo_b[5][48*A1+A2];	// r
			lewo_a[5][48*A1+47-A2]=prawo_a[5][48*A1+A2];	// a			
		}
	}

	free(buffer);

	// bufor do rysowania

	buffer_r = (unsigned char*) malloc(2304);
	buffer_g = (unsigned char*) malloc(2304);
	buffer_b = (unsigned char*) malloc(2304);
	buffer_a = (unsigned char*) malloc(2304);

	// ustaw na planszy

	x_global=0; y_global=0;
	x_local=0; y_local=0;
	
	dst_x_global=0; dst_y_global=0;

	ile_stoi=50;
}

Henryk::~Henryk()
{
	int A1;

	for (A1=0; A1<4; A1++) 
	{
		free(gora_r[A1]); free(gora_g[A1]); free(gora_b[A1]); free(gora_a[A1]);
		free(dol_r[A1]); free(dol_g[A1]); free(dol_b[A1]); free(dol_a[A1]);
	}

	free(stoi_r); free(stoi_g); free(stoi_b); free(stoi_a);


	free(buffer_r);
	free(buffer_g);
	free(buffer_b);
	free(buffer_a);

}

// dodaj, ze jezeli alfa=0 to pixela nie rysujemy
// najpierw if a potem for

Henryk::put_Henryk(unsigned int x, unsigned int y, FOX_Surface *destination, FOX_Surface *back)
{

	unsigned int A1,A2;

	// idzie w dol
		
	if (y_local>0)
	{
		memcpy(buffer_b,dol_b[y_local%3],2304);
		memcpy(buffer_g,dol_g[y_local%3],2304);		
		memcpy(buffer_r,dol_r[y_local%3],2304);
		memcpy(buffer_a,dol_a[y_local%3],2304);
		ile_stoi=0;
	}

	// idzie w gore

	if (y_local<0)
	{
		memcpy(buffer_b,gora_b[-y_local%3],2304);
		memcpy(buffer_g,gora_g[-y_local%3],2304);		
		memcpy(buffer_r,gora_r[-y_local%3],2304);
		memcpy(buffer_a,gora_a[-y_local%3],2304);
		ile_stoi=0;
	}

	// idzie w prawo

	if (x_local>0)
	{
		memcpy(buffer_b,prawo_b[x_local%5],2304);
		memcpy(buffer_g,prawo_g[x_local%5],2304);		
		memcpy(buffer_r,prawo_r[x_local%5],2304);
		memcpy(buffer_a,prawo_a[x_local%5],2304);
		ile_stoi=0;
	}


	// idzie w lewo

	if (x_local<0)
	{
		memcpy(buffer_b,lewo_b[-x_local%5],2304);
		memcpy(buffer_g,lewo_g[-x_local%5],2304);		
		memcpy(buffer_r,lewo_r[-x_local%5],2304);
		memcpy(buffer_a,lewo_a[-x_local%5],2304);
		ile_stoi=0;
	}		

	// stoi

	if (x_local==0&&y_local==0) // stoi
	{
		ile_stoi++;

		if (ile_stoi>25)
		{
		  memcpy(buffer_b,stoi_b,2304);
		  memcpy(buffer_g,stoi_g,2304);
		  memcpy(buffer_r,stoi_r,2304);
		  memcpy(buffer_a,stoi_a,2304);
		}

	}

	// narysuj

	for (A1=0; A1<48; A1++)
	{
		for (A2=0; A2<48; A2++)
		{
			FOX_pixelRGBA(destination,A2+x,A1+y,0,0,0,255);
			FOX_pixelRGBA(back,A2+x,A1+y,0,0,0,255);
			FOX_pixelRGBA(destination,A2+x,A1+y,
				buffer_b[(A1*48)+A2],
				buffer_g[(A1*48)+A2], 
				buffer_r[(A1*48)+A2],
				buffer_a[(A1*48)+A2]);
		}
	}
		
			

}