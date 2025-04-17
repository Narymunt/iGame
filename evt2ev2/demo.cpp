
// general include

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <d3d8.h>
#include <d3dx8.h>
#include <dmusicc.h>
#include <dmusici.h>
#include <ctype.h>

//#include <iostream.h>

// dodatkowe

#include "Font.h"
#include "LoadScreen.h"
#include "Scene3d.h"
#include "MetaballsFX.h"
#include "RadialZoom.h"
#include "FXTemp.h"
//#include "Sprite.h"
#include "VShader.h"
#include "Event.h"
#include "EventEVT.h"

#include "GLizer.h"
#include "Matrix.h"
#include "Vector.h"
#include "textureRenderTarget.h"	// dla motion blur

#include "VShaderPlayer.h"		// odtwarza scenki z vshaderem

#include "AnimPlayer.h"			// player do animacji

// flaga debug 

#include "Debug.h"

// bass player

#include "bassplayer.h"

// ikonki, okienka 

#include "Resource.h"

#define FIELD_OF_VIEW 45.f			// angle in vertical direction
#define Z_NEAR_VIEW_PLANE 0.1f
#define Z_FAR_VIEW_PLANE 100.f


//=== testowe

CEventEVT *pAnim1;

CAnimPlayer *pAnimPlayer;

//=== opoznienie

long lDelay = 0;

//=== zmienne dla directx

D3DLIGHT8			m_light;

IDirect3D8			*pDirect3D;		// handler
IDirect3DDevice8	*pDevice;		// urzadzenie

HRESULT				hr;				// wynik operacji

HWND				hWnd;			// dla okna
HINSTANCE			hInstance;


bool				bFullScreen;	// czy pelny ekran ? 
bool				bLoadScreen;	// czy ekran wczytywania ? 

char CurrentDirectory[512]		= {0,};	// aktualny katalog

char				cLoadScreenName[256];	// nazwa pliku do wczytania ekranu

bool				bScreenSection;
int					iXScreen;
int					iYScreen;
int					iRefresh;
int					iDisplayMode;

//=== dla timera

int					g_FrameCount		= 0;
int					g_StartFrameCount	= 0;
unsigned long		g_StartTime			= timeGetTime();
unsigned long		g_DemoTime			= 0;
unsigned long		g_EndTime			= g_StartTime;
unsigned long		g_CurrentTime		= 0;
int					g_FrameRate			= 0;
long				lTimer=0;
long				lTimer10=0;
long				lLocalTimer = 0;	// timer okresla ktora scene odtwarzac, a local timer klatke
long				lEndTimer = 0;		// jak timer osiagnie ta pozycje to program konczy sie


//=== czcionki

CFont				*pFont=NULL;			// jakas czcionka

//=== efekty

CMetaballsFX		*pMetaballs = NULL;

//=== player scenek 3d

CScene3d			*pScenePlayer[50];
int					iStartPlayer[50];
int					iEndPlayer[50];
char				cScenePlayerFilename[50][256];

CSprite				*pBlur;

//=== standardowe nakladki

CSprite				*pBackground = NULL;
CSprite				*pForeground = NULL;

//=== screen loading

CSprite				*pWaitScreen=NULL;

//=== fade screens

CSprite				*pWhiteScreen=NULL;
CSprite				*pBlackScreen=NULL;

//=== kadry

CSprite				*pKadr=NULL;

//=== switch efektów

int	iCurrentScene=0;	// aktualnie odgrywana scenka

//=== player

CBassPlayer			*pBassPlayer;

//=== dodatkowe

int					iLicznik;
long				h1,h2,h3,h4;	// do petli
float				f1,f2,f3;
long				lResetTime=300000;	// jak reset time > end time to demo nie jest powtarzane


//=== fog

float			m_fFogStart=5.0f;	// 5.0f
float			m_fFogEnd=5000.0f;	// 200.0f

//unsigned int	m_uiFogColor=0x00B3A483;	// must be set, default 0x000f0f0f
unsigned int	m_uiFogColor=0x00000000;	// must be set, default 0x000f0f0f

// dla motion blur

textureRenderTarget render_target;

//=========================================================================================================================
// rysowanie kwadratowej textury na ekranie, potrzebne do blura
//=========================================================================================================================

