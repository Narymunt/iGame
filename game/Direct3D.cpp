// Direct3D.cpp: implementation of the CDirect3D class.
//
//////////////////////////////////////////////////////////////////////

#include "Direct3D.h"
#include <d3dx8.h>
#include <windows.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirect3D::CDirect3D(CWindow *fp_pWindow)
{
	HRESULT	hr;

	pWindow = fp_pWindow;

	// tworzymy obiekt IDirect3D

	pDirect3D = Direct3DCreate8(D3D_SDK_VERSION);

	if (pDirect3D==NULL) 
	{
		MessageBox(0,"B³¹d inicjalizacji DirectX","B³¹d!",MB_OK);
		return;// false;
	}

	// ustaw w odpowiedni sposob tryb sprawdzajac czy wyswietlamy w oknie czy
	// na calym ekranie

	D3DDISPLAYMODE displayMode;

	if (pWindow->bFullScreen==false)
	{
		hr = pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);
		
		MessageBox(0,"Nie mo¿na pobraæ informacji o trybie DirectX","B³¹d!",MB_OK);
		if (FAILED(hr)) return; //false;
	}
	else
	{
		displayMode.Width = pWindow->iWidth;
		displayMode.Height = pWindow->iHeight;
		displayMode.RefreshRate = 0; 
		displayMode.Format = D3DFMT_R5G6B5;		// dlaczego wlasnie tak ? 
	}

	// ustaw/zapamietaj parametry wyswietlania

	D3DPRESENT_PARAMETERS presentParameters;

	memset(&presentParameters, 0, sizeof(D3DPRESENT_PARAMETERS));

	if (pWindow->bFullScreen==false)
	{
		presentParameters.Windowed = TRUE;
	}
	else
	{
		presentParameters.Windowed = FALSE;
	}

	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = displayMode.Format;
	presentParameters.BackBufferWidth = displayMode.Width;
	presentParameters.BackBufferHeight = displayMode.Height;

	// stworz urzadzenie

	hr=pDirect3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, pWindow->hWnd,
                                  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                  &presentParameters, &pDevice ); 

	if (FAILED(hr))	
	{
		MessageBox(0,"Nie mo¿na stworzyæ urz¹dzenia DirectX","B³¹d!",MB_OK);		
		return; // false;
	}

	SetCursor(NULL);					// ukryj kursor myszy, rysujemy wlasny
	pDevice->ShowCursor(FALSE);			// przeslij do urzadzenia
	
	// ustaw kursor myszy na srodku ekranu

	pDevice->SetCursorPosition(400,300,D3DCURSOR_IMMEDIATE_UPDATE );	

	// ustaw macierze 

	D3DXMATRIX mat;

	// tutaj lepiej ustawic bez rzutowania typu (bez float)

	D3DXMatrixPerspectiveFovLH(&mat, D3DX_PI/6, (float)pWindow->iWidth/pWindow->iHeight, 
								1.0, 100.0);
	
	pDevice->SetTransform(D3DTS_PROJECTION, &(D3DMATRIX)mat);

	D3DXMatrixIdentity(&mat);

	pDevice->SetTransform(D3DTS_WORLD, &(D3DMATRIX)mat);
	pDevice->SetTransform(D3DTS_VIEW, &(D3DMATRIX)mat);

	return; // true;
}

CDirect3D::~CDirect3D()
{
	if (pDirect3D) pDirect3D->Release(); pDirect3D=NULL;
	if (pDevice) pDevice->Release(); pDevice=NULL;

	return ;//true;
}

// wyczysc

void CDirect3D::Clear(DWORD dwColor)
{
	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, dwColor, 1.0f, 0 );
}

// ustaw

void CDirect3D::Present()
{
	pDevice->Present(NULL, NULL, NULL, NULL);
}

// rozpocznij scene

void CDirect3D::BeginScene()
{
	pDevice->BeginScene();
}

// koniec sceny

void CDirect3D::EndScene()
{
	pDevice->EndScene();
}

// end
