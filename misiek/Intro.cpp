// Intro.cpp: implementation of the CIntro class.
//
//////////////////////////////////////////////////////////////////////

#include "Intro.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//=== konstruktor zeruje wskazniki

CIntro::CIntro()
{
	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	m_bActive = false;

	m_pFile = NULL;

	for (int iLicznik=0; iLicznik<110; iLicznik++)
	{
			m_pAnimation[iLicznik]=NULL;
	}

	m_lLastFrame = 0;

}

//=== destruktor zwalnia pamiec

CIntro::~CIntro()
{

	if (m_pFile != NULL)
	{
		delete m_pFile;
		m_pFile = NULL;
	}

	for (int iLicznik=0; iLicznik<110; iLicznik++)
	{
		if (m_pAnimation[iLicznik]!=NULL)
		{
			delete m_pAnimation[iLicznik];
			m_pAnimation[iLicznik] = NULL;
		}
	}

	m_bActive = false;
}


//=== deinicjalizacja modulu, pamieta aktualny stan

void CIntro::DeInitialize(void)
{
	
	if (m_pFile != NULL)
	{
		delete m_pFile;
		m_pFile = NULL;
	}

	for (int iLicznik=0; iLicznik<110; iLicznik++)
	{
		if (m_pAnimation[iLicznik]!=NULL)
		{
			delete m_pAnimation[iLicznik];
			m_pAnimation[iLicznik] = NULL;
		}
	}

	m_bActive = false;
}


//=== ustawianie aktywnosci - czy dane sa w pamieci

void CIntro::SetActive(bool bState)
{
	m_bActive = bState;
}

//=== zwraca informacje czy dane sa wczytane

bool CIntro::GetActive(void)
{
	return m_bActive;
}

//=== inicjalizacja modulu

void CIntro::Initialize(IDirect3DDevice8 *pDevice,char CurrentDirectory[200], CAudio *pAudio)
{
	
	char cFrameFilename[20];// = {"a","n","i","m","0","0","0","0",".","b","m","p",NULL};	// nazwa pliku z jedna klatka
	
	char znakA=0x30;
	char znakB=0x30; 
	char znakC=0x30;
/*
	m_pFile = new CFileSystem("Resource\\intro.fox");	// otworz archiwum

	for (int iLicznik=0; iLicznik<110; iLicznik++)
	{
		for (int i=0; i<20; i++) cFrameFilename[i]=0;

		sprintf(cFrameFilename,"anim0000.jpg");
		cFrameFilename[5] = znakA;
		cFrameFilename[6] = znakB;
		cFrameFilename[7] = znakC;
	
		m_pFile->Load(cFrameFilename);

		m_pAnimation[iLicznik] = new CSprite(255,255,255,255);

		m_pAnimation[iLicznik]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search(cFrameFilename), pDevice);
	
		znakC++;

		if (znakC==0x3a)
		{
			znakB++;
			znakC=0x30;
		}

		if (znakB==0x3a)
		{
			znakA++;
			znakB=0x30;
		}

	}

	// koniec
	
	delete m_pFile;	// zwolnij system plikow
	m_pFile = NULL; // zeruj wskaznik
*/
	m_bActive = true;	// dane wczytane
}

//=== rysuje pojedyncza klatke

int CIntro::DrawScene(long lTimer,float fMouseX, float fMouseY, 
					  bool bLeftButton, bool bCenterButton, bool bRightButton, CAudio *pAudio, IDirect3DDevice8 *pDevice)
{
	char cFrameFilename[20];// = {"a","n","i","m","0","0","0","0",".","b","m","p",NULL};	// nazwa pliku z jedna klatka
	
	char znakA=0x30;
	char znakB=0x30; 
	char znakC=0x30;

	m_pFile = new CFileSystem("Resource\\intro.fox");	// otworz archiwum

	for (int iLicznik=0; iLicznik<m_lLastFrame; iLicznik++)
	{
		for (int i=0; i<20; i++) cFrameFilename[i]=0;

		sprintf(cFrameFilename,"anim0000.jpg");
		cFrameFilename[5] = znakA;
		cFrameFilename[6] = znakB;
		cFrameFilename[7] = znakC;
	
		znakC++;

		if (znakC==0x3a)
		{
			znakB++;
			znakC=0x30;
		}

		if (znakB==0x3a)
		{
			znakA++;
			znakB=0x30;
		}

	}

		m_pFile->Load(cFrameFilename);

		m_pAnimation[iLicznik] = new CSprite(255,255,255,255);

		m_pAnimation[iLicznik]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search(cFrameFilename), pDevice);

	// koniec
	
	delete m_pFile;	// zwolnij system plikow
	m_pFile = NULL; // zeruj wskaznik


	m_pAnimation[m_lLastFrame]->SetScale(3.125f,2.343f);
	m_pAnimation[m_lLastFrame]->Render();

	delete m_pAnimation[iLicznik];
	m_pAnimation[iLicznik]=NULL;


	if (m_lLastTimer!=lTimer && m_lLastFrame!=109)
	{
			m_lLastFrame++;
	}

	m_lLastTimer=lTimer;	// zapamietaj czas

	return (int) m_lLastFrame; // aktualnie rysowana klatka

}
