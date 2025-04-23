#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Button.h"

//=== tworzy przycisk na podstawie trzech bitmap ===

CButton::CButton(char cStatic[], char cOnClick[], char cOnMouse[])
{

    // zerowanie wskaznikow
    
    m_pStatic = m_pOnClick = m_pOnMouse = NULL;
    
    m_pStatic = new CBitmap(cStatic,TGA);
    m_pOnClick = new CBitmap(cOnClick,TGA);
    m_pOnMouse = new CBitmap(cOnMouse,TGA);

    // zerujemy wszystkie wspolrzedne
    
    m_iXPosition = m_iYPosition = 0;
    
    m_iHotXPositionStart = m_iHotXPositionEnd = 
    m_iHotYPositionStart = m_iHotYPositionEnd = 0;
    
    // jeszcze nie ma pierwszego wejscia
    
    m_bFE = false;
}

// dodatkowe ustawienie wspolrzednych rysowania w konstruktorze

CButton::CButton(char cStatic[], char cOnClick[], char cOnMouse[],
         int iXPosition, int iYPosition)
{

    // zerowanie wskaznikow
    
    m_pStatic = m_pOnClick = m_pOnMouse = NULL;
    
    m_pStatic = new CBitmap(cStatic,TGA);
    m_pOnClick = new CBitmap(cOnClick,TGA);
    m_pOnMouse = new CBitmap(cOnMouse,TGA);

    // zerujemy wszystkie wspolrzedne

    SetPosition(iXPosition, iYPosition);
    
    m_iHotXPositionStart = m_iHotXPositionEnd = 
    m_iHotYPositionStart = m_iHotYPositionEnd = 0;
    
    // jeszcze nie ma pierwszego wejscia
    
    m_bFE = false;
}

// dodatkowe ustawienie wszystkich wspolrzednych

CButton::CButton(char cStatic[], char cOnClick[], char cOnMouse[],
         int iXPosition, int iYPosition,
         int iHotXPositionStart, int iHotYPositionStart,
         int iHotXPositionEnd, int iHotYPositionEnd)
{

    // zerowanie wskaznikow
    
    m_pStatic = m_pOnClick = m_pOnMouse = NULL;
    
    m_pStatic = new CBitmap(cStatic,TGA);
    m_pOnClick = new CBitmap(cOnClick,TGA);
    m_pOnMouse = new CBitmap(cOnMouse,TGA);

    // zerujemy wszystkie wspolrzedne

    SetPosition(iXPosition, iYPosition);
    SetHotPosition(iHotXPositionStart,iHotYPositionStart,
            iHotXPositionEnd, iHotYPositionEnd);
    
    // jeszcze nie ma pierwszego wejscia
    
    m_bFE = false;
}

//=== inicjalizacja przycisku ze skryptu

