// Mouse.cpp: implementation of the CMouse class.
//
//////////////////////////////////////////////////////////////////////

#include "Mouse.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//=== konstruktor - inicjalizuje myszke

CMouse::CMouse()
{

	for (int i=0; i<16; i++) m_pCustomPoint[i]=NULL;

	// przyciski nie wcisniete

	m_bLeftButton = false;
	m_bRightButton = false;
	m_bCenterButton = false;

	// hotspot 0,0

	m_bAlfaSpot = false;

	// hot X,Y = 0

	m_cHotX = 0; 
	m_cHotY = 0; 

	// tutaj ladowane obiekty

	m_pMouseFile = NULL;	// plik ze wskaznikami
	
	m_pNormalPoint = NULL;	// zerowanie wskanzikow 
	m_pOnClickPoint = NULL;
	m_pOnObjectPoint = NULL;

	m_cState = 1;

}

//=== destruktor - zwalnia pamiec po obiektach

CMouse::~CMouse()
{
	
	for (int i=0; i<16; i++)
	{
		if (m_pCustomPoint[i]!=NULL)
		{
			delete m_pCustomPoint[i];
			m_pCustomPoint[i]=NULL;
		}
	}


	if (m_pMouseFile!=NULL)		// zwolnij system plikow od myszki
	{
		delete m_pMouseFile;
		m_pMouseFile = NULL;
	}

	if (m_pNormalPoint != NULL)	// zwolnij wskaznik normalnego punktu
	{
		delete m_pNormalPoint;
		m_pNormalPoint = NULL;
	}

	if (m_pOnClickPoint != NULL) // zwolnij wskaznik punktu na kliknieciu
	{
		delete m_pOnClickPoint;
		m_pOnClickPoint = NULL;
	}

	if (m_pOnObjectPoint != NULL) // zwolnij wskaznik punktu nad obiektem
	{
		delete m_pOnObjectPoint;
		m_pOnObjectPoint = NULL;
	}

}

//=== ustawia stan lewego przycisku 
//=== true - wcisniety
//=== false - nie nacisniety

void CMouse::SetLeftButtonState(bool bState)
{
	m_bLeftButton = bState;
}

//=== ustawia stan prawego przycisku
//=== true - wcisniety
//=== false - nie nacisniety

void CMouse::SetRightButtonState(bool bState)
{
	m_bRightButton = bState;
}

//=== ustawia stan srodkowego przycisku
//=== true - wcisniety
//=== false - ne nacisniety

void CMouse::SetCenterButtonState(bool bState)
{
	m_bCenterButton = bState;
}

//=== zwraca stan lewego przycisku
//=== enumeracja tak samo jak przy stawianiu

bool CMouse::GetLeftButtonState(void)
{
	return m_bLeftButton;
}

//=== zwraca stan prawego przycisku
//=== enumeracja tak samo jak przy stawianiu

bool CMouse::GetRightButtonState(void)
{
	return m_bRightButton;
}

//=== zwraca stan srodkowego przycisku
//=== enumeracja tak samo jak przy stawianiu

bool CMouse::GetCenterButtonState(void)
{
	return m_bCenterButton;
}

//=== ustawia wspolrzedne przechwycone z petli glownej

void CMouse::SetMouseX(float fPosition)
{
	m_fLastMouseX = m_fMouseX;
	m_fMouseX = fPosition;
}

//=== ustawia wspolrzedne przechwycone z petli glownej

void CMouse::SetMouseY(float fPosition)
{
	m_fLastMouseY = m_fMouseY;
	m_fMouseY = fPosition;
}

//=== zwraca wspolrzedne X

float CMouse::GetMouseX(void)
{
	return m_fMouseX;
}

//=== zwraca wspolrzedne Y

float CMouse::GetMouseY(void)
{
	return m_fMouseY;
}

//=== ustawia ostatnia wspolrzedna X, normalnie nie uzwane

void CMouse::SetLastMouseX(float fPosition)
{
	m_fLastMouseX = fPosition;
}

//=== ustawia ostatnia wspolrzedna Y, normalnie nie uzywane

void CMouse::SetLastMouseY(float fPosition)
{
	m_fLastMouseY = fPosition;
}

//=== zwraca ostatnia wspolrzedna X, aktualizowane co klatke

float CMouse::GetLastMouseX(void)
{
	return m_fLastMouseX;
}

//=== zwraca ostatnia wspolrzedna Y, aktualizowane co klatke

float CMouse::GetLastMouseY(void)
{
	return m_fLastMouseY;
}

//=== ustawia czy aktywna ma byc alfa czy hotspot

void CMouse::SetAlfaSpot(bool bState)
{
	m_bAlfaSpot = bState;
}

//=== odczytuje czy aktywna ma byc alfa czy hotspot

bool CMouse::GetAlfaSpot(void)
{
	return m_bAlfaSpot;
}

