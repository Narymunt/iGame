// Scene3d.cpp: implementation of the CScene3d class.
//
//////////////////////////////////////////////////////////////////////

//#include <iostream.h>
#include "Scene3d.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CScene3d::CScene3d(IDirect3DDevice8 *pDevice, char cFilename [])
{

	m_pBackground=NULL;
	m_pBlackScreen=NULL;
	m_pWhiteScreen=NULL;

	m_pBackground = new CSprite(255,255,255,255);	// nowy sprite
	m_pBackground->InitializeEx(cFilename,pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
	D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

	m_bDynamic = false;
	m_bActive = false;
	m_bFogEnable = false;
}

void CScene3d::ParseFromFile(IDirect3DDevice8 *pDevice, char cScriptFile[])
{

	FILE	*plik;	
	char	linia[1024];

	// ustaw domyslne parametry

	m_pBackground=NULL;
	m_pBlackScreen=NULL;
	m_pWhiteScreen=NULL;
	m_fPlayRate = 1.0f; // czas 1:1

	// sprawdz czy mozna odczytac plik

	if ((plik=fopen(cScriptFile,"r"))==NULL)
	{
		MessageBox(NULL,"ERROR! Brak pliku 3d!","ERROR", MB_OK);
		PostQuitMessage( 0 );
	}

	while (strcmp(linia,"</SCENE>"))
	{
		fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
		UpOnly(linia);

		// rozpoczecie skryptu
		if (!strcmp(linia,"<SCENE>"))
		{
			fscanf(plik,"%s\n",&linia);

			// tylko statyczne wczytywane od razu
			Initialize(pDevice,linia);	// wczytanie pliku .3d
		} 

		if (!strcmp(linia,"<PLAYRATE>"))
		{
			fscanf(plik,"%f\n",&m_fPlayRate);
		}

		if (!strcmp(linia,"LOOP")) m_bLoop = true;
		if (!strcmp(linia,"NO_LOOP")) m_bLoop = false;
		
		if (!strcmp(linia,"<FOG>"))
		{
			fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
			UpOnly(linia);
			
			if (!strcmp(linia,"ON")) m_bFogEnable = true;
			if (!strcmp(linia,"OFF")) m_bFogEnable = false;

			fscanf(plik,"%f\n",&m_fFogStart);
			fscanf(plik,"%f\n",&m_fFogEnd);
			fscanf(plik,"%d\n",&m_uiFogColor);

		}

		if (!strcmp(linia,"<CLEARSCREEN>"))
		{
			fscanf(plik,"%s\n",&linia);	// wczytaj nastepna linie
			UpOnly(linia);

			m_bBackground = false;	// nie ma tla
			m_pBackground = NULL;	// pusty wskaznik

			if (!strcmp(linia,"ON"))
			{
				m_bBackground = true;
				
				fscanf(plik,"%s\n",&linia);	// wczytaj nastepna linie, jakie czyszczenie ekranu
				UpOnly(linia);
				
				if (!strcmp(linia,"COLOR"))	// wypelniamy kolorem
				{
					fscanf(plik,"%d\n",&m_ucClearA);	// wypelnianie alfa
					fscanf(plik,"%d\n",&m_ucClearR);	// wypelnianie R
					fscanf(plik,"%d\n",&m_ucClearG);	// G
					fscanf(plik,"%d\n",&m_ucClearB);	// B
				}
				else // wypelniamy bitmapa
				{
					fscanf(plik,"%s\n",&linia);	// wczytaj nastepna linie, czyli nazwe pliku
					m_pBackground = new CSprite(255,255,255,255);	// nowy sprite
					strcpy(m_cBackgroundFilename,linia);
					
					if (!m_bDynamic) // wczytujemy jezeli statyczne
					{
						m_pBackground->InitializeEx(linia,pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
						D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);	
					}

					m_bBackground = true;
				}
			} // ON
		} // CLEARSCREEN

		if (!strcmp(linia,"<ONSCREEN>"))
		{
			fscanf(plik,"%s\n",&linia);	// wczytaj nastepna linie czy jest onscreen
			UpOnly(linia);			

			m_pForeground = NULL;

			if (!strcmp(linia,"ON")) // jest nakladka
			{
					fscanf(plik,"%s\n",&linia);	// wczytaj nastepna linie, czyli nazwe pliku
					m_pForeground = new CSprite(255,255,255,255);	// nowy sprite
					m_pForeground->InitializeEx(linia,pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
					D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);	
			}
		} // ON SCREEN

	} //</SCENE>
}

CScene3d::CScene3d(IDirect3DDevice8 *pDevice)
{
	m_pBackground=NULL;
	m_pBlackScreen=NULL;
	m_pWhiteScreen=NULL;
	m_pForeground = NULL;

	m_bActive = false;
}


CScene3d::~CScene3d()
{
	if (m_pForeground!=NULL)
	{
		delete m_pForeground;
		m_pForeground = NULL;
	}

	if (m_pBackground!=NULL)
	{
		delete m_pBackground;
		m_pBackground=NULL;
	}

	if (m_pBlackScreen!=NULL)
	{
		delete m_pBlackScreen;
		m_pBlackScreen=NULL;
	}

	if (m_pWhiteScreen!=NULL)
	{
		delete m_pWhiteScreen;
		m_pWhiteScreen=NULL;
	}
}

void CScene3d::DeInitialize(void)
{
	scene->CloseScene();
	
	if (m_pBackground!=NULL)
	{
		delete m_pBackground;
		m_pBackground=NULL;
	}

	if (m_pBlackScreen!=NULL)
	{
		delete m_pBlackScreen;
		m_pBlackScreen=NULL;
	}

	if (m_pWhiteScreen!=NULL)
	{
		delete m_pWhiteScreen;
		m_pWhiteScreen=NULL;
	}

	if (m_pForeground!=NULL)
	{
		delete m_pForeground;
		m_pForeground=NULL;
	}
}

void CScene3d::Initialize(IDirect3DDevice8 *pDevice,char cFilename[])
{

		strcpy(m_cFilename,cFilename);

		// jezeli statyczna to inicjalizujemy od razu

		if (!m_bDynamic)
		{
			m_bActive = true;	// dane wczytane

			scene = new G3D_CScene;
			scene->Initialize( pDevice );
	
			scene->Load(pDevice,cFilename);	
			scene->SetFlags(FLAG_RENDERFLARE|FLAG_SHADOW);

			scene->zMax = 50000.0f;
			scene->zMin = 5.0f;
			maxFrame = scene->dwFramesCount + 1;		
		}
}

void CScene3d::InitializeOut(IDirect3DDevice8 *pDevice,char cFilename[])
{
		m_pBlackScreen = new CSprite(255,255,255,255);
		m_pBlackScreen->InitializeEx("data\\black.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

		m_bActive = true;	// dane wczytane
		
		scene = new G3D_CScene;
		scene->Initialize( pDevice );
	
		scene->Load(pDevice,cFilename);	
		scene->SetFlags(FLAG_RENDERFLARE|FLAG_SHADOW);

		scene->zMax = 50000.0f;
		scene->zMin = 5.0f;
		maxFrame = scene->dwFramesCount + 1;		
}


void CScene3d::InitializeBlack(IDirect3DDevice8 *pDevice,char cFilename[])
{
		m_pBlackScreen = new CSprite(255,255,255,255);
		m_pBlackScreen->InitializeEx("data\\black.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

		m_bActive = true;	// dane wczytane
		
		scene = new G3D_CScene;
		scene->Initialize( pDevice );
	
		scene->Load(pDevice,cFilename);	
		scene->SetFlags(FLAG_RENDERFLARE|FLAG_SHADOW);

		scene->zMax = 50000.0f;
		scene->zMin = 5.0f;
		maxFrame = scene->dwFramesCount + 1;		
}

void CScene3d::InitializeWhite(IDirect3DDevice8 *pDevice,char cFilename[])
{
		m_pWhiteScreen = new CSprite(255,255,255,255);
		m_pWhiteScreen->InitializeEx("data\\white.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

		m_bActive = true;	// dane wczytane
		
		scene = new G3D_CScene;
		scene->Initialize( pDevice );
	
		scene->Load(pDevice,cFilename);	
		scene->SetFlags(FLAG_RENDERFLARE|FLAG_SHADOW);

		scene->zMax = 50000.0f;
		scene->zMin = 5.0f;
		maxFrame = scene->dwFramesCount + 1;		
}

void CScene3d::InitializeWhiteEnd(IDirect3DDevice8 *pDevice,char cFilename[])
{
		m_pWhiteScreen = new CSprite(255,255,255,255);
		m_pWhiteScreen->InitializeEx("data\\white.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

		m_bActive = true;	// dane wczytane
		
		scene = new G3D_CScene;
		scene->Initialize( pDevice );
	
		scene->Load(pDevice,cFilename);	
		scene->SetFlags(FLAG_RENDERFLARE|FLAG_SHADOW);

		scene->zMax = 50000.0f;
		scene->zMin = 5.0f;
		maxFrame = scene->dwFramesCount + 1;		
}

void CScene3d::InitializeBlackEnd(IDirect3DDevice8 *pDevice,char cFilename[])
{
		m_pBlackScreen = new CSprite(255,255,255,255);
		m_pBlackScreen->InitializeEx("data\\black.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

		m_bActive = true;	// dane wczytane
		
		scene = new G3D_CScene;
		scene->Initialize( pDevice );
	
		scene->Load(pDevice,cFilename);	
		scene->SetFlags(FLAG_RENDERFLARE|FLAG_SHADOW);

		scene->zMax = 50000.0f;
		scene->zMin = 5.0f;
		maxFrame = scene->dwFramesCount + 1;		
}

void CScene3d::InitializeBlackBlack(IDirect3DDevice8 *pDevice,char cFilename[])
{
		m_pBlackScreen = new CSprite(255,255,255,255);
		m_pBlackScreen->InitializeEx("data\\black.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

		m_bActive = true;	// dane wczytane
		
		scene = new G3D_CScene;
		scene->Initialize( pDevice );
	
		scene->Load(pDevice,cFilename);	
		scene->SetFlags(FLAG_RENDERFLARE|FLAG_SHADOW);

		scene->zMax = 50000.0f;
		scene->zMin = 5.0f;
		maxFrame = scene->dwFramesCount + 1;		
}

void CScene3d::InitializeWhiteWhite(IDirect3DDevice8 *pDevice,char cFilename[])
{
		m_pWhiteScreen = new CSprite(255,255,255,255);
		m_pWhiteScreen->InitializeEx("data\\white.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

		m_bActive = true;	// dane wczytane
		
		scene = new G3D_CScene;
		scene->Initialize( pDevice );
	
		scene->Load(pDevice,cFilename);	
		scene->SetFlags(FLAG_RENDERFLARE|FLAG_SHADOW);

		scene->zMax = 50000.0f;
		scene->zMin = 5.0f;
		maxFrame = scene->dwFramesCount + 1;		
}


void CScene3d::InitializeWhiteBlack(IDirect3DDevice8 *pDevice,char cFilename[])
{
		m_pWhiteScreen = new CSprite(255,255,255,255);
		m_pWhiteScreen->InitializeEx("data\\white.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

		m_pBlackScreen = new CSprite(255,255,255,255);
		m_pBlackScreen->InitializeEx("data\\black.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);


		m_bActive = true;	// dane wczytane
		
		scene = new G3D_CScene;
		scene->Initialize( pDevice );
	
		scene->Load(pDevice,cFilename);	
		scene->SetFlags(FLAG_RENDERFLARE|FLAG_SHADOW);

		scene->zMax = 50000.0f;
		scene->zMin = 5.0f;
		maxFrame = scene->dwFramesCount + 1;		
}

void CScene3d::InitializeBlackWhite(IDirect3DDevice8 *pDevice,char cFilename[])
{
		m_pWhiteScreen = new CSprite(255,255,255,255);
		m_pWhiteScreen->InitializeEx("data\\white.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

		m_pBlackScreen = new CSprite(255,255,255,255);
		m_pBlackScreen->InitializeEx("data\\black.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);


		m_bActive = true;	// dane wczytane
		
		scene = new G3D_CScene;
		scene->Initialize( pDevice );
	
		scene->Load(pDevice,cFilename);	

		scene->zMax = 50000.0f;
		scene->zMin = 5.0f;
		maxFrame = scene->dwFramesCount + 1;		
}

//=== ustawianie aktywnosci - czy dane sa w pamieci

void CScene3d::SetActive(bool bState)
{
	m_bActive = bState;
}

//=== zwraca informacje czy dane sa wczytane

bool CScene3d::bGetActive(void)
{
	return m_bActive;
}

int CScene3d::DrawScene(IDirect3DDevice8 *pDevice, long lTimer)
{

	int iKlatka;

	// sprawdz czy to nie jest scena DYNAMIC

	if (m_bDynamic && !m_bActive)
	{
		m_bActive = true;	// dane wczytane

		scene = new G3D_CScene;
		scene->Initialize( pDevice );
	
		scene->Load(pDevice,m_cFilename);	
		scene->SetFlags(FLAG_RENDERFLARE|FLAG_SHADOW);

		scene->zMax = 50000.0f;
		scene->zMin = 5.0f;
		maxFrame = scene->dwFramesCount + 1;		

		if (m_bBackground) // tlo jest DYNAMIC, musimy doczytac
		{
			m_pBackground->InitializeEx(m_cBackgroundFilename,pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
			D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);	
		}

	}

	if (m_bFogEnable)	// mg�a w��czona
	{
		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_FOGCOLOR, m_uiFogColor);
		pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
		pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&m_fFogStart));
		pDevice->SetRenderState(D3DRS_FOGEND,   *(DWORD *)(&m_fFogEnd));
	}
	else
	{
		pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	}

	// czyszczenie scenki

	if (m_bBackground)
	{
		if (m_pBackground!=NULL) 
		{
//			pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
//				D3DCOLOR_ARGB(m_ucClearA, m_ucClearR, m_ucClearG, m_ucClearB), 1.0f, 0 );
			m_pBackground->Render();	// rysuj tlo
		}
		else
		{
			pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
				D3DCOLOR_ARGB(m_ucClearA, m_ucClearR, m_ucClearG, m_ucClearB), 1.0f, 0 );
		}
	}
	else
	{
		pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0,0,0,0), 1.0f, 0 );
	}

	// dalsze rysowanie


	if (m_bLoop) 
	{
		iKlatka = (int)(lTimer * m_fPlayRate);
		iKlatka = iKlatka % maxFrame;
		scene->RenderFrame( (float) iKlatka);	// petla wiec rysujemy caly czas
/*
		iKlatka = (int)(lTimer * m_fPlayRate)+15;
		iKlatka = iKlatka % maxFrame;
		scene->RenderFrame( (float) iKlatka);	// petla wiec rysujemy caly czas

		iKlatka = (int)(lTimer * m_fPlayRate)+30;
		iKlatka = iKlatka % maxFrame;
		scene->RenderFrame( (float) iKlatka);	// petla wiec rysujemy caly czas
*/
	}
	else
	{
		iKlatka = (int)(lTimer * m_fPlayRate);

		if (iKlatka > maxFrame) 
		{
			scene->RenderFrame(maxFrame); // bez petli, ostatnia klatka rysowana
		}
		else
		{
			scene->RenderFrame(iKlatka*m_fPlayRate); // bez petli, timer rysowany
		}
	}

	if (m_pForeground!=NULL) m_pForeground->Render();

	return 0;
		
}

int CScene3d::DrawSceneOn(IDirect3DDevice8 *pDevice, long lTimer)
{

	int iKlatka;

	if (m_bFogEnable)	// mg�a w��czona
	{
		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_FOGCOLOR, m_uiFogColor);
		pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
		pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&m_fFogStart));
		pDevice->SetRenderState(D3DRS_FOGEND,   *(DWORD *)(&m_fFogEnd));
	}
	else
	{
		pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	}

	if (m_bLoop) 
	{
		iKlatka = (int)(lTimer * m_fPlayRate);
		iKlatka = iKlatka % maxFrame;
		scene->RenderFrame( (float) iKlatka);	// petla wiec rysujemy caly czas

		iKlatka = (int)(lTimer * m_fPlayRate)+100;
		iKlatka = iKlatka % maxFrame;
		scene->RenderFrame( (float) iKlatka);	// petla wiec rysujemy caly czas

		iKlatka = (int)(lTimer * m_fPlayRate)+200;
		iKlatka = iKlatka % maxFrame;
		scene->RenderFrame( (float) iKlatka);	// petla wiec rysujemy caly czas

	}
	else
	{
		if (lTimer > maxFrame) 
		{
			scene->RenderFrame(maxFrame); // bez petli, ostatnia klatka rysowana
		}
		else
		{
			scene->RenderFrame(lTimer*m_fPlayRate); // bez petli, timer rysowany
		}
	}

	return 0;
		
}

int CScene3d::DrawSceneOutBlack(IDirect3DDevice8 *pDevice, long lTimer, long lBlackOutStart)
{
	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	if (m_pBackground!=NULL) m_pBackground->Render();	// rysuj tlo

	scene->RenderFrame( (float)lTimer );

	if (lTimer>lBlackOutStart)
	{
		m_pBlackScreen->SetModulate((unsigned char)(lTimer-lBlackOutStart),255,255,255);
		m_pBlackScreen->Render();

	}

	return 0;
		
}

int CScene3d::DrawSceneOutWhite(IDirect3DDevice8 *pDevice, long lTimer, long lBlackOutStart)
{

	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	if (m_pBackground!=NULL) m_pBackground->Render();	// rysuj tlo

	scene->RenderFrame( (float)lTimer );

	if (lTimer>=lBlackOutStart)
	{
		m_pWhiteScreen->SetModulate((unsigned char)(lTimer-lBlackOutStart),255,255,255);
		m_pWhiteScreen->Render();
	}

	return 0;
		
}

int CScene3d::DrawSceneInWhite(IDirect3DDevice8 *pDevice, long lTimer)
{

	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	if (m_pBackground!=NULL) m_pBackground->Render();	// rysuj tlo

	scene->RenderFrame( (float)lTimer );

	if (lTimer<255)
	{
		m_pWhiteScreen->SetModulate((unsigned char)(255-lTimer),255,255,255);
		m_pWhiteScreen->Render();
	}

	return 0;
}

int CScene3d::DrawSceneInBlack(IDirect3DDevice8 *pDevice, long lTimer)
{

	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	if (m_pBackground!=NULL) m_pBackground->Render();	// rysuj tlo

	scene->RenderFrame( (float)lTimer );

	if (lTimer<255)
	{
		m_pBlackScreen->SetModulate((unsigned char)(255-lTimer),255,255,255);
		m_pBlackScreen->Render();
	}

	return 0;
		
}

int CScene3d::DrawSceneBlackBlack(IDirect3DDevice8 *pDevice, long lTimer, long lBlackOutStart)
{

	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	if (m_pBackground!=NULL) m_pBackground->Render();	// rysuj tlo

	scene->RenderFrame( (float)lTimer );

	if (lTimer<255)
	{
		m_pBlackScreen->SetModulate((unsigned char)(255-lTimer),255,255,255);
		m_pBlackScreen->Render();
	}

	if (lTimer>=lBlackOutStart)
	{
		m_pBlackScreen->SetModulate((unsigned char)(lTimer-lBlackOutStart),255,255,255);
		m_pBlackScreen->Render();
	}

	return 0;	
}

int CScene3d::DrawSceneWhiteWhite(IDirect3DDevice8 *pDevice, long lTimer, long lBlackOutStart)
{

	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	if (m_pBackground!=NULL) m_pBackground->Render();	// rysuj tlo

	scene->RenderFrame( (float)lTimer );

	if (lTimer<255)
	{
		m_pWhiteScreen->SetModulate((unsigned char)(255-lTimer),255,255,255);
		m_pWhiteScreen->Render();
	}

	if (lTimer>=lBlackOutStart)
	{
		m_pWhiteScreen->SetModulate((unsigned char)(lTimer-lBlackOutStart),255,255,255);
		m_pWhiteScreen->Render();
	}

	return 0;	
}

int CScene3d::DrawSceneWhiteBlack(IDirect3DDevice8 *pDevice, long lTimer, long lBlackOutStart)
{

	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	if (m_pBackground!=NULL) m_pBackground->Render();	// rysuj tlo

	scene->RenderFrame( (float)lTimer );

	if (lTimer<255)
	{
		m_pWhiteScreen->SetModulate((unsigned char)(255-lTimer),255,255,255);
		m_pWhiteScreen->Render();
	}

	if (lTimer>=lBlackOutStart)
	{
		m_pBlackScreen->SetModulate((unsigned char)(lTimer-lBlackOutStart),255,255,255);
		m_pBlackScreen->Render();
	}

	return 0;	
}

int CScene3d::DrawSceneBlackWhite(IDirect3DDevice8 *pDevice, long lTimer, long lBlackOutStart)
{

	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	if (m_pBackground!=NULL) m_pBackground->Render();	// rysuj tlo

	scene->RenderFrame( (float)lTimer );

	if (lTimer<255)
	{
		m_pBlackScreen->SetModulate((unsigned char)(255-lTimer),255,255,255);
		m_pBlackScreen->Render();
	}

	if (lTimer>=lBlackOutStart)
	{
		m_pWhiteScreen->SetModulate((unsigned char)(lTimer-lBlackOutStart),255,255,255);
		m_pWhiteScreen->Render();
	}

	return 0;	
}


bool CScene3d::bGetFogEnable(void)
{
	return m_bFogEnable;
}

void CScene3d::SetFog(bool bState)
{
	m_bFogEnable=bState;
}

float CScene3d::fGetFogStart(void)
{
	return m_fFogStart;
}

void CScene3d::SetFogStart(float fFogStart)
{
	m_fFogStart=fFogStart;
}

float CScene3d::fGetFogEnd(void)
{
	return m_fFogEnd;
}

void CScene3d::SetFogEnd(float fFogEnd)
{
	m_fFogEnd=fFogEnd;
}

unsigned int CScene3d::uiGetFogColor(void)
{
	return m_uiFogColor;
}

void CScene3d::SetFogColor(unsigned int uiFogColor)
{
	m_uiFogColor=uiFogColor;
}

void CScene3d::UpOnly(char str[])
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

//=== ustawianie/pobieranie znacznika dynamicznosci

void CScene3d::SetDynamic(bool bState)
{
	m_bDynamic = bState;
}

bool CScene3d::bGetDynamic(void)
{
	return m_bDynamic;
}