void DrawQuad(vec p, vec n, vec s, vec t, vec4 color)
{
	GLizer gl;
	gl.glBegin(D3DPT_TRIANGLESTRIP, 1, 1, 1);    // 3  4  poradie bodov
		gl.glNormal(n);                            // 1  2
		gl.glColor(color);
		gl.glTexCoord(0,0); gl.glVertex( p );
		gl.glTexCoord(1,0); gl.glVertex( p+s );
		gl.glTexCoord(0,1); gl.glVertex( p+t );
		gl.glTexCoord(1,1); gl.glVertex( p+s+t );
	gl.glEnd(pDevice);
}

//=========================================================================================================================
// rozszerzenie textury do wielkosci ekranu
//=========================================================================================================================

void ReSizeDXScene(int width, int height)
{

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, FIELD_OF_VIEW*PI180, (float)width/(float)height, Z_NEAR_VIEW_PLANE, Z_FAR_VIEW_PLANE );
//	D3DXMatrixOrthoOffCenterLH( &matProj, 0, 800, 0, 600, -1, 1 );
	pDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

//=== zgrywa zawartosc ekranu na dysk =======================================================================

void TakeScreenShot(IDirect3DDevice8* device, char *file_name, int screenx, int screeny, long lTimer)
{
		IDirect3DSurface8 *frontbuf;	// wskaznik do pamieci, tutaj kopia ekranu
		RECT	pMyRect;
		D3DDISPLAYMODE mode;
		char	cFilename[100];


		if (FAILED(hr=device->GetDisplayMode(&mode)))
		return ;

		device->CreateImageSurface(mode.Width,mode.Height,D3DFMT_A8R8G8B8,&frontbuf);

		// kopiowanie bufora do surface

//		HRESULT hr = device->GetRenderTarget(&frontbuf);
		HRESULT hr = device->GetFrontBuffer(frontbuf);
		
		
		// sprawdzenie czy sie udalo

		if (hr!=D3D_OK)
		{
			frontbuf->Release();
			return;
		}

		// zapisz nasz obraz na dysk
		// ostatnie dwa parametry sa NULL, poniewaz chcemy caly front buffer

//		D3DXSaveSurfaceToFile(file_name,D3DXIFF_BMP, frontbuf, NULL,NULL);

		pMyRect.left = 0; 
		pMyRect.top = 0;
		pMyRect.right = 1024;
		pMyRect.bottom = 768;

		sprintf(cFilename,"image%d.bmp",lTimer);

		D3DXSaveSurfaceToFile(cFilename,D3DXIFF_BMP, frontbuf, NULL,NULL);

		// zwolnij surface

		frontbuf->Release();
}


// parsowanie skryptu

void UpOnly(char str[])
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


void Parse(void)
{
	FILE	*plik;	
	char	linia[1024];
	int		iSceneCount = 0;

	// ustaw domyslne parametry

	bLoadScreen = false;
	bScreenSection = false;

	// sprawdz czy mozna odczytac plik

	if ((plik=fopen("demo.ini","r"))==NULL)
	{
		MessageBox(NULL,"ERROR! Brak pliku demo.ini!","ERROR", MB_OK);
		PostQuitMessage( 0 );
	}

	while (strcmp(linia,"</DEMO>"))
	{
		fscanf(plik,"%s\n",&linia);	// wczytaj linie pliku
		UpOnly(linia);

		// rozpoczecie skryptu
		if (!strcmp(linia,"<DEMO>"))
		{
			fscanf(plik,"%s\n",&linia);
			UpOnly(linia);
			
			if (!strcmp(linia,"DEBUG"))
			{
				bFullScreen=false;
			}
			else
			{
				bFullScreen=true;
			}

		} // <DEMO>

		if (!strcmp(linia,"<RESET>"))	// kiedy demo sie resetuje
		{
			fscanf(plik,"%d\n",&lResetTime);
		}

		if (!strcmp(linia,"<END>"))	// koniec odtwarzania
		{
			fscanf(plik,"%d\n",&lEndTimer);
		}

		// ekran wczytywania	
	
		if (!strcmp(linia,"<LOADSCREEN>"))
		{
			fscanf(plik,"%s\n",&cLoadScreenName);
			bLoadScreen = true;			
		} // <LOADSCREEN>

		// ustawienia wyswietlania

		if (!strcmp(linia,"<SCREEN>"))
		{
			fscanf(plik,"%d\n",&iXScreen);
			fscanf(plik,"%d\n",&iYScreen);

			fscanf(plik,"%s\n",&linia);
			UpOnly(linia);

			if (!strcmp(linia,"AUTO"))
			{
				iRefresh = 0; 
			}
			else
			{
				fscanf(plik,"%d\n",&iRefresh);
			}

			fscanf(plik,"%d\n",&iDisplayMode);
			
			bScreenSection = true;
		}  // <SCREEN>
	} // <DEMO>
}

