
// kabzdle

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <d3d8.h>
#include <d3dx8.h>
#include <dmusicc.h>
#include <dmusici.h>

#include <Fox.h>

#include "Resource.h"

#include "Ball.h"
#include "Player.h"

//=== zmienne dla directx

IDirect3D8			*pDirect3D;		// handler
IDirect3DDevice8	*pDevice;		// urzadzenie

HRESULT				hr;				// wynik operacji

HWND				hWnd;			// dla okna
HINSTANCE			hInstance;

bool				bFullScreen;	// czy pelny ekran ? 

//=== to dla myszki 

bool				leftButton = false;		// przyciski myszki
bool				rightButton = false;
bool				centerButton = false;

float				mouseX;			// wspolrzedne myszy
float				mouseY;

//=== aktualny katalog

char CurrentDirectory[200]		= {0,};	

//=== systemy plikow

CFileSystem			*pMouseFile;

//=== dla timera

int					g_FrameCount		= 0;
int					g_StartFrameCount	= 0;
DWORD				g_StartTime			= timeGetTime();
DWORD				g_EndTime			= g_StartTime;
int					g_FrameRate			= 0;

//=== dla systemu dzwiekowego

CAudio				*pAudio;

//=== sample

CSound				*pBounce;

//=== czcionki

CFont				*pFont;			// jakas czcionka

//=== sprite

CSprite				*pBubble;		// babelek ;>
CSprite				*pBackground;	// tlo

CSprite				*pLewaBramka;		// bramki
CSprite				*pPrawaBramka;

CSprite				*pGoll;

CSprite				*pCienPilki;	// doslownie
CSprite				*pCienZawodnika;	// tutaj tak samo

int					iLicznik;

long				h1,h2,h3,h4;	// do petli

float				f1,f2,f3;

Player				*pGracz1;
Player				*pGracz2;

bool				bJestBramka;	// czy pilka w bramce
int					iIleWBramce;	// ile czasu lezy w pilka w bramce

//=== pilka

Ball				*pPilka;


//=== pomocnicza, inicjalizuje direct3d i ustawia rozne dodatki

