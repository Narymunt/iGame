// LoadScreen.cpp: implementation of the CAnimPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "AnimPlayer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnimPlayer::CAnimPlayer()
{
	for (int i=0; i<EVT_LIMIT; i++)	// czyszczenie tablic
	{
		m_bActive[i] = false;
		m_cType[i] = 255;
	}

}

CAnimPlayer::~CAnimPlayer()
{
	for (int i=0; i<EVT_LIMIT; i++)
	{
		if (m_bActive[i])
		{
			delete m_pPlayer[i];
			m_bActive[i] = false;
		}
	}
}


//=== aktualizuje i wczytuje dane

void CAnimPlayer::Initialize(IDirect3DDevice8 *pDevice)
{
	FILE	*plik;	
	char	linia[1024];
	int		licznik;

	if ((plik=fopen("demo.ini","r"))==NULL)
	{
		MessageBox(NULL,"ERROR! Brak pliku demo.ini!","ERROR", MB_OK);
		PostQuitMessage( 0 );
	}

	licznik = 0;	// ile animacji wczytano

	while (strcmp(linia,"</DEMO>"))
	{
		fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku

		// rozpoczecie skryptu
		if (!strcmp(linia,"<ANIMATION>"))
		{
			fscanf(plik,"%s\n",&m_cAnimFilename[licznik]);	// nazwa pliku .bin
			fscanf(plik,"%d\n",&m_cEventNo[licznik]);	// numer eventu
			fscanf(plik,"%d %d %d\n",&m_lTimerLoad[licznik],&m_lTimerStart[licznik],&m_lTimerEnd[licznik]); // load start end
			fscanf(plik,"%d\n",&m_iFPS[licznik]);
			fscanf(plik,"%d %d %d %d\n",&m_lPositionX[licznik],&m_lPositionY[licznik],&m_iScaleX[licznik], &m_iScaleY[licznik]);
			fscanf(plik,"%s\n",&linia);

			if (!strcmp(linia,"LOOP")) m_cType[licznik]=0;
			if (!strcmp(linia,"LAST_FRAME")) m_cType[licznik]=1;
			if (!strcmp(linia,"NO_FRAME")) m_cType[licznik]=2;
			
			// jezeli ma bys cos wgrane na starcie to od razu wgrywamy

			if (m_lTimerLoad[licznik]==0)
			m_pPlayer[licznik] = new CEventEVT(m_cAnimFilename[licznik],"anim.evt",pDevice);

			m_bActive[licznik] = true;

			licznik ++;
		} // <ANIMATOR>
	} // while

	fclose(plik);

}

void CAnimPlayer::DeInitialize(void)
{
	for (int i=0; i<EVT_LIMIT; i++)
	{
		if (m_bActive[i])
		{
			delete m_pPlayer[i];
			m_bActive[i] = false;
		}
	}
}

//=== rysuje pojedyncza klatke

int CAnimPlayer::DrawScene(IDirect3DDevice8 *pDevice, long lTimer)
{

	for (int i=0; i<EVT_LIMIT; i++)
	{

		// najpierw sprawdzamy czy nie powinnismy wczytac jakiejs animacji

		if (m_lTimerLoad[i]>lTimer && m_lTimerEnd[i]<lTimer && m_bActive[i])
		{
			m_pPlayer[i] = new CEventEVT(m_cAnimFilename[i],"anim.evt",pDevice);
			m_bActive[i] = true;
		}

		// teraz sprawdzamy czy nie powinnismy jakiejs animacji odtworzyc

		if (m_lTimerStart[i]<lTimer && m_lTimerEnd[i]>lTimer && m_bActive[i])
		{
			m_pPlayer[i]->PutScaled(m_iScaleX[i]/100,m_iScaleY[i]/100,lTimer%20,m_cEventNo[i]);
		}

		// teraz sprawdzamy czy nie powinnismy jakies animacji wyrzucic z pamieci

		if (m_lTimerEnd[i]<lTimer && m_bActive[i])
		{
			delete m_pPlayer[i];
			m_bActive[i] = false;
		}

	}

	return 0;

}