bool Direct3DInit()
{
	pDirect3D = Direct3DCreate8(D3D_SDK_VERSION);

	if (pDirect3D==NULL) 
	{
		MessageBox(0,"Cannot init DirectX 9.0 !","Error!",MB_OK);
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
			MessageBox(0,"Cannot init DirectX!","Error!",MB_OK);
			return false;
		}
	}
	else
	{
		if (bScreenSection)
		{
			displayMode.Width = iXScreen;
			displayMode.Height = iYScreen;
			
			if (iRefresh!=0) displayMode.RefreshRate = iRefresh;

			switch(iDisplayMode)
			{
			case 1:
				displayMode.Format = D3DFMT_R8G8B8;
				break;
			case 2:
				displayMode.Format = D3DFMT_A8R8G8B8;
				break;
			case 3:
				displayMode.Format = D3DFMT_X8R8G8B8;
				break;
			case 4:
				displayMode.Format = D3DFMT_R5G6B5;
				break;
			case 5:
				displayMode.Format = D3DFMT_X1R5G5B5;
				break;
			case 6:
				displayMode.Format = D3DFMT_A1R5G5B5;
				break;
			case 7:
				displayMode.Format = D3DFMT_A4R4G4B4;
				break;
			case 8:
				displayMode.Format = D3DFMT_A8;
				break;
			case 9:
				displayMode.Format = D3DFMT_R3G3B2;
				break;
			case 10:
				displayMode.Format = D3DFMT_A8R3G3B2;
				break;
			case 11:
				displayMode.Format = D3DFMT_X4R4G4B4;
				break;
			case 12:
				displayMode.Format = D3DFMT_A2B10G10R10;
				break;
			case 13:
				displayMode.Format = D3DFMT_G16R16;
				break;
			case 14:
				displayMode.Format = D3DFMT_A8P8;
				break;
			case 15:
				displayMode.Format = D3DFMT_P8;
				break;
			case 16:
				displayMode.Format = D3DFMT_L8;
				break;
			case 17:
				displayMode.Format = D3DFMT_A8L8;
				break;
			case 18:
				displayMode.Format = D3DFMT_A4L4;
				break;
			}
		}
		else
		{
			displayMode.Width = iXScreen;				//iWidth;
			displayMode.Height = iYScreen;				//iHeight;
			//displayMode.RefreshRate = 6;
			displayMode.Format = D3DFMT_A8R8G8B8;	//R5G6B5;		// tu mozna zmienic
		}
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
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;

	// stworz urzadzenie

	hr=pDirect3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                  D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                  &presentParameters, &pDevice ); 

	if (FAILED(hr))	
	{
		MessageBox(0,"Cannot create DirectX device !","Error!",MB_OK);		
		return false;
	}

	SetCursor(NULL);					// ukryj kursor myszy, rysujemy wlasny
	pDevice->ShowCursor(FALSE);			// przeslij do urzadzenia
	
	// ustaw kursor myszy na srodku ekranu

	pDevice->SetCursorPosition(400,300,D3DCURSOR_IMMEDIATE_UPDATE );	

	// ustaw macierze 

	D3DXMATRIX mat;

	// tutaj lepiej ustawic bez rzutowania typu (bez float)