bool Direct3DInit()
{

	pDirect3D = Direct3DCreate8(D3D_SDK_VERSION);

	if (pDirect3D==NULL) 
	{
		MessageBox(0,"B��d inicjalizacji DirectX 8.1 !","B��d!",MB_OK);
		return false;
	}

	// ustaw w odpowiedni sposob tryb sprawdzajac czy wyswietlamy w oknie czy
	// na calym ekranie

	D3DDISPLAYMODE displayMode;

	if (bFullScreen==false)
	{
		hr = pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);
		
		if (FAILED(hr)) 
		{
			MessageBox(0,"Nie mo�na pobra� informacji o aktualnym trybie DirectX","B��d!",MB_OK);
			return false;
		}
	}
	else
	{
		displayMode.Width = 800;				//iWidth;
		displayMode.Height = 600;				//iHeight;
		displayMode.RefreshRate = 0; 
		displayMode.Format = D3DFMT_R5G6B5;		// tu mozna zmienic
	}

	// ustaw/zapamietaj aktualne parametry wyswietlania

	D3DPRESENT_PARAMETERS presentParameters;

	memset(&presentParameters, 0, sizeof(D3DPRESENT_PARAMETERS));

	if (bFullScreen==false)
	{
		presentParameters.Windowed = TRUE;
	}
	else
	{
		presentParameters.Windowed = FALSE;
		presentParameters.BackBufferWidth = displayMode.Width;
		presentParameters.BackBufferHeight = displayMode.Height;
	}

	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = displayMode.Format;

	// stworz urzadzenie

	hr=pDirect3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                  &presentParameters, &pDevice ); 

	if (FAILED(hr))	
	{
		MessageBox(0,"Nie mo�na stworzy� urz�dzenia DirectX!","B��d!",MB_OK);		
		return false;
	}

	SetCursor(NULL);					// ukryj kursor myszy, rysujemy wlasny
	pDevice->ShowCursor(FALSE);			// przeslij do urzadzenia
	
	// ustaw kursor myszy na srodku ekranu

	pDevice->SetCursorPosition(400,300,D3DCURSOR_IMMEDIATE_UPDATE );	

	// ustaw macierze 

	D3DXMATRIX mat;

	// tutaj lepiej ustawic bez rzutowania typu (bez float)

	D3DXMatrixPerspectiveFovLH(&mat, D3DX_PI/4, (float)800/600,	1.0, 100.0);
	
	pDevice->SetTransform(D3DTS_PROJECTION, &(D3DMATRIX)mat);

	D3DXMatrixIdentity(&mat);

	// ustaw transformacje

	pDevice->SetTransform(D3DTS_WORLD, &(D3DMATRIX)mat);
	pDevice->SetTransform(D3DTS_VIEW, &(D3DMATRIX)mat);

    pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );	// backface culling off
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );			// swiatlo
	
	// blending
	
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// alpha channel
	
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	// macierz widoku

	D3DXMatrixTranslation(&mat, 0, 0, 4/3);
	pDevice->SetTransform(D3DTS_VIEW, &(D3DMATRIX)mat);

	// dodatkowe obiekty - powinno byc jak najmniej

	pFont = new CFont();
	pFont->Initialize(pDevice,(HFONT)GetStockObject(SYSTEM_FONT),D3DCOLOR_XRGB(255,255,255));

	pMouseFile = new CFileSystem("mouse.fox");
	pMouseFile->Load("myszka.tga");

	pBubble = new CSprite(255,255,255,255);
	pBubble->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("myszka.tga"),pDevice);

	pBackground = new CSprite(255,255,255,255);
	pMouseFile->Load("boisko.bmp");
	pBackground->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("boisko.bmp"),pDevice);

	pLewaBramka = new CSprite(255,255,255,255);
	pMouseFile->Load("lewa.tga");
	pLewaBramka->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("lewa.tga"),pDevice);

	pPrawaBramka = new CSprite(255,255,255,255);
	pMouseFile->Load("prawa.tga");
	pPrawaBramka->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("prawa.tga"),pDevice);

	pGoll = new CSprite(255,255,255,255);
	pMouseFile->Load("goll.tga");
	pGoll->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("goll.tga"),pDevice);

	// wczytaj obiekt graczy

	pGracz1 = new Player(368+100,268);

	pMouseFile->Load("a1.tga");
	pGracz1->m_pFrames[0]->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("a1.tga"),pDevice);

	pMouseFile->Load("a2.tga");
	pGracz1->m_pFrames[1]->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("a2.tga"),pDevice);

	pMouseFile->Load("a3.tga");
	pGracz1->m_pFrames[2]->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("a3.tga"),pDevice);

	pMouseFile->Load("a4.tga");
	pGracz1->m_pFrames[3]->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("a4.tga"),pDevice);

	// drugi gracz

	pGracz2 = new Player(368-100,268);

	pMouseFile->Load("b1.tga");
	pGracz2->m_pFrames[0]->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("b1.tga"),pDevice);

	pMouseFile->Load("b2.tga");
	pGracz2->m_pFrames[1]->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("b2.tga"),pDevice);

	pMouseFile->Load("b3.tga");
	pGracz2->m_pFrames[2]->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("b3.tga"),pDevice);

	pMouseFile->Load("b4.tga");
	pGracz2->m_pFrames[3]->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("b4.tga"),pDevice);


	// wczytaj obiekt pi�ki

	pPilka = new Ball();

	pMouseFile->Load("pilka1.tga");
	pPilka->m_pFrames[0]->InitializeTGAinMemory((unsigned int*) pMouseFile->pDataBuffer,
		pMouseFile->Search("pilka1.tga"),pDevice);

	pMouseFile->Load("pilka2.tga");
	pPilka->m_pFrames[1]->InitializeTGAinMemory((unsigned int*) pMouseFile->pDataBuffer,
		pMouseFile->Search("pilka2.tga"), pDevice);

	pMouseFile->Load("pilka3.tga");
	pPilka->m_pFrames[2]->InitializeTGAinMemory((unsigned int*) pMouseFile->pDataBuffer,
		pMouseFile->Search("pilka3.tga"), pDevice);

	pMouseFile->Load("pilka4.tga");
	pPilka->m_pFrames[3]->InitializeTGAinMemory((unsigned int*) pMouseFile->pDataBuffer,
		pMouseFile->Search("pilka4.tga"), pDevice);

	// wczytaj cien pilki

	pCienPilki = new CSprite(255,255,255,255);
	pMouseFile->Load("pc.tga");
	pCienPilki->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("pc.tga"),pDevice);

	// cien zawodnika

	pCienZawodnika = new CSprite(255,255,255,255);
	pMouseFile->Load("zc.tga");
	pCienZawodnika->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("zc.tga"),pDevice);

	return true;
}

//=== aktualizuj scenke, to ma byc wymienione i podzielone na czesci

