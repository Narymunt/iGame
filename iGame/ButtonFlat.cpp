// implementation of class
// .bmp file is reversed, so at and we flip it

// w pliku ini to wyglada tak 
// <BUTTON_FLAT>
//
// <NAZWA>
// tutaj_nazwa_bez_spacji
//
// <IMAGE>
// resource/gui/buton.tga
//
// <X1Y1X2Y2>
// 10 10 74 74
//
// </BUTTON_FLAT>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ButtonFlat.h"

//=== class constructor

CButtonFlat::CButtonFlat(int x, int y, char filename[], int xscreen, int yscreen)
{
    m_pImage = new CBitmap(x,y,filename);
    m_ulSizeX = x; // zapamietaj na potem
    m_ulSizeY = y;
    m_ulX1 = xscreen;
    m_ulY1 = yscreen;
	m_ulX2 = m_ulX1 + m_ulSizeX;
	m_ulY2 = m_ulY1 + m_ulSizeY;
}

//=== class destructor

CButtonFlat::~CButtonFlat()
{
    delete m_pImage;
}

//=== inicjalizacja ze skryptu

CButtonFlat::CButtonFlat(char cScriptFile[])
{
   
    FILE *plik;
    char linia[256];

	printf("CButtonFlat: inicjalizacja ze skryptu - %s\n",cScriptFile);
	
	plik = fopen(cScriptFile,"r");
	fscanf(plik,"%s\n",&linia);	// wczytaj 
	printf("TYP: %s\n",linia);	// wyswietl czy to oby napewno odpowiedni format pliku
	
	while (strcmp(linia,"</BUTTON_FLAT>"))
	{
		fscanf(plik,"%s\n",&linia);	// wczytaj 

		if (!strcmp(linia,"<NAZWA>")) // odczytujemy w nastepnej linii nazwe przycisku
		{
			fscanf(plik,"%s\n",&m_cName);
			UpOnly(m_cName);	// tylko duze litery
			printf("NAZWA: %s\n",m_cName);
		}

		if (!strcmp(linia,"<IMAGE>"))	// standardowy obraz
		{
			fscanf(plik,"%s\n",&linia);
			printf("IMAGE: %s\n",linia);
			m_pImage = new CBitmap(linia,TGA);
		}

		if (!strcmp(linia,"<X1Y1X2Y2>"))	// gdzie rysujemy i aktywny
		{
			fscanf(plik,"%d %d %d %d\n",&m_ulX1,&m_ulY1,&m_ulX2,&m_ulY2);
			printf("RYSOWANE NA: %d %d %d %d\n",&m_ulX1,&m_ulY1,&m_ulX2,&m_ulY2);
		}
		
	
	} // </BUTTON_FLAT>

}

int CButtonFlat::Render1280(int mousex, int mousey, bool bleft, bool bright, unsigned char *pBuffer)
{
	m_pImage->Render1280(m_ulX1, m_ulY1, pBuffer);
	
	if ((mousex>m_ulX1)&&(mousex<(m_ulX2))&&
	    (mousey>m_ulY1)&&(mousey<(m_ulY2))&& bleft
	   ) return 1;
	    else return 0;
}

// dla 1024x768

int CButtonFlat::Render(int mousex, int mousey, bool bleft, bool bright, unsigned char *pBuffer)
{
	m_pImage->Render(m_ulX1, m_ulY1, pBuffer);
	
	if ((mousex>m_ulX1)&&(mousex<(m_ulX2))&&
	    (mousey>m_ulY1)&&(mousey<(m_ulY2))&& bleft
	   ) return 1;
	    else return 0;

}

//=== kapitalizacja ciagu znakow ===

void CButtonFlat::UpOnly(char str[])
{
	int i=0;
	char c;
	
	while (str[i])
	{
		c = str[i];
		str[i]= toupper(c);
		i++;
	}
}