//	D3DXMatrixPerspectiveFovLH(&mat, D3DX_PI/4, (float)1024/768,	-100.0, 100.0);
	D3DXMatrixPerspectiveLH(&mat, 2.3f, 3.3f*3/4, 0.5f, 10);	
	pDevice->SetTransform(D3DTS_PROJECTION, &(D3DMATRIX)mat);

	D3DXMatrixIdentity(&mat);

	// ustaw transformacje

	pDevice->SetTransform(D3DTS_WORLD, &(D3DMATRIX)mat);
	pDevice->SetTransform(D3DTS_VIEW, &(D3DMATRIX)mat);

    pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );	// backface culling off
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );			// swiatlo
	pDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE );		// dithering
	pDevice->SetRenderState( D3DRS_FILLMODE,D3DFILL_SOLID);
	pDevice->SetRenderState( D3DRS_SHADEMODE,D3DSHADE_GOURAUD);

	// blending
	
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTEXF_ANISOTROPIC);
	pDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_ANISOTROPIC);   
	pDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_ANISOTROPIC);   
	pDevice->SetTextureStageState(0, D3DTSS_MAXANISOTROPY,4);

	// alpha channel
	
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	// macierz widoku

	D3DXMatrixTranslation(&mat, 0, 0, 3);
	pDevice->SetTransform(D3DTS_VIEW, &(D3DMATRIX)mat);

	// dodatkowe obiekty - powinno byc jak najmniej

	pFont = new CFont();
	pFont->Initialize(pDevice,(HFONT)GetStockObject(SYSTEM_FONT),D3DCOLOR_XRGB(0,255,255));

	// jezeli jest ekran wczytywania to dajemy

	if (bLoadScreen)
	{
		pWaitScreen = new CSprite(255,255,255,255);	// nowy sprite
		pWaitScreen->InitializeEx(cLoadScreenName,pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);
	}

	pWhiteScreen = new CSprite(255,255,255,255);	// nowy sprite
	pWhiteScreen->InitializeEx("data\\white.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

	pBlackScreen = new CSprite(255,255,255,255);	// nowy sprite
	pBlackScreen->InitializeEx("data\\black.jpg",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

	pKadr = new CSprite(255,255,255,255);	// nowy sprite
	pKadr->InitializeEx("data\\kadr.png",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

	// tylko kiedy ma byc ekran wczytywania

	if (bLoadScreen)
	{
		pDevice->BeginScene();
		pWaitScreen->Render();	// jedno wyswietlenie

		pDevice->EndScene();
		pDevice->Present(NULL, NULL, NULL, NULL);	

		if (pWaitScreen!=NULL)
		{
			delete pWaitScreen;
			pWaitScreen=NULL;
		}
	}

	// wczytywanie 

	SetTexturePath("data");
	InitializeTextureSystem( pDevice );		

	// inicjalizacja scenek

//	ShowWindow( hWnd, SW_SHOWDEFAULT );
//	UpdateWindow( hWnd );		

//============================================================= inicjalizacja metaballs

/*
	pMetaballs = new CMetaballsFX();
	pMetaballs->Initialize(pDevice,"data\\metaballs.jpg");
*/
	// inicjalizacja scene X

//	pSceneX1 = new CVShader();
//	pSceneX1->Initialize(pDevice);

//	pKon = new CEventEVT("data\\kon.bin","kon.evt",pDevice);

	pAnim1 = new CEventEVT("data\\gazeta.bin","anim.evt",pDevice);
	pAnim1->Convert2EVT2();


	pBlur = new CSprite(128,0,0,0);
	pBlur->InitializeEx("data\\kadr.png",pDevice,0, 0, 0, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, NULL);

	if(!render_target.Init(hWnd,pDevice,1024,1024,24))
	{
		MessageBox(NULL,"ERROR! Cannot init reder_target texture","ERROR", MB_OK);			
	}

	return true;
}

//============================================================================================== aktualizuj stan dema
//=== rysuj scenke, tylko przygotowuje calosc, a potem odwoluje sie do odpowiedniej
//=== funkcji aktualizujacej w zaleznosci od CScene

void DrawScene()
{

	char str[200];

	if (g_DemoTime==0) g_DemoTime=timeGetTime();

	if (lTimer>=lResetTime) g_DemoTime= g_CurrentTime;

	g_CurrentTime = lDelay + ((timeGetTime()-g_DemoTime)/10);

	pDevice->BeginScene();
	
	render_target.Begin(pDevice);
	// sprawdz najpierw stan gry

	lTimer = (long)((g_CurrentTime));
	lTimer10 = lTimer/5;

//	pAnim1->PutScaled(1,1,lTimer10%115,0);
	pAnim1->Put(lTimer10%pAnim1->iGetEventFrameCount(0),0);
	

//	pKon->Put(1+(lTimer10%98),0);
//	pKon->Put(256,256,1+((2*lTimer10)%98),0);


	// sprawdz wszystkie scenki czy teraz pora na rysowanie
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE );



	// wypisz fps

	if (!bFullScreen)
	{
		pFont->OutputText("FPS: ",10,10);
		_itoa(g_FrameRate,str,10);		// fps
		pFont->OutputText(str,50,10);

		_itoa(g_FrameCount,str,10);
		pFont->OutputText(str,10,50);

		pFont->OutputText("timer: ",10,100);
		_ui64toa(g_CurrentTime,str,10);
		pFont->OutputText(str,50,100);
	}

	// pomiary czasu

	g_EndTime = timeGetTime();

	if (g_EndTime - g_StartTime > 1000)
	{
		g_FrameRate = (g_FrameCount - g_StartFrameCount) * 1000 / (g_EndTime - g_StartTime);
		g_StartTime = g_EndTime;
		g_StartFrameCount = g_FrameCount;
	}

	g_FrameCount++;	

	// sprawdzamy czy to koniec

	if (lTimer>=lEndTimer) PostQuitMessage(0);

	if (lTimer>=lResetTime) lTimer = 0;

	// koniec rysowania

	render_target.End();

	pDevice->EndScene();	
	pDevice->Present(NULL, NULL, NULL, NULL);	

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
		           D3DCOLOR_XRGB(24,24,24), 1.0f, 0);

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
		} 
		break;

		case WM_KEYDOWN:
			switch( wParam ) 
			{
				case VK_ESCAPE:
					PostQuitMessage( 0 );
					break;
				
				case VK_F4:
					TakeScreenShot(pDevice,"xxx",iXScreen, iYScreen,lTimer);
					break;

			}
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
	
	GetCurrentDirectory(sizeof(CurrentDirectory), CurrentDirectory);

	// parsuj skrypt

	Parse();

	// zapytaj o pelny ekran ? 