void UpdateScene()
{
	char	str[20];	// tymczasowy


	pBackground->Render();

	// player 1 biegnie

	if (pGracz1->m_fAddX>2.0f)	// nie za szybko ? 
	{
		pGracz1->m_fAddX=2.0f;
	}

	if (pGracz1->m_fAddX<-2.0f)
	{
		pGracz1->m_fAddX=-2.0f;
	}

	if (pGracz1->m_fAddY>2.0f)
	{
		pGracz1->m_fAddY=2.0f;
	}

	if (pGracz1->m_fAddY<-2.0f)
	{
		pGracz1->m_fAddY=-2.0f;
	}

	pGracz1->m_fX+=pGracz1->m_fAddX;
	pGracz1->m_fY+=pGracz1->m_fAddY;


	// odbicia od scian

	if (pGracz1->m_fX>688 && pGracz1->m_fAddX>0)	// prawa
	{
		pGracz1->m_fX=688;
	}
	
	if (pGracz1->m_fX<50 && pGracz1->m_fAddX<0 )		// lewa
	{
		pGracz1->m_fX=50;
	}

	if (pGracz1->m_fY<-16 && pGracz1->m_fAddY<0)		// gora
	{
		pGracz1->m_fY=-16;
	}

	if (pGracz1->m_fY>440 && pGracz1->m_fAddY>0)
	{
		pGracz1->m_fY=440;
	}


	// tarcie poziome i pionowe (biegnie pod gorke, albo z gorki)

	if (pGracz1->m_fAddY>0)	pGracz1->m_fAddY-=0.1f;
	if (pGracz1->m_fAddY<0) pGracz1->m_fAddY+=0.1f;
	if (pGracz1->m_fAddX>0)	pGracz1->m_fAddX-=0.1f;
	if (pGracz1->m_fAddX<0) pGracz1->m_fAddX+=0.1f;

	if (pGracz1->m_fAddY>0&&pGracz1->m_fAddY<0.1f) pGracz1->m_fAddY=0;
	if (pGracz1->m_fAddY<0&&pGracz1->m_fAddY>0.1f) pGracz1->m_fAddY=0;
	if (pGracz1->m_fAddX>0&&pGracz1->m_fAddX<0.1f) pGracz1->m_fAddX=0;
	if (pGracz1->m_fAddX<0&&pGracz1->m_fAddX>0.1f) pGracz1->m_fAddX=0;
		


	// player 2 biegnie

	if (pGracz2->m_fAddX>2.0f)	// nie za szybko ? 
	{
		pGracz2->m_fAddX=2.0f;
	}

	if (pGracz2->m_fAddX<-2.0f)
	{
		pGracz2->m_fAddX=-2.0f;
	}

	if (pGracz2->m_fAddY>2.0f)
	{
		pGracz2->m_fAddY=2.0f;
	}

	if (pGracz2->m_fAddY<-2.0f)
	{
		pGracz2->m_fAddY=-2.0f;
	}

	// nie za szybko ? 
/*
	if (pGracz2->m_fAddX>2.0f)
	{
		pGracz2->m_fAddX=2.0f;
	}

	if (pGracz2->m_fAddX<-2.0f)
	{
		pGracz2->m_fAddX=-2.0f;
	}

	if (pGracz2->m_fAddY>2.0f)
	{
		pGracz2->m_fAddY=2.0f;
	}

	if (pGracz2->m_fAddY<-2.0f)
	{
		pGracz2->m_fAddY=-2.0f;
	}
*/
	pGracz2->m_fX+=pGracz2->m_fAddX;
	pGracz2->m_fY+=pGracz2->m_fAddY;

	// odbicia od scian

	if (pGracz2->m_fX>688 && pGracz2->m_fAddX>0)	// prawa
	{
		pGracz2->m_fX=688;		
	}
	
	if (pGracz2->m_fX<50&&pGracz2->m_fAddX<0 )		// lewa
	{
		pGracz2->m_fX=50;
	}

	if (pGracz2->m_fY<-16 && pGracz2->m_fAddY<0)		// gora
	{
		pGracz2->m_fY=-16;
	}

	if (pGracz2->m_fY>440 && pGracz2->m_fAddY>0)
	{
		pGracz2->m_fY=440;
	}

	// tarcie poziome i pionowe (biegnie pod gorke, albo z gorki)

	if (pGracz2->m_fAddX>0) pGracz2->m_fAddX-=0.1f;
	if (pGracz2->m_fAddX<0) pGracz2->m_fAddX+=0.1f;
	
	if (pGracz2->m_fAddY>0)	pGracz2->m_fAddY-=0.1f;
	if (pGracz2->m_fAddY<0) pGracz2->m_fAddY+=0.1f;

	if (pGracz2->m_fAddY>0&&pGracz2->m_fAddY<0.1f) pGracz2->m_fAddY=0;
	if (pGracz2->m_fAddY<0&&pGracz2->m_fAddY>0.1f) pGracz2->m_fAddY=0;
	if (pGracz2->m_fAddX>0&&pGracz2->m_fAddX<0.1f) pGracz2->m_fAddX=0;
	if (pGracz2->m_fAddX<0&&pGracz2->m_fAddX>0.1f) pGracz2->m_fAddX=0;


	//=== pilka, nie ma ograniczen predkosci dla pilki

	pPilka->m_ucCurrentFrame=((int)((pPilka->m_fBallAddX+pPilka->m_fBallAddY)));
	pPilka->m_ucCurrentFrame%=3;

	pPilka->m_fBallX+=pPilka->m_fBallAddX;
	pPilka->m_fBallY+=pPilka->m_fBallAddY;

	// odbicia od scian

	if (pPilka->m_fBallY<200 || pPilka->m_fBallY>400)
	{
		if (pPilka->m_fBallX>710 && pPilka->m_fBallAddX>0)	// prawa
		{
			pPilka->m_fBallAddX = -pPilka->m_fBallAddX+(pPilka->m_fBallAddX*0.3f);
		}
	
		if (pPilka->m_fBallX<66&&pPilka->m_fBallAddX<0 )		// lewa
		{
			pPilka->m_fBallAddX = -pPilka->m_fBallAddX+(pPilka->m_fBallAddX*0.3f);
		}
	}

	if (pPilka->m_fBallY>200 && pPilka->m_fBallY<400)
	{
		if (pPilka->m_fBallX>764 && pPilka->m_fBallAddX>0)	// prawa
		{
			pPilka->m_fBallAddX = -pPilka->m_fBallAddX+(pPilka->m_fBallAddX*0.3f);
		}
	
		if (pPilka->m_fBallX<12&&pPilka->m_fBallAddX<0 )		// lewa
		{
			pPilka->m_fBallAddX = -pPilka->m_fBallAddX+(pPilka->m_fBallAddX*0.3f);
		}
	
		// odbicie gora i dol wewnatrz bramki

		if (pPilka->m_fBallX<66 || pPilka->m_fBallX>710)
		{

			// wolniej x2 + golll!

			pPilka->m_fBallAddX=pPilka->m_fBallAddX*0.9f;
			pPilka->m_fBallAddY=pPilka->m_fBallAddY*0.9f;
			
				if (pPilka->m_fBallY<205 && pPilka->m_fBallAddY<0)		// gora
				{
					pPilka->m_fBallAddY = -pPilka->m_fBallAddY+(pPilka->m_fBallAddY*0.3f);
				}

				if (pPilka->m_fBallY>390 && pPilka->m_fBallAddY>0)		// dol
				{
					pPilka->m_fBallAddY = -pPilka->m_fBallAddY+(pPilka->m_fBallAddY*0.3f);
				}

			if (pPilka->m_fBallX<66 && bJestBramka==false)
			{
				pGracz2->m_ucPunkty++;
				bJestBramka=true;
			}

			if (pPilka->m_fBallX>710 && bJestBramka==false)
			{
				pGracz1->m_ucPunkty++;
				bJestBramka=true;
			}
		}
	}


	if (pPilka->m_fBallY<36 && pPilka->m_fBallAddY<0)		// gora
	{
		pPilka->m_fBallAddY = -pPilka->m_fBallAddY+(pPilka->m_fBallAddY*0.3f);
	}

	if (pPilka->m_fBallY>536 && pPilka->m_fBallAddY>0)		// dol
	{
		pPilka->m_fBallAddY = -pPilka->m_fBallAddY+(pPilka->m_fBallAddY*0.3f);
	}

	// GRACZ  kopnal PILKE

	if ( (pPilka->m_fBallX-pGracz1->m_fX-36)<32 && (pPilka->m_fBallX-pGracz1->m_fX-36)>-32 &&
		 (pPilka->m_fBallY-pGracz1->m_fY-84)<32 && (pPilka->m_fBallY-pGracz1->m_fY-84)>-32 )
	{
		if (GetAsyncKeyState(VK_RSHIFT)!=0)
		{
			pPilka->m_fBallAddX = 1.5f*pGracz1->m_fAddX+(pPilka->m_fBallAddX*0.3f);
			pPilka->m_fBallAddY = 1.5f*pGracz1->m_fAddY+(pPilka->m_fBallAddY*0.3f);
		}
		else
		{
			pPilka->m_fBallAddX = pGracz1->m_fAddX+(pPilka->m_fBallAddX*0.3f);
			pPilka->m_fBallAddY = pGracz1->m_fAddY+(pPilka->m_fBallAddY*0.3f);
		}
	}


	if ( (pPilka->m_fBallX-pGracz2->m_fX-36)<32 && (pPilka->m_fBallX-pGracz2->m_fX-36)>-32 &&
		 (pPilka->m_fBallY-pGracz2->m_fY-84)<32 && (pPilka->m_fBallY-pGracz2->m_fY-84)>-32 )
	{
		if (GetAsyncKeyState(VK_LSHIFT)!=0)
		{
			pPilka->m_fBallAddX = 1.5f*pGracz2->m_fAddX+(pPilka->m_fBallAddX*0.3f);
			pPilka->m_fBallAddY = 1.5f*pGracz2->m_fAddY+(pPilka->m_fBallAddY*0.3f);
		}
		else
		{
			pPilka->m_fBallAddX = pGracz2->m_fAddX+(pPilka->m_fBallAddX*0.3f);
			pPilka->m_fBallAddY = pGracz2->m_fAddY+(pPilka->m_fBallAddY*0.3f);
		}
	}

	// tarcie poziome i pionowe, pilka leci pod gorke, albo toczy sie z gorki

	if (pPilka->m_fBallAddX>0) pPilka->m_fBallAddX-=0.01f;
	if (pPilka->m_fBallAddX<0) pPilka->m_fBallAddX+=0.01f;
	
	if (pPilka->m_fBallAddY>0) pPilka->m_fBallAddY-=0.01f;
	if (pPilka->m_fBallAddY<0) pPilka->m_fBallAddY+=0.01f;

	// przesuniecie na ekranie

	pPilka->m_pFrames[pPilka->m_ucCurrentFrame]->SetTranslation(pPilka->m_fBallX, pPilka->m_fBallY);
	
	// obrot

	f1=1+(pPilka->m_fBallAddX+pPilka->m_fBallAddY)/10;

	if (f1<0)
	{
		f1 = -1 * f1;
	}

	if (f1<1) 
	{
		f1 = 1;
	}

	if (f1>2)
	{
		f1 = 2;
	}

//	pBall->SetRotationCenter((64*f1)/2,(64*f1)/2);
	pPilka->m_pFrames[pPilka->m_ucCurrentFrame]->SetRotationCenter(12,13);
	pPilka->m_pFrames[pPilka->m_ucCurrentFrame]->SetRotation(pPilka->m_fBallAddX*pPilka->m_fBallAddY*4);	

	// skala
	

//	pPilka->m_pFrames[pPilka->m_ucCurrentFrame]->SetScale(f1,f1);

	// jeszcze raz sprawdzenie zderzenia graczy

	if ( (pGracz1->m_fX-pGracz2->m_fX)<32 && (pGracz1->m_fX-pGracz2->m_fX)>-32 &&
		 (pGracz1->m_fY-pGracz2->m_fY)<32 && (pGracz1->m_fY-pGracz2->m_fY)>-32 )
	{

		pGracz1->m_fAddX=0; pGracz1->m_fAddY=0;
		pGracz2->m_fAddX=0; pGracz2->m_fAddY=0;
	}

	// przesuniecie na ekranie

	pGracz2->m_pFrames[(pGracz2->m_ucCurrentFrame>>2)%4]->SetTranslation(pGracz2->m_fX, pGracz2->m_fY);
	
	// obrot

	pGracz2->m_pFrames[(pGracz2->m_ucCurrentFrame>>2)%4]->SetRotationCenter(36,84);
	pGracz2->m_pFrames[(pGracz2->m_ucCurrentFrame>>2)%4]->SetRotation(pGracz2->m_fAngle);

	// przesuniecie na ekranie

	pGracz1->m_pFrames[(pGracz1->m_ucCurrentFrame>>2)%4]->SetTranslation(pGracz1->m_fX, pGracz1->m_fY);
	
	// obrot

	pGracz1->m_pFrames[(pGracz1->m_ucCurrentFrame>>2)%4]->SetRotationCenter(36,84);
	pGracz1->m_pFrames[(pGracz1->m_ucCurrentFrame>>2)%4]->SetRotation(pGracz1->m_fAngle);

	// rysuj

	pCienPilki->SetTranslation(pPilka->m_fBallX-4,pPilka->m_fBallY);
	pCienPilki->Render();

	pPilka->m_pFrames[pPilka->m_ucCurrentFrame]->Render();

	pCienZawodnika->SetTranslation(pGracz1->m_fX-8, pGracz1->m_fY);
	pCienZawodnika->Render();

	pCienZawodnika->SetTranslation(pGracz2->m_fX-8, pGracz2->m_fY);
	pCienZawodnika->Render();
	
	pGracz1->m_pFrames[(pGracz1->m_ucCurrentFrame>>2)%4]->Render();
	pGracz2->m_pFrames[(pGracz2->m_ucCurrentFrame>>2)%4]->Render();

	//=== koniec pilka, teraz asynchroniczne sprawdzenie klawiatury

	// player1 

	if (GetAsyncKeyState(VK_UP)!=0)	// biegnie przed siebie ? 
	{
							// zapamietaj (bedzie potrzebne przy kopnieciu pilki)

					pGracz1->m_fLastAddX = pGracz1->m_fAddX;
					pGracz1->m_fLastAddY = pGracz1->m_fAddY;

					pGracz1->m_ucCurrentFrame++;

					// lewo 

					if (pGracz1->m_fAngle>=0 && pGracz1->m_fAngle<1.5f)
					{
						pGracz1->m_fAddX-=pGracz1->m_fAngle;
						pGracz1->m_fAddY-=(1.5f-pGracz1->m_fAngle);
					}

					if (pGracz1->m_fAngle>=1.5f && pGracz1->m_fAngle<3.0f)
					{
						pGracz1->m_fAddX-=(3.0f-pGracz1->m_fAngle);
						pGracz1->m_fAddY+=pGracz1->m_fAngle-1.5f;
					}

					if (pGracz1->m_fAngle>=3.0f && pGracz1->m_fAngle<4.7f)
					{
						pGracz1->m_fAddX+=pGracz1->m_fAngle-3.0f;
						pGracz1->m_fAddY+=4.5f-pGracz1->m_fAngle;
					}

					if (pGracz1->m_fAngle>=4.7)
					{
						pGracz1->m_fAddX+=6.3f-pGracz1->m_fAngle;
						pGracz1->m_fAddY-=6.3f-pGracz1->m_fAngle;
					}

					// prawo

					if (pGracz1->m_fAngle<0 && pGracz1->m_fAngle>-1.6f)
					{
						pGracz1->m_fAddX-=pGracz1->m_fAngle;
						pGracz1->m_fAddY-=(1.5f-pGracz1->m_fAngle);
					}

					if (pGracz1->m_fAngle<=-1.6f && pGracz1->m_fAngle>-3.1f)
					{
						pGracz1->m_fAddX+=(3.1f+pGracz1->m_fAngle);
						pGracz1->m_fAddY-=pGracz1->m_fAngle+1.6f;
					}

					if (pGracz1->m_fAngle<=-3.1f && pGracz1->m_fAngle>-4.7f)
					{
						pGracz1->m_fAddX+=pGracz1->m_fAngle+3.0f;
						pGracz1->m_fAddY+=4.5f-pGracz1->m_fAngle;
					}

					if (pGracz1->m_fAngle<=-4.7)
					{
						pGracz1->m_fAddX-=6.3f-pGracz1->m_fAngle;
						pGracz1->m_fAddY-=6.3f-pGracz1->m_fAngle;
					}
		
	}

	if (GetAsyncKeyState(VK_LEFT)!=0)	// player1 odwraca sie w lewo
	{
					pGracz1->m_fAngle+=0.1f;
					
					if (pGracz1->m_fAngle>6.2)
					{
						pGracz1->m_fAngle=0;
					}
	}

	
	if (GetAsyncKeyState(VK_RIGHT)!=0)	// player1 odwraca sie w prawo
	{
					pGracz1->m_fAngle-=0.1f;

					if (pGracz1->m_fAngle<-6.2)
					{
						pGracz1->m_fAngle=0;
					}
	}


	if (GetAsyncKeyState('T')!=0)	// player 2 biegnie do przodu
	{

					// zapamietaj (bedzie potrzebne przy kopnieciu pilki)

					pGracz2->m_fLastAddX = pGracz2->m_fAddX;
					pGracz2->m_fLastAddY = pGracz2->m_fAddY;

					pGracz2->m_ucCurrentFrame++;

					// lewo 

					if (pGracz2->m_fAngle>=0 && pGracz2->m_fAngle<1.5f)
					{
						pGracz2->m_fAddX-=pGracz2->m_fAngle;
						pGracz2->m_fAddY-=(1.5f-pGracz2->m_fAngle);
					}

					if (pGracz2->m_fAngle>=1.5f && pGracz2->m_fAngle<3.0f)
					{
						pGracz2->m_fAddX-=(3.0f-pGracz2->m_fAngle);
						pGracz2->m_fAddY+=pGracz2->m_fAngle-1.5f;
					}

					if (pGracz2->m_fAngle>=3.0f && pGracz2->m_fAngle<4.7f)
					{
						pGracz2->m_fAddX+=pGracz2->m_fAngle-3.0f;
						pGracz2->m_fAddY+=4.5f-pGracz2->m_fAngle;
					}

					if (pGracz2->m_fAngle>=4.7)
					{
						pGracz2->m_fAddX+=6.3f-pGracz2->m_fAngle;
						pGracz2->m_fAddY-=6.3f-pGracz2->m_fAngle;
					}

					// prawo

					if (pGracz2->m_fAngle<0 && pGracz2->m_fAngle>-1.6f)
					{
						pGracz2->m_fAddX-=pGracz2->m_fAngle;
						pGracz2->m_fAddY-=(1.5f-pGracz2->m_fAngle);
					}

					if (pGracz2->m_fAngle<=-1.6f && pGracz2->m_fAngle>-3.1f)
					{
						pGracz2->m_fAddX+=(3.1f+pGracz2->m_fAngle);
						pGracz2->m_fAddY-=pGracz2->m_fAngle+1.6f;
					}

					if (pGracz2->m_fAngle<=-3.1f && pGracz2->m_fAngle>-4.7f)
					{
						pGracz2->m_fAddX+=pGracz2->m_fAngle+3.0f;
						pGracz2->m_fAddY+=4.5f-pGracz2->m_fAngle;
					}

					if (pGracz2->m_fAngle<=-4.7)
					{
						pGracz2->m_fAddX-=6.3f-pGracz2->m_fAngle;
						pGracz2->m_fAddY-=6.3f-pGracz2->m_fAngle;
					}
	}					

	if (GetAsyncKeyState('F')!=0)	// odwraca sie w lewo
	{
					
					pGracz2->m_fAngle+=0.1f;
					
					if (pGracz2->m_fAngle>6.2)
					{
						pGracz2->m_fAngle=0;
					}

	}					

	if (GetAsyncKeyState('H')!=0)
	{				
		
					pGracz2->m_fAngle-=0.1f;

					if (pGracz2->m_fAngle<-6.2)
					{
						pGracz2->m_fAngle=0;
					}
	}

	// zderzyli sie idioci

	if ( ((pGracz1->m_fX+32)-(pGracz2->m_fX+32))<64 && ((pGracz1->m_fX+32)-(pGracz2->m_fX+32))>-64 &&
		 ((pGracz1->m_fY+103)-(pGracz2->m_fY+103))<32 && ((pGracz1->m_fY+103)-(pGracz2->m_fY+103))>-32)
	{
		pGracz1->m_fAddX*=-2; pGracz1->m_fAddY*=-2;
		pGracz2->m_fAddX*=-2; pGracz2->m_fAddY*=-2;
	}



	// bramki

	pLewaBramka->SetTranslation(-92,162);
	pLewaBramka->Render();

	pPrawaBramka->SetTranslation(638,162);
	pPrawaBramka->Render();
	
	//		pBramki->Render();


	// myszka i reszta 

	pBubble->SetRotationCenter(0,64);
	
	if (rightButton) pBubble->AddRotation(0.01f);

	leftButton ? pBubble->SetTranslation(mouseX+16,mouseY+16) : pBubble->SetTranslation(mouseX,mouseY);

//	pBubble->SetTranslation(mouseX,mouseY) ? !leftButton : leftButton;

	//pBubble->SetTranslation(mouseX,mouseY);
//	pBubble->Render();

	
	// jezeli gol to napisz

	if (bJestBramka)
	{
		pGoll->SetScale(2,2);
		pGoll->SetTranslation(400-256,300-256);
		pGoll->Render();
	}

	_itoa(pGracz1->m_ucPunkty,str,10);
	pFont->OutputText(str,368,10);

	pFont->OutputText(":",400,10);

	_itoa(pGracz2->m_ucPunkty,str,10);
	pFont->OutputText(str,432,10);

	// debug
/*

	pFont->OutputText("FPS: ",10,10);
	_itoa(g_FrameRate,str,10);		// fps
	pFont->OutputText(str,50,10);

	pFont->OutputText("Player1 Angle: ",10,30);
	_itoa(pGracz1->m_fAngle*10,str,10);
	pFont->OutputText(str,120,30);

	pFont->OutputText("Player1 X: ",10,50);
	_itoa(pGracz1->m_fX,str,10);
	pFont->OutputText(str,100,50);

	pFont->OutputText("Y: ",140,50);
	_itoa(pGracz1->m_fY,str,10);
	pFont->OutputText(str,160,50);

	pFont->OutputText("LX: ", 190,50);
	_itoa(pGracz1->m_fLastAddX*100,str,10);
	pFont->OutputText(str,220,50);

	pFont->OutputText("LY: ",250,50);
	_itoa(pGracz1->m_fLastAddY*100,str,10);
	pFont->OutputText(str,280,50);

	_itoa(GetAsyncKeyState(VK_RSHIFT),str,10);
	pFont->OutputText(str,10,170);

	pFont->OutputText("Player2 Angle: ",10,130);
	_itoa(pGracz2->m_fAngle*10,str,10);
	pFont->OutputText(str,120,130);

	pFont->OutputText("Player2 X: ",10,150);
	_itoa(pGracz2->m_fX,str,10);
	pFont->OutputText(str,100,150);

	pFont->OutputText("Y: ",140,150);
	_itoa(pGracz2->m_fY,str,10);
	pFont->OutputText(str,160,150);

	pFont->OutputText("LX: ", 190,150);
	_itoa(pGracz2->m_fLastAddX*100,str,10);
	pFont->OutputText(str,220,150);

	pFont->OutputText("LY: ",250,150);
	_itoa(pGracz2->m_fLastAddY*100,str,10);
	pFont->OutputText(str,280,150);

	_itoa(GetAsyncKeyState(VK_LSHIFT),str,10);
	pFont->OutputText(str,10,190);

	_itoa(((pGracz1->m_fX+32)-(pGracz2->m_fX+32)),str,10);
	pFont->OutputText(str,10,500);
		
	_itoa(((pGracz1->m_fY+103)-(pGracz2->m_fY+103)),str,10);
	pFont->OutputText(str,10,550);
*/
}

