// [game]::[starter]

#include <windows.h>
#include <stdio.h>
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

//=== glowne dla gry

CWindow		*pWindow;		// glowne okno
CDirect3D	*pDirect3D;		// handler
CFont		*pFont;			//	
//=== obiekty graficzne

CSprite		*obiekt;

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

	obiekt = new CSprite();
	obiekt->Initialize(pDirect3D->pDevice,"sprite.bmp");
	obiekt->m_Translation.x=0.5f; //272;
	obiekt->m_Translation.y=0.5f; //172;
	obiekt->m_RotCenter.x=400;
	obiekt->m_RotCenter.y=300;

	return true;
}

// aktualizuj scenke

void UpdateScene()
{
	obiekt->Render();
	obiekt->m_Rotation+=0.01f;
}

// rysuj scenke

void DrawScene()
{
	pDirect3D->Clear(D3DCOLOR_XRGB(0, 0, 0));
	pDirect3D->BeginScene();

	UpdateScene();	// to zamienic na game,background itepe
	
	pDirect3D->EndScene();
	pDirect3D->Present();
}

//### start programu ###

int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					LPSTR lpCmdLine, int nCmdShow) 
{

	bool bFullScreen;	// czy pelny ekran ? 

	// pelny ekran ? 

	if (MessageBox(NULL, "Fullscreen?", "Fullscreen?", MB_YESNO)==IDYES)
		bFullScreen=true;
	else 
		bFullScreen=false;

	pWindow = new CWindow(hInstance, "Kozio³ek Mato³ek idzie do szko³y", "Kozio³ek Mato³ek", 
					  0, 0, 800, 600, bFullScreen);

	Direct3DInit();		// usunac, bez funkcji pomocniczej

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
