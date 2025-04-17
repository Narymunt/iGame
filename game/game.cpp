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


//=== glowne dla gry

CWindow		Window;		// glowne okno
CDirect3D	Direct3D;	// handler

//=== pomocnicza

bool Direct3DInit()
{

	Direct3D.Create(&Window);
	

//	font.Initialize((HFONT)GetStockObject(SYSTEM_FONT),D3DCOLOR_XRGB(255,255,0));
	
    Direct3D.pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); // backface culling 
	Direct3D.pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );	// swiatlo
	
	// blending
	
	Direct3D.pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	Direct3D.pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	Direct3D.pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// alpha channel
	
	Direct3D.pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	// macierz widoku

	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, 0, 0, 5);
	Direct3D.pDevice->SetTransform(D3DTS_VIEW, &(D3DMATRIX)mat);

	return true;
}

// aktualizuj scenke

void UpdateScene()
{

	int h1;

	h1++;

}

// rysuj scenke

void DrawScene()
{
	Direct3D.Clear(D3DCOLOR_XRGB(0, 0, 0));
	Direct3D.BeginScene();

	UpdateScene();	// to zamienic na game,background itepe
	
	Direct3D.EndScene();
	Direct3D.Present();
}

// usun urzadzenie 

void Direct3DRelease()
{
	Direct3D.Release();
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

	Window.MakeWindow(hInstance, "Kozio³ek Mato³ek idzie do szko³y", "Kozio³ek Mato³ek", 
					  0, 0, 800, 600, bFullScreen);

	Direct3DInit();		// usunac, bez funkcji pomocniczej

	// petla glowna 

	while(1)
	{
		if (Window.CheckMessages()==-1)	break; // koniec ? 
		
		if (GetAsyncKeyState(VK_ESCAPE)) PostQuitMessage(0); // escape ? 
		
		DrawScene();	// rysuj klatke 
	} 

	Direct3DRelease();	// usunac, bez funkcji pomocniczej

	return 0;

}