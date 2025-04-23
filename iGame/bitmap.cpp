// implementation of class
// .bmp file is reversed, so at and we flip it
// .tga jest 32bpp, wiec zawsze odczytywana alfa

#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>

//=== class constructor

CBitmap::CBitmap()
{
    m_pBitmapData=NULL;
}

//=== class destructor

CBitmap::~CBitmap()
{
	if (m_pBitmapData!=NULL) free(m_pBitmapData);
}

//=== class constructor - automatic memory allocation
// ten rozmiar musi byc podany w bajtach (x4)

CBitmap::CBitmap(unsigned long size)
{
	m_pBitmapData = (unsigned char*)malloc(1+size);
}

//=== class constructor - automatic load file

CBitmap::CBitmap(unsigned long size, char filename[])
{
    unsigned char *mTemp;
    FILE *bmp_file;
	
    unsigned long b1, b2;

    mTemp = (unsigned char *)malloc(54+(size*3));	// 54 bytes for header, skip

    m_pBitmapData = (unsigned char*)malloc(size*4);	// rgba

    if ((bmp_file=fopen(filename,"rb"))==NULL) printf("Error opening %s file!\n",filename);
    fread(mTemp,54+(size*3),1,bmp_file); // header and data
    fclose(bmp_file);

    for (b1=0, b2=0; b1<size; b1++, b2+=3)	// reverse data
    {
		m_pBitmapData[(b1*4)]=mTemp[51+(size*3)-b2];
		m_pBitmapData[(b1*4)+1]=mTemp[52+(size*3)-b2];
		m_pBitmapData[(b1*4)+2]=mTemp[53+(size*3)-b2];
		m_pBitmapData[(b1*4)+3]=255;	// przy okazji ustawiamy alfa na zawsze widoczna
    }
}

//=== wczytanie, a parametry x i y z argumentow

CBitmap::CBitmap(long lX, long lY, char filename[])
{
    unsigned char *mTemp;
    FILE *bmp_file;
    unsigned long size;	
    unsigned long b1, b2;

    // zapamietaj rozmiary bitmapy

    m_ulSizeX = lX;
    m_ulSizeY = lY;

    size = lX *lY;
    printf("[CBitmap]: %s x: %d y: %d size: %d\n",filename,m_ulSizeX,m_ulSizeY,size);
    
    mTemp = (unsigned char *)malloc(54+(size*3));	// 54 bytes for header, 24bpp, skip

    m_pBitmapData = (unsigned char*)malloc(size*4);

    if ((bmp_file=fopen(filename,"rb"))==NULL) printf("Error opening %s file!\n",filename);
    fread(mTemp,54+(size*3),1,bmp_file); // header and data
    fclose(bmp_file);

    for (b1=0, b2=0; b1<size; b1++, b2+=3)	// reverse data
    {
		m_pBitmapData[(b1*4)]=mTemp[51+(size*3)-b2];
		m_pBitmapData[(b1*4)+1]=mTemp[52+(size*3)-b2];
		m_pBitmapData[(b1*4)+2]=mTemp[53+(size*3)-b2];
		m_pBitmapData[(b1*4)+3]=255;	// przy okazji ustawiamy alfa na zawsze widoczna
    }
}

//=== bitmapa wg typu

