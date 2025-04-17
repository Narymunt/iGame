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

#include "Sprite.h"			// sprite 
#include "Font.h"			// czcionka
#include "Audio.h"			// system audio
#include "Sound.h"			// dzwiek

#define		ILE_OBIEKTOW	20

//=== dla dx

IDirect3D8			*pDirect3D;
IDirect3DDevice8	*pDevice;
HRESULT				hr;
HWND				hWnd;
HINSTANCE			hInstance;

bool bFullScreen;	// czy pelny ekran ? 

bool			leftButton;		// przyciski myszki
bool			rightButton;
bool			centerButton;

float			mouseX;
float			mouseY;


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

CFont		*pFont;			// jakas czcionka
CAudio		*pAudio;		// audio 

//=== obiekty graficzne

CSprite		**obiekty;
CSprite		*back;
CSprite		*kursor_myszy;

//=== dzwieki

CSound		*pik;

//=== pomocnicza

bool Direct3DInit()
{

	pDirect3D = Direct3DCreate8(D3D_SDK_VERSION);

	if (pDirect3D==NULL) 
	{
		MessageBox(0,"B³¹d inicjalizacji DirectX","B³¹d!",MB_OK);
		return false;
	}

	// ustaw w odpowiedni sposob tryb sprawdzajac czy wyswietlamy w oknie czy
	// na calym ekranie

	D3DDISPLAYMODE displayMode;

	if (bFullScreen==false)
	{
		hr = pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);
		
		MessageBox(0,"Nie mo¿na pobraæ informacji o trybie DirectX","B³¹d!",MB_OK);
		if (FAILED(hr)) return false;
	}
	else
	{
		displayMode.Width = 800; //iWidth;
		displayMode.Height = 600; //iHeight;
		displayMode.RefreshRate = 0; 
		displayMode.Format = D3DFMT_R5G6B5;		// dlaczego wlasnie tak ? 
	}

	// ustaw/zapamietaj parametry wyswietlania

	D3DPRESENT_PARAMETERS presentParameters;

	memset(&presentParameters, 0, sizeof(D3DPRESENT_PARAMETERS));

	if (bFullScreen==false)
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

	hr=pDirect3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                  &presentParameters, &pDevice ); 

	if (FAILED(hr))	
	{
		MessageBox(0,"Nie mo¿na stworzyæ urz¹dzenia DirectX","B³¹d!",MB_OK);		
		return false;
	}

	SetCursor(NULL);					// ukryj kursor myszy, rysujemy wlasny
	pDevice->ShowCursor(FALSE);			// przeslij do urzadzenia
	
	// ustaw kursor myszy na srodku ekranu

	pDevice->SetCursorPosition(400,300,D3DCURSOR_IMMEDIATE_UPDATE );	

	// ustaw macierze 

	D3DXMATRIX mat;

	// tutaj lepiej ustawic bez rzutowania typu (bez float)

	D3DXMatrixPerspectiveFovLH(&mat, D3DX_PI/6, (float)800/600,	1.0, 100.0);
	
	pDevice->SetTransform(D3DTS_PROJECTION, &(D3DMATRIX)mat);

	D3DXMatrixIdentity(&mat);

	pDevice->SetTransform(D3DTS_WORLD, &(D3DMATRIX)mat);
	pDevice->SetTransform(D3DTS_VIEW, &(D3DMATRIX)mat);


//	font.Initialize((HFONT)GetStockObject(SYSTEM_FONT),D3DCOLOR_XRGB(255,255,0));

    pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); // backface culling 
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );	// swiatlo
	
	// blending
	
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// alpha channel
	
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	// macierz widoku