//=== rysuj scenke, tylko przygotowuje calosc, a potem odwoluje sie do odpowiedniej
//=== funkcji aktualizujacej w zaleznosci od CScene

void DrawScene()
{
//	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 );
	
	pDevice->BeginScene();
	
	
	UpdateScene();	// to zamienic na game,background itepe
	
	g_EndTime = timeGetTime();

	if (g_EndTime - g_StartTime > 1000)
	{
		g_FrameRate = (g_FrameCount - g_StartFrameCount) * 1000 / (g_EndTime - g_StartTime);
		g_StartTime = g_EndTime;
		g_StartFrameCount = g_FrameCount;
	}

	g_FrameCount++;	
	
	pDevice->EndScene();	//pDirect3D->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);	//pDirect3D->Present();
}

//=== obsluga okna

LRESULT CALLBACK BasicWindowProc(HWND wpHWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch(msg)
	{	
		case WM_DESTROY: 
		{ 
			PostQuitMessage(0);
			return 0;
		} break;

		case WM_KEYDOWN:
			switch( wParam ) 
			{
				case VK_ESCAPE:
					PostQuitMessage( 0 );
					break;
				
				case VK_SPACE:
					bJestBramka=false;

					pGracz1->m_fX=368+100; pGracz1->m_fY=268;
					pGracz2->m_fX=368-100; pGracz2->m_fY=268;
					
					pGracz1->m_fAngle=0;
					pGracz2->m_fAngle=0;

					pGracz1->m_fAddX=0; pGracz1->m_fAddY=0;
					pGracz2->m_fAddX=0; pGracz2->m_fAddY=0;
						
					pPilka->m_fBallX=400-32; 
					pPilka->m_fBallY=300-32;
					
					pPilka->m_fBallAddX=0;
					pPilka->m_fBallAddY=0;

					break;
			}
			break;

		// myszka

		case WM_MOUSEMOVE:
			mouseX = LOWORD(lParam);
			mouseY = HIWORD(lParam);
			break;

		case WM_LBUTTONDOWN:
			leftButton = true;
			pBounce->Play(pAudio,(-400+mouseX)/200,0,0);
			 break;

		case WM_LBUTTONUP:
			leftButton = false; 
			break;

		case WM_RBUTTONDOWN:
			rightButton = true;
			break;

		case WM_RBUTTONUP:
			rightButton = false;
			 break;		


		case WM_SETCURSOR:
            // wylacz kursor
            SetCursor(NULL);
            return TRUE;


		default:break; 
	} 

	return DefWindowProc(wpHWnd, msg, wParam, lParam);
}