CBitmap::CBitmap(char filename[], char cType)
{
    FILE *plik;
    
    unsigned char cHeader[18];
    unsigned char *pTemp;
    
    // struktura pliku TGA
    
    unsigned char	ucIdentSize;	// zwykle 0
    unsigned char	ucPalette;	// 0 brak, 1 paleta
    unsigned char	ucType;		// 0 brak, 1 index, 2 rgb, 3 szary, +8 spakowane rle
    unsigned short	usPalStart;	// poczatek palety
    unsigned short	usPalLength;	// dlugosc palety
    unsigned char	ucPalBpp;	// 15,16,24,32
    
    unsigned short	usXStart;	// poczatek X
    unsigned short	usYStart;	// poczatek Y
    unsigned short	usXSize;		// rozmiar X
    unsigned short	usYSize;		// rozmiar Y
    unsigned char	ucBpp;		// 8,16,24,32
    unsigned char	ucDesc;		// czy obrocony

    unsigned long	size;

    if (cType==TGA)
    {
    
        if ((plik=fopen(filename,"rb"))==NULL) printf("#\nCBitmap: Nie mozna odczytac %s \n",filename);
        fread(&cHeader,18,1,plik);
    
        printf("#\nCBitmap: nowy obraz TGA %s\n",filename);
    
        ucIdentSize = cHeader[0];
        ucPalette = cHeader[1];
        ucType = cHeader[2];
        usPalStart = (cHeader[4]<<8)+cHeader[3];
        usPalLength = (cHeader[6]<<8)+cHeader[5];
        ucPalBpp = cHeader[7];
        usXStart = (cHeader[9]<<8)+cHeader[8];
        usYStart = (cHeader[11]<<8)+cHeader[10];
        usXSize = (cHeader[13]<<8)+cHeader[12];
        usYSize = (cHeader[15]<<8)+cHeader[14];
        ucBpp = cHeader[16];
        ucDesc = cHeader[17];    
    
        printf("TGA: identyfikator %d\n",ucIdentSize);
        printf("TGA: paleta %d\n",ucPalette);
        printf("TGA: typ %d\n",ucType);
        printf("TGA: poczatek palety %d\n",usPalStart);
        printf("TGA: dlugosc palety %d\n",usPalLength);
        printf("TGA: rodzaj palety %d bpp\n",ucPalBpp);
        printf("TGA: poczatek X %d\n",usXStart);
        printf("TGA: poczatek Y %d\n",usYStart);
        printf("TGA: rozmiar X %d\n",usXSize);
        printf("TGA: rozmiar Y %d\n",usYSize);
        printf("TGA: %d bpp\n",ucBpp);
        printf("TGA: opis %d\n",ucDesc);

	// zapamietaj rozmiary
    
        m_ulSizeX = usXSize;
        m_ulSizeY = usYSize;
    
        // zakladamy, ze tga zawsze bedzie 32bpp
    
        size = (m_ulSizeX * m_ulSizeY);
        pTemp = new unsigned char[1+(size*4)];

        m_pBitmapData = (unsigned char*)malloc(size*4);
    
        if (ucBpp==32) fread(pTemp,size*4,1,plik);
        if (ucBpp==24) fread(pTemp,size*3,1,plik);
        
        printf("TGA: wczytano dane\n");
        fclose(plik);

		if (ucBpp==32) // pobieramy alfe
		{
				for (long i=0; i<size; i++)
				{
					m_pBitmapData[(i*4)] = pTemp[(size-i)*4];
					m_pBitmapData[(i*4)+1] = pTemp[((size-i)*4)+1];
					m_pBitmapData[(i*4)+2] = pTemp[((size-i)*4)+2];
					m_pBitmapData[(i*4)+3] = pTemp[((size-i)*4)+3];
				}	    
		}
	
		if (ucBpp==24) // nie ma alfy w pliku
		{
				for (long i=0; i<size; i++)
				{
					m_pBitmapData[(i*4)] = pTemp[(size-i)*3];
					m_pBitmapData[(i*4)+1] = pTemp[((size-i)*3)+1];
					m_pBitmapData[(i*4)+2] = pTemp[((size-i)*3)+2];
					m_pBitmapData[(i*4)+3] = 255;
				}	    
		}

    } // cType==TGA
    
}

//=== akcesory dla danych bitmapy

unsigned char CBitmap::ucGetDataR(int iIndex)
{
    return m_pBitmapData[(iIndex*4)+2];	// bgra
}

unsigned char CBitmap::ucGetDataG(int iIndex)
{
    return m_pBitmapData[(iIndex*4)+1]; // bgra
}