//	if (MessageBox(NULL, "Fullscreen?", "Fullscreen?", MB_YESNO)==IDYES)
//		bFullScreen=true;
//	else 
//		bFullScreen=false;



	// inicjalizacja okienka

		WNDCLASSEX winClass;

	// ustaw i zarejestruj klase okna
	
	winClass.cbSize         = sizeof(WNDCLASSEX); 
	winClass.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc	= BasicWindowProc; // nasza statyczna funkcja
	winClass.cbClsExtra		= 0;
	winClass.cbWndExtra		= 0; 
	winClass.hInstance		= hInstance; 
	winClass.hIcon			= ::LoadIcon(hInstance, MAKEINTRESOURCE(DEMO_ICON));	// NULL zamiast icon
	winClass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
	winClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH); 
	winClass.lpszMenuName	= NULL; 
	winClass.lpszClassName	= "Demo";	//szClassName; 
	winClass.hIconSm        = ::LoadIcon(hInstance, MAKEINTRESOURCE(DEMO_ICON));	// NULL zamiast icon
	
	if (!RegisterClassEx(&winClass)) return -1;

	// stworz w odpowiedni sposob okno

	if (bFullScreen==false)	// zwykle okno
	{
				
		hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, "Demo", "Demo", 
							 WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_VISIBLE, 
					 		 0, 0, iXScreen, iYScreen, NULL, NULL, hInstance, NULL);	
	}
	else	// fulscreen
	{
		hWnd = CreateWindowEx(NULL, "Demo", "Demo", WS_POPUP | WS_VISIBLE, 
					 		 0, 0, iXScreen, iYScreen, NULL, NULL, hInstance, NULL);	
	}

	CoInitialize(NULL);	// nie tylko jeden watek

	Direct3DInit();		// usunac, bez funkcji pomocniczej

	

	// inicjalizacja systemu audio

	pBassPlayer = new CBassPlayer(hWnd);

	pBassPlayer->LoadMP3("data\\demo.mp3");
	pBassPlayer->PlayMP3();

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


	pBassPlayer->StopMP3();
	delete pBassPlayer;
	delete pFont;	// fonty

	for (int i=0; i<50; i++)
	{
		if (pScenePlayer[i]!=NULL)
		{
			delete pScenePlayer[i];
			pScenePlayer[i]=NULL;
		}
	}


	// screeny

	if (pWaitScreen!=NULL)
	{
		delete pWaitScreen;
		pWaitScreen=NULL;
	}

	if (pWhiteScreen!=NULL)
	{
		delete pWhiteScreen;
		pWhiteScreen=NULL;
	}

	if (pBlackScreen!=NULL)
	{
		delete pBlackScreen;
		pBlackScreen=NULL;
	}


//	delete pKon;

	delete pAnim1;

	pDevice->Release();
	pDirect3D->Release();

	return 0;
}
