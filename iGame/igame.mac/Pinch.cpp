#include <stdio.h>
#include "Pinch.h"

//=== konstruktor 

CPinch::CPinch(unsigned int uiXSize, unsigned int uiYSize, char cXTable[], char cYTable[], char cTexture[])
{

    m_uiXSize = uiXSize; 	// zapamietaj na potem
    m_uiYSize = uiYSize;

    FILE *plik;
    
    plik = NULL;
    if ((plik = fopen(cXTable,"rb"))==NULL) printf("PINCH: nie znaleziono XTable\n");

    m_pXTable = NULL;	// wyzeruj przed alokacja
    m_pXTable = new unsigned char[1+(uiXSize*uiYSize)];
    
    fread(m_pXTable,1,uiXSize*uiYSize,plik);	// wczytaj tablice
    fclose(plik);
    
    plik = NULL;
    if ((plik = fopen(cYTable,"rb"))==NULL) printf("PINCH: nie znaleziono YTable\n");

    m_pYTable = NULL;	// wyzeruj przed alokacja
    m_pYTable = new unsigned char[1+(uiXSize*uiYSize)];
    
    fread(m_pYTable,1,uiXSize*uiYSize,plik);	// wczytaj tablice
    fclose(plik);
    
    m_pTexture = NULL;
    m_pTexture = new CBitmap(256,256,cTexture);
}

CPinch::CPinch(unsigned int uiXSize, unsigned int uiYSize, char cXTable[], char cYTable[], char cTexture[], bool bNIC)
{

    m_uiXSize = uiXSize; 	// zapamietaj na potem
    m_uiYSize = uiYSize;

    m_pXTable = NULL;	// wyzeruj przed alokacja
    m_pXTable = new unsigned char[1+(uiXSize*uiYSize)];
    
    m_pYTable = NULL;	// wyzeruj przed alokacja
    m_pYTable = new unsigned char[1+(uiXSize*uiYSize)];

    m_pXMap = NULL; // wczytaj obraz x
    m_pXMap = new CBitmap(uiXSize,uiYSize,cXTable);
    
    m_pYMap = NULL; // wczytaj obraz y
    m_pYMap = new CBitmap(uiXSize,uiYSize,cYTable);
    
    // przetwarzanie bitmapy
    
    for (int i=0; i<(uiXSize*uiYSize); i++)
    {
	m_pXTable[i] = m_pXMap->ucGetDataR(i);
	m_pYTable[i] = m_pYMap->ucGetDataR(i);
    }
    
    m_pTexture = NULL;
    m_pTexture = new CBitmap(256,256,cTexture);
}


//=== destruktor

CPinch::~CPinch()
{
    if (m_pXTable!=NULL) // skazuj tablice jezeli uzywana
    {
	delete []m_pXTable;
	m_pXTable = NULL;
    }
    
    if (m_pYTable!=NULL)
    {
	delete []m_pYTable;
	m_pYTable = NULL;
    }
    
    if (m_pTexture!=NULL)
    {
	delete m_pTexture;
	m_pTexture = NULL;
    }

}

//=== zwieksz X

void CPinch::IncX(char ucVal)
{
    for (int i=0; i<(m_uiXSize*m_uiYSize); i++) 
	m_pXTable[i]+=ucVal;
}

void CPinch::IncY(char ucVal)
{
    for (int i=0; i<(m_uiXSize*m_uiYSize); i++) 
	m_pYTable[i]+=ucVal;
}

// rysuj

void CPinch::Render(unsigned char *pBuffer)
{
    unsigned int uiAdres;
    unsigned int uiTAdres;

    for (int h1=0; h1<m_uiYSize; h1++)
    {
	for (int h2=0; h2<m_uiXSize; h2++)
	{
	    uiAdres = ((800*h1)+h2)<<2;
	    uiTAdres = (m_pYTable[uiAdres>>2]<<8)+m_pXTable[uiAdres>>2];
	
	    pBuffer[uiAdres] = m_pTexture->ucGetDataR(uiTAdres);
	    pBuffer[uiAdres+1] = m_pTexture->ucGetDataG(uiTAdres);
	    pBuffer[uiAdres+2] = m_pTexture->ucGetDataB(uiTAdres);	    
	}
    }    
}

void CPinch::RenderBlur(unsigned char *pBuffer)
{
    unsigned int uiAdres;
    unsigned int uiTAdres;

    unsigned char ucKolor;

    for (int h1=0; h1<m_uiYSize; h1++)
    {
	for (int h2=0; h2<m_uiXSize; h2++)
	{
	    uiAdres = ((800*h1)+h2)<<2;
	    uiTAdres = (m_pYTable[uiAdres>>2]<<8)+m_pXTable[uiAdres>>2];
	
	    ucKolor = pBuffer[uiAdres];
	    pBuffer[uiAdres] = (ucKolor+m_pTexture->ucGetDataR(uiTAdres))/2;

	    ucKolor = pBuffer[uiAdres+1];
	    pBuffer[uiAdres+1] = (ucKolor+m_pTexture->ucGetDataG(uiTAdres))/2;

	    ucKolor = pBuffer[uiAdres+2];
	    pBuffer[uiAdres+2] = (ucKolor+m_pTexture->ucGetDataB(uiTAdres))/2;	    
	}
    }    
}


void CPinch::Render(int iXSize, int iYSize, unsigned char *pBuffer)
{
    unsigned int uiAdres;
    unsigned int uiTAdres;

    int d1, d2;

    double x_factor;

    x_factor = iXSize/m_uiXSize;

    printf("xfactor: %d\n",x_factor);

    for (int h1=0; h1<iYSize; h1++)
    {
	for (int h2=0; h2<iXSize; h2++)
	{
	    uiAdres = ((800*h1)+h2)<<2;
	    
	    d1 = (int)(h1 / (double)(iYSize/m_uiYSize));

	    d2 = (int)(h2 / (double)(iXSize/m_uiXSize));
    
	    uiTAdres = (m_pXTable[h1]<<8)+m_pYTable[h2];
	
	    pBuffer[uiAdres] = m_pTexture->ucGetDataR(uiTAdres);
	    pBuffer[uiAdres+1] = m_pTexture->ucGetDataG(uiTAdres);
	    pBuffer[uiAdres+2] = m_pTexture->ucGetDataB(uiTAdres);	    
	}
    }    
}