unsigned char CBitmap::ucGetDataB(int iIndex)
{
    return m_pBitmapData[(iIndex*4)]; // bgra
}

unsigned char CBitmap::ucGetDataA(int iIndex)
{
    return m_pBitmapData[(iIndex*4)+3]; // bgra
}

// renderowanie po przeskalowaniu

int CBitmap::Render(int iX, int iY, int iXSize, int iYSize, double iXScale, double iYScale, unsigned char *pBuffer)
{

	return 0;
}

// renderowanie, dziala clipping  

int CBitmap::Render(int iX, int iY, unsigned char *pBuffer)
{
	long lAdres;
	
	for (int h1=0; h1<m_ulSizeY; h1++)
	{
		for (int h2=0;h2<m_ulSizeX; h2++)
		{
			if ( ((iX+h2)<1024) && ((iX+h2)>0) &&
			     ((iY+h1)<768) && ((iY+h1)>0) && (m_pBitmapData[(((m_ulSizeX*h1)+h2)*4)+3]>127))
			{
				lAdres=((1024*(iY+h1))+iX+h2)*4;
				pBuffer[lAdres] = m_pBitmapData[(((m_ulSizeX*h1)+h2)*4)+2]; // r
				pBuffer[lAdres+1] = m_pBitmapData[(((m_ulSizeX*h1)+h2)*4)+1]; // g
				pBuffer[lAdres+2] = m_pBitmapData[((m_ulSizeX*h1)+h2)*4]; // b
			}
		}
	}
	return 0;
}

// dla rozdzielczosci 1280x1024

int CBitmap::Render1280(int iX, int iY, unsigned char *pBuffer)
{
	long lAdres;
	
	for (int h1=0; h1<m_ulSizeY; h1++)
	{
		for (int h2=0;h2<m_ulSizeX; h2++)
		{
			if ( ((iX+h2)<1280) && ((iX+h2)>0) &&
			     ((iY+h1)<1024) && ((iY+h1)>0) && (m_pBitmapData[(((m_ulSizeX*h1)+h2)*4)+3]>127))
			{
			lAdres=((1280*(iY+h1))+iX+h2)*4;
			pBuffer[lAdres] = m_pBitmapData[(((m_ulSizeX*h1)+h2)*4)+2]; // r
			pBuffer[lAdres+1] = m_pBitmapData[(((m_ulSizeX*h1)+h2)*4)+1]; // g
			pBuffer[lAdres+2] = m_pBitmapData[(((m_ulSizeX*h1)+h2)*4)]; // b
			}
		}
	}
	return 0;
}


// renderowanie, dodaje kolory do siebie

int CBitmap::RenderPlus(int iX, int iY, unsigned char *pBuffer)
{
	long lAdres;
	unsigned int iKolor;
	unsigned char cKolor;
	
	for (int h1=0; h1<m_ulSizeY; h1++)
	{
		for (int h2=0;h2<m_ulSizeX; h2++)
		{
			if ( ((iX+h2)<1024) && ((iX+h2)>0) &&
			     ((iY+h1)<768) && ((iY+h1)>0) )
			{
			lAdres=((1024*(iY+h1))+iX+h2)*4;

			cKolor = pBuffer[lAdres]; 
			iKolor = cKolor + m_pBitmapData[(((m_ulSizeX*h1)+h2)*4)+2]; // r
			if (iKolor>255) iKolor = 255;
			pBuffer[lAdres] = (unsigned char)iKolor;

			cKolor = pBuffer[lAdres+1]; 
			iKolor = cKolor + m_pBitmapData[(((m_ulSizeX*h1)+h2)*4)+1]; // g
			if (iKolor>255) iKolor = 255;
			pBuffer[lAdres+1] = (unsigned char)iKolor;

			cKolor = pBuffer[lAdres+2]; 
			iKolor = cKolor + m_pBitmapData[((m_ulSizeX*h1)+h2)*4]; // b
			if (iKolor>255) iKolor = 255;
			pBuffer[lAdres+2] = (unsigned char)iKolor;
			}
		}
	}
	return 0;
}