//######################
//### start programu ###
//######################

int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					LPSTR lpCmdLine, int nCmdShow) 
{

	// pobierz aktualny katalog
	
	GetCurrentDirectory( sizeof(CurrentDirectory), CurrentDirectory);

	// zapytaj o pelny ekran ? 

	if (MessageBox(NULL, "Reboot?", "Reboot?", MB_YESNO)==IDYES)
		bFullScreen=true;
	else 
		bFullScreen=false;

	// inicjalizacja okienka

		WNDCLASSEX winClass;

	// ustaw i zarejestruj klase okna
	
	winClass.cbSize         = sizeof(WNDCLASSEX); 
	winClass.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc	= BasicWindowProc; // nasza statyczna funkcja
	winClass.cbClsExtra		= 0;
	winClass.cbWndExtra		= 0; 
	winClass.hInstance		= hInstance; 
	winClass.hIcon			= ::LoadIcon(hInstance, MAKEINTRESOURCE(KOZA_ICON));	// NULL zamiast icon
	winClass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
	winClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH); 
	winClass.lpszMenuName	= NULL; 
	winClass.lpszClassName	= "Kozio�ek Mato�ek";	//szClassName; 
	winClass.hIconSm        = ::LoadIcon(hInstance, MAKEINTRESOURCE(KOZA_ICON));	// NULL zamiast icon
	
	if (!RegisterClassEx(&winClass)) return -1;

	// stworz w odpowiedni sposob okno

	bJestBramka=false;

	if (bFullScreen==false)	// zwykle okno
	{
				
		hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, "Kozio�ek Mato�ek", "Kozio�ek Mato�ek", 
							 WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_VISIBLE, 
					 		 0, 0, 800, 600, NULL, NULL, hInstance, NULL);	
	}
	else	// fulscreen
	{
		hWnd = CreateWindowEx(NULL, "Kozio�ek Mato�ek", "Kozio�ek Mato�ek", WS_POPUP | WS_VISIBLE, 
					 		 0, 0, 800, 600, NULL, NULL, hInstance, NULL);	
	}

	CoInitialize(NULL);	// nie tylko jeden watek

//    m_bitmap = (HBITMAP)LoadImage( GetModuleHandle( NULL ),
//                                       "c:\\projects\\Fox\\screen.bmp", IMAGE_BITMAP,
//                                         800, 600, LR_LOADFROMFILE );



	Direct3DInit();		// usunac, bez funkcji pomocniczej

	// inicjalizacja systemu audio

	pAudio = new CAudio();

	if( FAILED( pAudio->Init(CurrentDirectory) ) )
	{
		MessageBox(0, "Nie mo�na zainicjalizowa� Direct Audio!", "B��d!", MB_OK);
		return 0;
	}

	pAudio->PlayMusic(L"001.wav");
	
	pBounce = new CSound(CurrentDirectory,pAudio,L"tap.wav");

	// petla przechwytywania komunikatow

	MSG msg; 

	PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );

	while(msg.message != WM_QUIT)
	{
       if ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
       {
                   TranslateMessage( &msg );
                   DispatchMessage( &msg );
       }

		DrawScene();	// rysuj klatke 
	} 

	free(pGracz1);


	free (pBubble);
	free (pBackground);
	free (pFont);
	free (pBounce);

	free (pAudio);

	pDevice->Release();
	pDirect3D->Release();

	return 0;
}