//	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, 0, 0, 5);
	pDevice->SetTransform(D3DTS_VIEW, &(D3DMATRIX)mat);

	// dodatkowe obiekty 
	
	obiekty = new CSprite* [50];

	for (h1=0; h1<ILE_OBIEKTOW; h1++)	
	{
	obiekty[h1] = new CSprite(128,255,255,255);
	obiekty[h1]->Initialize(pDevice,"sprite.tga");
	obiekty[h1]->m_Translation.x=0.5f; //272;
	obiekty[h1]->m_Translation.y=0.5f; //172;
	obiekty[h1]->m_RotCenter.x=400;
	obiekty[h1]->m_RotCenter.y=300;
	}

	back = new CSprite(255,255,255,255);
	back->Initialize(pDevice,"back.bmp");
	back->m_Translation.x=0; //272;
	back->m_Translation.y=0; //172;
	back->m_RotCenter.x=400;
	back->m_RotCenter.y=300;

	pFont = new CFont();
	pFont->Initialize(pDevice,(HFONT)GetStockObject(SYSTEM_FONT),D3DCOLOR_XRGB(255,255,0));

	kursor_myszy = new CSprite(128,255,255,255);
	kursor_myszy->Initialize(pDevice,"mouse.tga");

	return true;
}

// aktualizuj scenke

void UpdateScene()
{
	char	str[20];
	float	fIleRotacja;
	
	back->Render();	
	
	kursor_myszy->m_Translation.x=mouseX;
	kursor_myszy->m_Translation.y=mouseY;
	kursor_myszy->Render();

	//back->m_Rotation+=0.1f;

	for (h1=0, fIleRotacja=0.01f;h1<ILE_OBIEKTOW;h1++,fIleRotacja+=0.01f)
	{
	obiekty[h1]->Render();
	obiekty[h1]->m_Rotation+=fIleRotacja;

	obiekty[h1]->m_RotCenter.x=-100;//h1<<4;
	obiekty[h1]->m_RotCenter.y=0;//h1<<4;

	obiekty[h1]->m_Translation.x=400;
	obiekty[h1]->m_Translation.y=300;


	obiekty[h1]->m_Scaling.x=h1>>1;
	obiekty[h1]->m_Scaling.y=-h1>>1;
	}

	pFont->OutputText("FPS: ",10,10);
	
	_itoa(g_FrameRate,str,10);		// fps
	pFont->OutputText(str,50,10);

}

// rysuj scenke

void DrawScene()
{
	
	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 );
	//pDirect3D->Clear(D3DCOLOR_XRGB(0, 0, 0));
	pDevice->BeginScene();
	//pDirect3D->BeginScene();
	
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

// obsluga okna

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
			}
			break;

		case WM_MOUSEMOVE:
			mouseX = LOWORD(lParam);
			mouseY = HIWORD(lParam);
			break;

		case WM_SETCURSOR:
            // Turn off the cursor since this is a full-screen app
            SetCursor(NULL);
            return TRUE;


		default:break; 
	} 

	return DefWindowProc(wpHWnd, msg, wParam, lParam);
}


//### start programu ###

int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					LPSTR lpCmdLine, int nCmdShow) 
{
	// aktualny katalog
	
	GetCurrentDirectory( sizeof(CurrentDirectory), CurrentDirectory);

	// pelny ekran ? 

	if (MessageBox(NULL, "Fullscreen?", "Fullscreen?", MB_YESNO)==IDYES)
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
	winClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	// NULL zamiast icon
	winClass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
	winClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH); 
	winClass.lpszMenuName	= NULL; 
	winClass.lpszClassName	= "Kozio³ek Mato³ek";	//szClassName; 
	winClass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);
	
	if (!RegisterClassEx(&winClass)) return -1;

	// stworz w odpowiedni sposob okno

	if (bFullScreen==false)	// zwykle okno
	{
				
		hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, "Kozio³ek Mato³ek", "Kozio³ek Mato³ek", 
							 WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_VISIBLE, 
					 		 0, 0, 800, 600, NULL, NULL, hInstance, NULL);	
	}
	else	// fulscreen
	{
		hWnd = CreateWindowEx(NULL, "Kozio³ek Mato³ek", "Kozio³ek Mato³ek", WS_POPUP | WS_VISIBLE, 
					 		 0, 0, 800, 600, NULL, NULL, hInstance, NULL);	
	}

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

	pik = new CSound(pAudio,L"pik.wav");


	MSG msg;

	while(msg.message != WM_QUIT)
	{
       if ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
       {
                   TranslateMessage( &msg );
                   DispatchMessage( &msg );
       }

		DrawScene();	// rysuj klatke 
	} 

//	delete pDirect3D;

	return 0;
}
