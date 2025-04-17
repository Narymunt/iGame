// Quiz.cpp: implementation of the CQuiz class.
//
//////////////////////////////////////////////////////////////////////

#include "Quiz.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQuiz::CQuiz()
{
	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	m_bActive = false;

	m_pBackground = NULL;	// zerujemy wskazniki
	m_pFile = NULL;
	m_pExitButton = NULL;

	m_pMysticLogo = NULL;	// rysunek

}

//=== destruktor zwalnia pamiec i zeruje wskazniki

CQuiz::~CQuiz()
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

void CQuiz::SetActive(bool bState)
{
	m_bActive = bState;
}

//=== zwraca informacje czy dane sa wczytane

bool CQuiz::GetActive(void)
{
	return m_bActive;
}

//=== aktualizuje i wczytuje dane

void CQuiz::Initialize(IDirect3DDevice8 *pDevice,char CurrentDirectory[200], CAudio *pAudio)
{
	// wczytaj logo mystic
	
	m_pFile = new CFileSystem("Resource\\klocki.fox");
	m_pFile->Load("mystic.tga");
	m_pMysticLogo = new CSprite(255,255,255,255);
	m_pMysticLogo->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("mystic.tga"), pDevice);

	delete m_pFile;
	m_pFile = NULL;

	
	m_pFile = new CFileSystem("Resource\\plansze.fox");	// otworz archiwum
	m_pFile->Load("quiz001.bmp");	// wczytujemy tlo

	m_pBackground = new CSprite(255,255,255,255);	// nowy sprite

	m_pBackground->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("quiz001.bmp"), pDevice);
		
	// zainicjalizuj przycisk exit

	m_pExitButton = new CButton("Resource\\przycisk.fox",
								"exit01.tga",
								"exit03.tga",
								"exit02.tga",pDevice);

	// koniec
	
	delete m_pFile;	// zwolnij system plikow
	m_pFile = NULL; // zeruj wskaznik

	//=== AKTYWACJA ===

	m_bActive = true;	// dane wczytane


}

//=== deaktualizuje, ale trzyma znaczniki (zwalnia tylko textury)

void CQuiz::DeInitialize(void)
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

int CQuiz::DrawScene(long lTimer,float fMouseX, float fMouseY, 
					  bool bLeftButton, bool bCenterButton, bool bRightButton, CAudio *pAudio)
{

	
	m_pBackground->Render();	// rysuj tlo

	m_pMysticLogo->SetTranslation(32,472);
	m_pMysticLogo->Render();

	// reszta

	m_pExitButton->SetPosition(0,472);	// prawy dolny rog

	m_lLastTimer=lTimer;	// zapamietaj czas

	return m_pExitButton->Draw(fMouseX,fMouseY,bLeftButton,bCenterButton,bRightButton); // przycisk

}
//end