CButton::CButton(char cScriptFile[])
{
	FILE *plik;
	char linia[256];

    // zerowanie wskaznikow
    
    m_pStatic = m_pOnClick = m_pOnMouse = NULL;

	printf("CButton: inicjalizacja ze skryptu - %s\n",cScriptFile);
	
	plik = fopen(cScriptFile,"r");
	fscanf(plik,"%s\n",&linia);	// wczytaj 
	printf("TYP: %s\n",linia);

	while (strcmp(linia,"</BUTTON>"))
	{
		fscanf(plik,"%s\n",&linia);	// wczytaj 
		
		if (!strcmp(linia,"<NAZWA>")) // odczytujemy w nastepnej linii nazwe przycisku
		{
			fscanf(plik,"%s\n",&m_cName);
			UpOnly(m_cName);	// tylko duze litery
			printf("NAZWA: %s\n",m_cName);
		}
		
		if (!strcmp(linia,"<STATIC>"))	// standardowy obraz
		{
			fscanf(plik,"%s\n",&linia);
			printf("STATIC: %s\n",linia);
			m_pStatic = new CBitmap(linia,TGA);
		}
		
		if (!strcmp(linia,"<ON_MOUSE>"))	// myszka nad obrazem
		{
			fscanf(plik,"%s\n",&linia);
			printf("ON_MOUSE: %s\n",linia);
			m_pOnMouse = new CBitmap(linia,TGA);
		}
		
		if (!strcmp(linia,"<ON_CLICK>"))	// klikniety obraz
		{
			fscanf(plik,"%s\n",&linia);
			printf("ON_CLICK: %s\n",linia);
			m_pOnClick = new CBitmap(linia,TGA);
		}
		
		if (!strcmp(linia,"<XY>"))	// standardowy obraz
		{
			fscanf(plik,"%d %d\n",&m_iXPosition,&m_iYPosition);
			printf("RYSOWANE NA: %d %d\n",m_iXPosition,m_iYPosition);
		}
		
		if (!strcmp(linia,"<XY_ACTIVE>"))	// standardowy obraz
		{
			fscanf(plik,"%d %d %d %d\n",&m_iHotXPositionStart,&m_iHotYPositionStart,
										&m_iHotXPositionEnd,&m_iHotYPositionEnd);
			printf("AKTYWNE NA: %d %d %d %d\n",m_iHotXPositionStart,m_iHotYPositionStart,
											m_iHotXPositionEnd,m_iHotYPositionEnd);
		}		
	}
		
	fclose(plik);
    
    // jeszcze nie ma pierwszego wejscia
    
    m_bFE = false;

}


//=== destruktor zwalnia pamiec po obiektach ===

CButton::~CButton()
{
	if (m_pOnClick!=NULL)
	{
		delete m_pOnClick;
		m_pOnClick = NULL;
	}

	if (m_pStatic!=NULL) 
	{
		delete m_pStatic;
		m_pStatic = NULL;
	}

	if (m_pOnMouse!=NULL) 
	{
		delete m_pOnMouse;
		m_pOnMouse = NULL;
	}
}

//=== rysuje przycisk w zaleznosci od stanu myszy ===

int CButton::Render(int iMouseX, int iMouseY, bool bLeftButton, bool bCenterButton,
                bool bRightButton, unsigned char *pBackBuffer)
{

	// sprawdzamy czy przycisk jest wcisniety na podstawie goracych wspolrzednych
	// jezeli jest to wyswietlamy bitmape w odpowiednim stanie

	if ((iMouseX>m_iHotXPositionStart)&&
	   (iMouseX<m_iHotXPositionEnd)&&
	   (iMouseY>m_iHotYPositionStart)&&
	   (iMouseY<m_iHotYPositionEnd))
	{
		if (bRightButton)
		{
			m_pOnClick->Render(m_iXPosition,m_iYPosition,pBackBuffer);	// przycisk wcisniety prawym klawiszem
			return 4;
		}

		if (bCenterButton)
		{
			m_pOnClick->Render(m_iXPosition,m_iYPosition,pBackBuffer);
			return 3;
		}
		
		if (bLeftButton)
		{
			m_pOnClick->Render(m_iXPosition,m_iYPosition,pBackBuffer);
			return 2;
		}

		m_pOnMouse->Render(m_iXPosition,m_iYPosition,pBackBuffer);
		return 1;
	}

	m_pStatic->Render(m_iXPosition,m_iYPosition,pBackBuffer);
	return 0;

}

//=== ustawia wspolrzedne przycisku ===

void CButton::SetPosition(int iXPosition, int iYPosition)
{
    m_iXPosition = iXPosition;
    m_iYPosition = iYPosition;
}

//=== ustawia wspolrzedne w obrebie ktorych przycisk jest aktywny

void CButton::SetHotPosition(int iHotXPositionStart, int iHotYPositionStart,
                int iHotXPositionEnd, int iHotYPositionEnd)
{
        m_iHotXPositionStart = iHotXPositionStart;
        m_iHotXPositionEnd = iHotXPositionEnd;
        m_iHotYPositionStart = iHotYPositionStart;
        m_iHotYPositionEnd = iHotYPositionEnd;
}

//=== kapitalizacja ciagu znakow ===

void CButton::UpOnly(char str[])
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


//=== end ===
