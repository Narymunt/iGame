// [game]::[starter]

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <d3d8.h>
#include <d3dx8.h>
#include <dshow.h>
#include <dmusicc.h>
#include <dmusici.h>

#include "Direct3D.h"		// obsluga urzadzenia
#include "Window.h"			// obsluga okna
#include "Sprite.h"			// sprite 
#include "Font.h"			// czcionka
#include "Audio.h"			// system audio

#define		ILE_OBIEKTOW	20

//=== aktualny katalog

char CurrentDirectory[200]		= {0,};	

//=== liczniki

long	h1,h2,h3;

//=== dla timera

int						g_FrameCount		= 0;
int						g_StartFrameCount	= 0;
DWORD					g_StartTime			= timeGetTime();
DWORD					g_EndTime			= g_StartTime;
int						g_FrameRate			= 0;

//=== glowne dla gry

CWindow		*pWindow;		// glowne okno
CDirect3D	*pDirect3D;		// handler
CFont		*pFont;			// jakas czcionka
CAudio		*pAudio;		// audio 

//=== obiekty graficzne

CSprite		**obiekty;
CSprite		*back;

//=== pomocnicza

bool Direct3DInit()
{

	pDirect3D = new CDirect3D(pWindow);
	

//	font.Initialize((HFONT)GetStockObject(SYSTEM_FONT),D3DCOLOR_XRGB(255,255,0));

    pDirect3D->pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); // backface culling 
	pDirect3D->pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );	// swiatlo
	
	// blending
	
	pDirect3D->pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDirect3D->pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDirect3D->pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// alpha channel
	
	pDirect3D->pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	// macierz widoku

	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, 0, 0, 5);
	pDirect3D->pDevice->SetTransform(D3DTS_VIEW, &(D3DMATRIX)mat);

	// dodatkowe obiekty 
	
	obiekty = new CSprite* [50];

	for (h1=0; h1<ILE_OBIEKTOW; h1++)	
	{
	obiekty[h1] = new CSprite(128,255,255,255);
	obiekty[h1]->Initialize(pDirect3D->pDevice,"sprite.tga");
	obiekty[h1]->m_Translation.x=0.5f; //272;
	obiekty[h1]->m_Translation.y=0.5f; //172;
	obiekty[h1]->m_RotCenter.x=400;
	obiekty[h1]->m_RotCenter.y=300;
	}

	back = new CSprite(255,255,255,255);
	back->Initialize(pDirect3D->pDevice,"back.bmp");
	back->m_Translation.x=0; //272;
	back->m_Translation.y=0; //172;
	back->m_RotCenter.x=400;
	back->m_RotCenter.y=300;

	pFont = new CFont();
	pFont->Initialize(pDirect3D->pDevice,(HFONT)GetStockObject(SYSTEM_FONT),D3DCOLOR_XRGB(255,255,0));

	return true;
}

// aktualizuj scenke

void UpdateScene()
{
	char str[20];
	float	fIleRotacja;
	
	back->Render();
	//back->m_Rotation+=0.1f;
	for (h1=0, fIleRotacja=0.01f;h1<ILE_OBIEKTOW;h1++,fIleRotacja+=0.01f)
	{
	obiekty[h1]->Render();
	obiekty[h1]->m_Rotation+=fIleRotacja;

	obiekty[h1]->m_RotCenter.x=-100;//h1<<4;
	obiekty[h1]->m_RotCenter.y=0;//h1<<4;

	obiekty[h1]->m_Translation.x=400;
	obiekty[h1]->m_Translation.y=300;


	obiekty[h1]->m_Scaling.x=sin(17*3.14159/(fIleRotacja*g_FrameCount));
	obiekty[h1]->m_Scaling.y=cos(15*3.14159/(fIleRotacja*g_FrameCount));
	}

	pFont->OutputText("FPS: ",10,10);
	
	_itoa(g_FrameRate,str,10);		// fps
	pFont->OutputText(str,50,10);

}

// rysuj scenke

void DrawScene()
{
	
	pDirect3D->Clear(D3DCOLOR_XRGB(0, 0, 0));
	pDirect3D->BeginScene();
	
	UpdateScene();	// to zamienic na game,background itepe
	
	g_EndTime = timeGetTime();

	if (g_EndTime - g_StartTime > 1000)
	{
		g_FrameRate = (g_FrameCount - g_StartFrameCount) * 1000 / (g_EndTime - g_StartTime);
		g_StartTime = g_EndTime;
		g_StartFrameCount = g_FrameCount;
	}

	g_FrameCount++;	
	
	pDirect3D->EndScene();
	pDirect3D->Present();
}

//### start programu ###

int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					LPSTR lpCmdLine, int nCmdShow) 
{

	bool bFullScreen;	// czy pelny ekran ? 

	// aktualny katalog
	
	GetCurrentDirectory( sizeof(CurrentDirectory), CurrentDirectory);

	// pelny ekran ? 

	if (MessageBox(NULL, "Fullscreen?", "Fullscreen?", MB_YESNO)==IDYES)
		bFullScreen=true;
	else 
		bFullScreen=false;

	pWindow = new CWindow(hInstance, "Kozio³ek Mato³ek idzie do szko³y", "Kozio³ek Mato³ek", 
					  0, 0, 800, 600, bFullScreen);

	CoInitialize(NULL);	// nie tylko jeden watek

	Direct3DInit();		// usunac, bez funkcji pomocniczej

	// inicjalizacja systemu audio

	pAudio = new CAudio();

	if( FAILED( pAudio->Init(CurrentDirectory) ) )
	{
		MessageBox(0, "Nie mo¿na zainicjalizowaæ Direct Audio!", "B³¹d!", MB_OK);
		return 0;
	}

	pAudio->PlayMusic(L"smok1.wav");
	
	// petla glowna 

	while(1)
	{
		if (pWindow->CheckMessages()==-1)	break; // koniec ? 
		
		if (GetAsyncKeyState(VK_ESCAPE)) PostQuitMessage(0); // escape ? 
		
		DrawScene();	// rysuj klatke 
	} 

	delete pDirect3D;

	return 0;
}
