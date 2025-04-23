#include "button.h"
#include <stdio.h>
#include <stdlib.h>

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

//=== end ===