//=== ustawia delteX, normalnie nie uzywane

void CMouse::SetDeltaX(float fValue)
{
	m_fDeltaX = fValue;
}

//=== ustawia delteY, normalnie nie uzywane

void CMouse::SetDeltaY(float fValue)
{
	m_fDeltaY = fValue;
}

//=== zwraca delteX

float CMouse::GetDeltaX(void)
{
	return m_fDeltaX;
}

//=== zwraca delteY

float CMouse::GetDeltaY(void)
{
	return m_fDeltaY;
}

//=== wczytuje wyglad kursora myszy

void CMouse::Initialize(IDirect3DDevice8 *pDevice,char cDataFile[])
{
	m_pMouseFile = new CFileSystem(cDataFile);	// otworz system plikow

	m_pMouseFile->Load("m_point.tga");	// wczytaj pierwszy obrazek

	m_pNormalPoint = new CSprite(255,255,255,255);	// alfa z tga

	// zainicjalizuj 
	
	m_pNormalPoint->InitializeTGAinMemory((unsigned int*)m_pMouseFile->pDataBuffer,
		m_pMouseFile->Search("m_point.tga"),pDevice);

	// tutaj dalsze wskazniki
	
	m_pMouseFile->Load("m_hand.tga");
	m_pOnObjectPoint = new CSprite(255,255,255,255);
	m_pOnObjectPoint->InitializeTGAinMemory((unsigned int*)m_pMouseFile->pDataBuffer,
		m_pMouseFile->Search("m_hand.tga"),pDevice);

	m_pMouseFile->Load("m_hand.tga");
	m_pOnClickPoint = new CSprite(255,255,255,255);
	m_pOnClickPoint->InitializeTGAinMemory((unsigned int*)m_pMouseFile->pDataBuffer,
		m_pMouseFile->Search("m_hand.tga"),pDevice);

	// filesystem juz jest niepotrzebny

	delete m_pMouseFile;
	m_pMouseFile = NULL;

}

//=== zwalnia wskazniki uzywane przy inicjalizacji

void CMouse::DeInitialize(void)
{
	for (int i=0; i<16; i++)
	{
		if (m_pCustomPoint[i]!=NULL)
		{
			delete m_pCustomPoint[i];
			m_pCustomPoint[i]=NULL;
		}
	}
	
	if (m_pMouseFile!=NULL)		// zwolnij system plikow od myszki
	{
		delete m_pMouseFile;
		m_pMouseFile = NULL;
	}

	if (m_pNormalPoint != NULL)	// zwolnij wskaznik normalnego punktu
	{
		delete m_pNormalPoint;
		m_pNormalPoint = NULL;
	}

	if (m_pOnClickPoint != NULL) // zwolnij wskaznik punktu na kliknieciu
	{
		delete m_pOnClickPoint;
		m_pOnClickPoint = NULL;
	}

	if (m_pOnObjectPoint != NULL) // zwolnij wskaznik punktu nad obiektem
	{
		delete m_pOnObjectPoint;
		m_pOnObjectPoint = NULL;
	}
}

//=== renderuje zwykly wskaznik

void CMouse::Render(void)
{
	switch (m_cState)
	{
		case 1:
			m_pNormalPoint->SetTranslation(m_fMouseX, m_fMouseY);
			m_pNormalPoint->Render();
		break;

		case 2:
			m_pOnObjectPoint->SetTranslation(m_fMouseX, m_fMouseY);
			m_pOnObjectPoint->Render();
		break;

		case 3:
			m_pOnClickPoint->SetTranslation(m_fMouseX, m_fMouseY);
			m_pOnClickPoint->Render();
		break;
	}
}

// renderuje podany przez nas wskaznik

void CMouse::Render(int iNumer)
{
	m_pCustomPoint[iNumer]->SetTranslation(m_fMouseX, m_fMouseY);
	m_pCustomPoint[iNumer]->Render();
}

//=== ustawia stan myszy, na jego podstawie rysujemy odpowiedni wskaznik

void CMouse::SetState(char cState)
{
	m_cState = cState;
}

char CMouse::GetState(void)
{
	return m_cState;
}

// dodaj wlasny kursor

void CMouse::AddCustomPoint(IDirect3DDevice8 *pDevice, int iIndex, char cName[], char cDataFile[])
{
	m_pMouseFile = new CFileSystem(cDataFile);	// otworz system plikow

	m_pMouseFile->Load(cName);	// wczytaj pierwszy obrazek

	m_pCustomPoint[iIndex] = new CSprite(255,255,255,255);	// alfa z tga
	m_pCustomPoint[iIndex]->InitializeTGAinMemory((unsigned int*)m_pMouseFile->pDataBuffer,
		m_pMouseFile->Search(cName),pDevice);

	delete m_pMouseFile;
	m_pMouseFile =NULL;
}



// end
