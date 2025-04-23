
#include "pinch.h"

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
	    uiTAdres = (m_pYTable[h1]<<8)+m_pXTable[h2];
	
	    pBuffer[uiAdres] = m_pTexture->ucGetDataR(uiTAdres);
	    pBuffer[uiAdres+1] = m_pTexture->ucGetDataG(uiTAdres);
	    pBuffer[uiAdres+2] = m_pTexture->ucGetDataB(uiTAdres);	    
	}
    }    
}
