// Mapa.cpp: implementation of the CMapa class.
//
//////////////////////////////////////////////////////////////////////

#include "Mapa.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//=== konstruktor

CMapa::CMapa()
{
	
	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	m_bActive = false;

	m_pBackground = NULL;	// zerujemy wskazniki
	m_pFile = NULL;
	m_pExitButton = NULL;
	m_pMysticLogo = NULL;
}

//=== destruktor 

CMapa::~CMapa()
{
	
	if (m_pMysticLogo!=NULL)
	{
		delete m_pMysticLogo;
		m_pMysticLogo=NULL;
	}

	// zwolnij tlo jezeli uzywane
	
	if (m_pBackground!=NULL)
	{
		delete m_pBackground;
		m_pBackground=NULL;
	}

	// zwolnij archiwum jezeli uzywane

	if (m_pFile!=NULL)
	{
		delete m_pFile;
		m_pFile = NULL;
	}

	// zwolnij przycisk exit jezeli uzywane

	if (m_pExitButton!=NULL)
	{
		delete m_pExitButton;
		m_pExitButton=NULL;
	}

	// ustaw stan na nieaktywny (brak danych w pamieci)

	m_bActive = false;
}

//=== ustawianie aktywnosci - czy dane sa w pamieci

void CMapa::SetActive(bool bState)
{
	m_bActive = bState;
}

//=== zwraca informacje czy dane sa wczytane

bool CMapa::GetActive(void)
{
	return m_bActive;
}

//=== aktualizuje i wczytuje dane

void CMapa::Initialize(IDirect3DDevice8 *pDevice)
{
	
	m_pFile = new CFileSystem("Resource\\klocki.fox");
	m_pFile->Load("mystic.tga");
	m_pMysticLogo = new CSprite(255,255,255,255);
	m_pMysticLogo->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("mystic.tga"), pDevice);
	delete m_pFile;
	m_pFile = NULL;

	m_pFile = new CFileSystem("Resource\\plansze.fox");	// otworz archiwum
	m_pFile->Load("lok01.bmp");	// wczytujemy tlo

	m_pBackground = new CSprite(255,255,255,255);	// nowy sprite

	m_pBackground->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("lok01.bmp"), pDevice);
		
	m_bActive = true;	// dane wczytane

	// zainicjalizuj przycisk exit

	m_pExitButton = new CButton("Resource\\przycisk.fox",
								"exit01.tga",
								"exit03.tga",
								"exit02.tga",pDevice);

	// koniec
	
	delete m_pFile;	// zwolnij system plikow
	m_pFile = NULL;	// zeruj wskaznik
}

//=== deaktualizuje, ale trzyma znaczniki (zwalnia tylko textury)

void CMapa::DeInitialize(void)
{

	if (m_pMysticLogo!=NULL)
	{
		delete m_pMysticLogo;
		m_pMysticLogo=NULL;
	}

	// zwolnij tlo jezeli uzywane
	
	if (m_pBackground!=NULL)
	{
		delete m_pBackground;
		m_pBackground=NULL;
	}

	// zwolnij archiwum jezeli uzywane

	if (m_pFile!=NULL)
	{
		delete m_pFile;
		m_pFile = NULL;
	}

}

//=== rysuje pojedyncza klatke

int CMapa::DrawScene(long lTimer,float fMouseX, float fMouseY, 
					  bool bLeftButton, bool bRightButton, bool bCenterButton)
{
	m_pBackground->Render();	// rysuj tlo

	m_pMysticLogo->SetTranslation(32,32);
	m_pMysticLogo->Render();
	
	m_pExitButton->SetPosition(0,472);	// lewy dolny rog
	
	if (bLeftButton) return 2;
	return 0;//m_pExitButton->Draw(fMouseX,fMouseY,bLeftButton,bRightButton,bCenterButton); // przycisk

}
//end
