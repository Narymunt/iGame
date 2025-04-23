// implementation of class
// .bmp file is reversed, so at and we flip it

#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>

//=== class constructor

CBitmap::CBitmap()
{
    m_pBitmapDataR=NULL;
    m_pBitmapDataG=NULL;
    m_pBitmapDataB=NULL;
	m_pBitmapDataA = NULL;
}

//=== class destructor

CBitmap::~CBitmap()
{
	if (m_pBitmapDataR!=NULL) free(m_pBitmapDataR);
	if (m_pBitmapDataG!=NULL) free(m_pBitmapDataG);
	if (m_pBitmapDataB!=NULL) free(m_pBitmapDataB);
	if (m_pBitmapDataA!=NULL) free(m_pBitmapDataA);
}

//=== class constructor - automatic memory allocation

CBitmap::CBitmap(unsigned long size)
{
	m_pBitmapDataR = (unsigned char*)malloc(size);
	m_pBitmapDataG = (unsigned char*)malloc(size);
	m_pBitmapDataB = (unsigned char*)malloc(size);
	m_pBitmapDataA = (unsigned char*)malloc(size);
}

//=== class constructor - automatic load file

CBitmap::CBitmap(unsigned long size, char filename[])
{
    unsigned char *mTemp;
    FILE *bmp_file;
	
    unsigned long b1, b2;

    mTemp = (unsigned char *)malloc(54+(size*3));	// 54 bytes for header, skip

    m_pBitmapDataR = (unsigned char*)malloc(size);
    m_pBitmapDataG = (unsigned char*)malloc(size);
    m_pBitmapDataB = (unsigned char*)malloc(size);
	m_pBitmapDataA = (unsigned char*)malloc(size);

    if ((bmp_file=fopen(filename,"rb"))==NULL) printf("Error opening %s file!\n",filename);
    fread(mTemp,54+(size*3),1,bmp_file); // header and data
    fclose(bmp_file);

    for (b1=0, b2=0; b1<size; b1++, b2+=3)	// reverse data
    {
	m_pBitmapDataB[b1]=mTemp[51+(size*3)-b2];
	m_pBitmapDataG[b1]=mTemp[52+(size*3)-b2];
	m_pBitmapDataR[b1]=mTemp[53+(size*3)-b2];
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

    mTemp = (unsigned char *)malloc(54+(size*3));	// 54 bytes for header, skip

    m_pBitmapDataR = (unsigned char*)malloc(size);
    m_pBitmapDataG = (unsigned char*)malloc(size);
    m_pBitmapDataB = (unsigned char*)malloc(size);
	m_pBitmapDataA = (unsigned char*)malloc(size);

    if ((bmp_file=fopen(filename,"rb"))==NULL) printf("Error opening %s file!\n",filename);
    fread(mTemp,54+(size*3),1,bmp_file); // header and data
    fclose(bmp_file);

    for (b1=0, b2=0; b1<size; b1++, b2+=3)	// reverse data
    {
	m_pBitmapDataB[b1]=mTemp[51+(size*3)-b2];
	m_pBitmapDataG[b1]=mTemp[52+(size*3)-b2];
	m_pBitmapDataR[b1]=mTemp[53+(size*3)-b2];
    }
}


//=== akcesory dla danych bitmapy

unsigned char CBitmap::ucGetDataR(int iIndex)
{
    return m_pBitmapDataR[iIndex];
}

unsigned char CBitmap::ucGetDataG(int iIndex)
{
    return m_pBitmapDataG[iIndex];
}

unsigned char CBitmap::ucGetDataB(int iIndex)
{
    return m_pBitmapDataB[iIndex];
}

unsigned char CBitmap::ucGetDataA(int iIndex)
{
    return m_pBitmapDataA[iIndex];
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
			if ( ((iX+h2)<800) && ((iX+h2)>0) &&
			     ((iY+h1)<600) && ((iY+h1)>0) )
			{
			lAdres=((800*(iY+h1))+iX+h2)*4;
			pBuffer[lAdres] = m_pBitmapDataR[(m_ulSizeX*h1)+h2];
			pBuffer[lAdres+1] = m_pBitmapDataG[(m_ulSizeX*h1)+h2];
			pBuffer[lAdres+2] = m_pBitmapDataB[(m_ulSizeX*h1)+h2];
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
			if ( ((iX+h2)<800) && ((iX+h2)>0) &&
			     ((iY+h1)<600) && ((iY+h1)>0) )
			{
			lAdres=((800*(iY+h1))+iX+h2)*4;

			cKolor = pBuffer[lAdres]; 
			iKolor = cKolor + m_pBitmapDataR[(m_ulSizeX*h1)+h2];
			if (iKolor>255) iKolor = 255;
			pBuffer[lAdres] = (unsigned char)iKolor;

			cKolor = pBuffer[lAdres+1]; 
			iKolor = cKolor + m_pBitmapDataG[(m_ulSizeX*h1)+h2];
			if (iKolor>255) iKolor = 255;
			pBuffer[lAdres+1] = (unsigned char)iKolor;

			cKolor = pBuffer[lAdres+2]; 
			iKolor = cKolor + m_pBitmapDataB[(m_ulSizeX*h1)+h2];
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
	    if ( (iX+a2>0) &&(iX+a2<800) && (iY+a1>0) && (iY+a1<600) )
	    {
		lAdresBufora = ((800*(iY+a1))+iX+a2)*4;
		flare_addr = (long)((((long)dCurrentY)*iXSize)+dCurrentX);

		pBuffer[lAdresBufora] = m_pBitmapDataR[flare_addr];
		pBuffer[lAdresBufora+1] = m_pBitmapDataG[flare_addr];
		pBuffer[lAdresBufora+2] = m_pBitmapDataB[flare_addr];
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
	    if ( (iX+a2>0) &&(iX+a2<800) && (iY+a1>0) && (iY+a1<600) )
	    {
		lAdresBufora = ((800*(iY+a1))+iX+a2)*4;
		flare_addr = (long)((((long)dCurrentY)*iXSize)+dCurrentX);

		iKolor = m_pBitmapDataR[flare_addr] + pBuffer[lAdresBufora];
		if (iKolor>255) iKolor = 255;
		pBuffer[lAdresBufora] = (unsigned char)iKolor;

		iKolor = m_pBitmapDataG[flare_addr] + pBuffer[lAdresBufora+1];
		if (iKolor>255) iKolor = 255;
		pBuffer[lAdresBufora+1] = (unsigned char)iKolor;

		iKolor = m_pBitmapDataB[flare_addr] + pBuffer[lAdresBufora+2];
		if (iKolor>255) iKolor = 255;
		pBuffer[lAdresBufora+2] = (unsigned char)iKolor;

	    }
	
	    dCurrentX = dCurrentX + dAddX;
	}
	
	dCurrentY = dCurrentY + dAddY;
    }

    return 0;
}