//=== podawanie i odbieranie rozmiarow

void CBitmap::SetSizeX(unsigned long ulX)
{
    m_ulSizeX = ulX;
}

unsigned long CBitmap::ulGetSizeX(void)
{
    return m_ulSizeX;
}

void CBitmap::SetSizeY(unsigned long ulY)
{
    m_ulSizeY = ulY;
}

unsigned long CBitmap::ulGetSizeY(void)
{
    return m_ulSizeY;
}

//=== renderowanie przeskalowane

int CBitmap::RenderScale(int iX, int iY, int iXSize, int iYSize, double dXScale, double dYScale, unsigned char *pBuffer)
{
    long flare_addr,lAdresBufora;
    double dAddX, dAddY;	// o ile dodajemy na pixel
    double dCurrentX, dCurrentY; // aktualne wspolrzedne
    
    dAddX = iXSize/dXScale;
    dAddY = iYSize/dYScale;
    
    dCurrentY = 0;	// zerujemy
    
    for (int a1=0; a1<dYScale; a1++)
    {
	dCurrentX = 0; 
	
	for (int a2=0; a2<dXScale; a2++)
	{
	    if ( (iX+a2>0) &&(iX+a2<1024) && (iY+a1>0) && (iY+a1<768) )
	    {
		lAdresBufora = ((1024*(iY+a1))+iX+a2)*4;
		flare_addr = (long)((((long)dCurrentY)*iXSize)+dCurrentX);

		pBuffer[lAdresBufora] = m_pBitmapData[(flare_addr<<2)+2]; // r
		pBuffer[lAdresBufora+1] = m_pBitmapData[(flare_addr<<2)+1]; // g
		pBuffer[lAdresBufora+2] = m_pBitmapData[(flare_addr<<2)]; // b
	    }
	
	    dCurrentX = dCurrentX + dAddX;
	}
	
	dCurrentY = dCurrentY + dAddY;
    }

    return 0;
}

//=== renderowanie przeskalowane z dodawaniem

int CBitmap::RenderScalePlus(int iX, int iY, int iXSize, int iYSize, double dXScale, double dYScale, unsigned char *pBuffer)
{
    long flare_addr,lAdresBufora;
    double dAddX, dAddY;	// o ile dodajemy na pixel
    double dCurrentX, dCurrentY; // aktualne wspolrzedne
    
    unsigned int iKolor;
    unsigned char cKolor;
    
    dAddX = iXSize/dXScale;
    dAddY = iYSize/dYScale;
    
    dCurrentY = 0;	// zerujemy
    
    for (int a1=0; a1<dYScale; a1++)
    {
	dCurrentX = 0; 
	
	for (int a2=0; a2<dXScale; a2++)
	{
	    if ( (iX+a2>0) &&(iX+a2<1024) && (iY+a1>0) && (iY+a1<768) )
	    {
		lAdresBufora = ((1024*(iY+a1))+iX+a2)*4;
		flare_addr = (long)((((long)dCurrentY)*iXSize)+dCurrentX);

		iKolor = m_pBitmapData[(flare_addr<<2)+2] + pBuffer[lAdresBufora]; // r
		if (iKolor>255) iKolor = 255;
		pBuffer[lAdresBufora] = (unsigned char)iKolor;

		iKolor = m_pBitmapData[(flare_addr<<2)+1] + pBuffer[lAdresBufora+1]; // g
		if (iKolor>255) iKolor = 255;
		pBuffer[lAdresBufora+1] = (unsigned char)iKolor;

		iKolor = m_pBitmapData[flare_addr<<2] + pBuffer[lAdresBufora+2]; // b
		if (iKolor>255) iKolor = 255;
		pBuffer[lAdresBufora+2] = (unsigned char)iKolor;

	    }
	
	    dCurrentX = dCurrentX + dAddX;
	}
	
	dCurrentY = dCurrentY + dAddY;
    }

    return 0;
}
