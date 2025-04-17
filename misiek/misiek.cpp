
// misiek

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <d3d8.h>
#include <d3dx8.h>
#include <dmusicc.h>
#include <dmusici.h>

#include <ghost.h>

// modu³y

#include "Mapa.h"
#include "Rotation.h"
#include "Intro.h"
#include "Quiz.h"

// zasoby

#include "Resource.h"


//=== zmienne dla directx

IDirect3D8			*pDirect3D;		// handler
IDirect3DDevice8	*pDevice;		// urzadzenie

HRESULT				hr;				// wynik operacji

HWND				hWnd;			// dla okna
HINSTANCE			hInstance;

bool				bFullScreen;	// czy pelny ekran ? 

CMouse				*pMouse;		// mysz

//=== aktualny katalog

char CurrentDirectory[200]		= {0,};	

//=== systemy plikow

CFileSystem			*pMisiekFile;		// hmm...?

//=== dla timera

int					g_FrameCount		= 0;
int					g_StartFrameCount	= 0;
DWORD				g_StartTime			= timeGetTime();
DWORD				g_EndTime			= g_StartTime;
int					g_FrameRate			= 0;

//=== dla systemu dzwiekowego

CAudio				*pAudio;

//=== czcionki

CFont				*pFont;			// jakas czcionka

//=== gra

// intro - animacja poczatkowa
// mapa
// start - wejscie do gry
// rotation - [modul] ukladanki
// end - wyjscie z gry
// outro - zwyciestwo w grze
// duze_male - [modul] wewnatrz jaskinii zgadywanie
// dots2dots - [modul] ukladanka - kropki
// quiz - [modul] pytanie odpowiedŸ
// boulder dash - [modul] wewnatrz jaskinii
// details - [modul] znajdz szczegoly
// puzzle - [modul] ukladanka
// football - [modul] gra w pilke 


enum STAN_GRY		{
						INTRO,
						MAPA,
						START,
						ROTATION,
						ROTATION_PUZZLE,
						DUZE_MALE,
						DOTS2DOTS,
						QUIZ,
						BOULDER_DASH,
						DETAILS,
						PUZZLE,
						FOOTBALL, 
						END,
						OUTRO
					} eStanGry;

//=== modu³y ===

CMapa		*pMapa;		// modul mapy (labirynt 3d)
CRotation	*pRotation;	// ukladanka
CRotation	*pRotationPuzzle;	// ukladanka puzzle
CIntro		*pIntro;	// intro - animacja 
CQuiz		*pQuiz;		// quiz

//=== dodatkowe

int					iLicznik;

long				h1,h2,h3,h4;	// do petli

float				f1,f2,f3;


//=== pomocnicza, inicjalizuje direct3d i ustawia rozne dodatki

bool Direct3DInit()
{

	pDirect3D = Direct3DCreate8(D3D_SDK_VERSION);

	if (pDirect3D==NULL) 
	{
		MessageBox(0,"B³¹d inicjalizacji DirectX 8.1 !","B³¹d!",MB_OK);
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
			MessageBox(0,"Nie mo¿na pobraæ informacji o aktualnym trybie DirectX","B³¹d!",MB_OK);
			return false;
		}
	}
	else
	{
		displayMode.Width = 800;				//iWidth;
		displayMode.Height = 600;				//iHeight;
//		displayMode.RefreshRate = 0; 
		displayMode.Format = D3DFMT_A8R8G8B8;		// tu mozna zmienic
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
		MessageBox(0,"Nie mo¿na stworzyæ urz¹dzenia DirectX!","B³¹d!",MB_OK);		
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
	pDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE );		// dithering
	
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
	pFont->Initialize(pDevice,(HFONT)GetStockObject(SYSTEM_FONT),D3DCOLOR_XRGB(0,255,255));

	//=== modu³y

	pMapa = new CMapa();
	pRotation = new CRotation();
	pIntro = new CIntro();
	pRotationPuzzle = new CRotation();
	pQuiz = new CQuiz();

	//=== myszka 

	pMouse = new CMouse();
	pMouse->Initialize(pDevice,"Resource\\myszka.fox");
	pMouse->AddCustomPoint(pDevice,0,"myszka.tga","Resource\\myszka.fox");

	return true;
}

//=== rysuj scenke, tylko przygotowuje calosc, a potem odwoluje sie do odpowiedniej
//=== funkcji aktualizujacej w zaleznosci od CScene

void DrawScene()
{
	char	str[20];	// tymczasowy

	pDevice->BeginScene();

	// sprawdz najpierw stan gry

	switch	(eStanGry)
	{
		
	case	INTRO:
				if (!pIntro->GetActive()) // nie zawiera danych
				{
					pIntro->Initialize(pDevice,CurrentDirectory,pAudio);
				}

				if (pIntro->GetActive())	// tutaj leci intro
				{
					
					//pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 );
					
					// przelaczyc ? 
					
					if (pIntro->DrawScene(g_FrameCount,
						pMouse->GetMouseX(), pMouse->GetMouseY(),
						pMouse->GetLeftButtonState(),
						pMouse->GetCenterButtonState(),
						pMouse->GetRightButtonState(),pAudio,pDevice)==109
						)
					{
						pIntro->DeInitialize();
						eStanGry=MAPA;
					}
				}
				

			break;

	case	MAPA:
				if (!pMapa->GetActive())	// nie zawiera danych
				{
					pMapa->Initialize(pDevice);	// wczytaj dane
				}
	
				if (pMapa->GetActive())
				{
					
					// zmiany stanu w zaleznosci od planszy
					
					switch (
						pMapa->DrawScene(g_FrameCount,
						pMouse->GetMouseX(), pMouse->GetMouseY(),
						pMouse->GetLeftButtonState(),
						pMouse->GetCenterButtonState(),
						pMouse->GetRightButtonState())
						)
						{
							// lewy przycisk, button exit
					
							case 2:
									pMapa->DeInitialize();
									eStanGry = ROTATION;
									break;

						}
				}

				break;

	case	ROTATION:
				if (!pRotation->GetActive())	// nie zawiera danych
				{
					pAudio->StopMusic(5);		// zmiana muzyki

					if( FAILED( pAudio->Init(CurrentDirectory,"Resource\\Music") ) )
					{
						MessageBox(0, "Nie mo¿na zainicjalizowaæ Direct Audio!", "B³¹d!", MB_OK);
					}

					pAudio->PlayMusic(L"001.wav");

					pRotation->Initialize(pDevice,CurrentDirectory,pAudio );	// wczytaj dane

				}
	
				if (pRotation->GetActive())
				{
					switch (
						pRotation->DrawScene(g_FrameCount,
						pMouse->GetMouseX(), pMouse->GetMouseY(),
						pMouse->GetLeftButtonState(),
						pMouse->GetCenterButtonState(),
						pMouse->GetRightButtonState(),pAudio)		// rysuje jezeli aktywne
						)
					{
						// lewy przycisk, button exit
	
					case 2:
								pRotation->DeInitialize();
								eStanGry = ROTATION_PUZZLE;
								break;
					}
				}
				break;

	case	ROTATION_PUZZLE:
				if (!pRotationPuzzle->GetActive())	// nie zawiera danych
				{
					pAudio->StopMusic(5);		// zmiana muzyki

					if( FAILED( pAudio->Init(CurrentDirectory,"Resource\\Music") ) )
					{
						MessageBox(0, "Nie mo¿na zainicjalizowaæ Direct Audio!", "B³¹d!", MB_OK);
					}

					pAudio->PlayMusic(L"003.wav");

					pRotationPuzzle->Initialize_Puzzle(pDevice,CurrentDirectory,pAudio );	// wczytaj dane

				}
	
				if (pRotationPuzzle->GetActive())
				{
					switch (
						pRotationPuzzle->DrawScene(g_FrameCount,
						pMouse->GetMouseX(), pMouse->GetMouseY(),
						pMouse->GetLeftButtonState(),
						pMouse->GetCenterButtonState(),
						pMouse->GetRightButtonState(),pAudio)		// rysuje jezeli aktywne
						)
					{
						// lewy przycisk myszy, button exit
					case 4: 
							pRotationPuzzle->DeInitialize();
							eStanGry = QUIZ;
							break;
					}
				}
				break;

	case	QUIZ:
				if (!pQuiz->GetActive())	// nie zawiera danych
				{
					pAudio->StopMusic(5);		// zmiana muzyki

					if( FAILED( pAudio->Init(CurrentDirectory,"Resource\\Music") ) )
					{
						MessageBox(0, "Nie mo¿na zainicjalizowaæ Direct Audio!", "B³¹d!", MB_OK);
					}

					pAudio->PlayMusic(L"004.wav");

					pQuiz->Initialize(pDevice,CurrentDirectory,pAudio );	// wczytaj dane

				}
	
				if (pQuiz->GetActive())
				{
					switch (
						pQuiz->DrawScene(g_FrameCount,
						pMouse->GetMouseX(), pMouse->GetMouseY(),
						pMouse->GetLeftButtonState(),
						pMouse->GetCenterButtonState(),
						pMouse->GetRightButtonState(),pAudio)		// rysuje jezeli aktywne
						)
					{
						// lewy przycisk myszy, button exit
					case 2: 
							pRotationPuzzle->DeInitialize();
							eStanGry = QUIZ;
							break;
					}
				}
				break;

				
	}
	

	// tutaj kursor myszy

	pMouse->Render(0);

	// wypisz fps

	pFont->OutputText("FPS: ",10,10);
	_itoa(g_FrameRate,str,10);		// fps
	pFont->OutputText(str,50,10);

	// pomiary czasu

	g_EndTime = timeGetTime();

	if (g_EndTime - g_StartTime > 1000)
	{
		g_FrameRate = (g_FrameCount - g_StartFrameCount) * 1000 / (g_EndTime - g_StartTime);
		g_StartTime = g_EndTime;
		g_StartFrameCount = g_FrameCount;
	}

	g_FrameCount++;	
	
	// koniec rysowania

	pDevice->EndScene();	
	pDevice->Present(NULL, NULL, NULL, NULL);	
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
			}
			break;

		// myszka

		case WM_MOUSEMOVE:
			pMouse->SetMouseX(LOWORD(lParam));
			pMouse->SetMouseY(HIWORD(lParam));
			break;

		case WM_LBUTTONDOWN:
			pMouse->SetLeftButtonState(true);
			 break;

		case WM_LBUTTONUP:
			pMouse->SetLeftButtonState(false);
			break;

		case WM_RBUTTONDOWN:
			pMouse->SetRightButtonState(true);
			break;

		case WM_RBUTTONUP:
			pMouse->SetRightButtonState(false);
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
	
	// tak wyglada na poczatku

	eStanGry = INTRO;

	// pobierz aktualny katalog
	
	GetCurrentDirectory( sizeof(CurrentDirectory), CurrentDirectory);

	// zapytaj o pelny ekran ? 

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
	winClass.hIcon			= ::LoadIcon(hInstance, MAKEINTRESOURCE(MISIEK_ICON));	// NULL zamiast icon
	winClass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
	winClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH); 
	winClass.lpszMenuName	= NULL; 
	winClass.lpszClassName	= "Misiek";	//szClassName; 
	winClass.hIconSm        = ::LoadIcon(hInstance, MAKEINTRESOURCE(MISIEK_ICON));	// NULL zamiast icon
	
	if (!RegisterClassEx(&winClass)) return -1;

	// stworz w odpowiedni sposob okno

	if (bFullScreen==false)	// zwykle okno
	{
				
		hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, "Misiek", "Misiek", 
							 WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_VISIBLE, 
					 		 0, 0, 800, 600, NULL, NULL, hInstance, NULL);	
	}
	else	// fulscreen
	{
		hWnd = CreateWindowEx(NULL, "Misiek", "Misiek", WS_POPUP | WS_VISIBLE, 
					 		 0, 0, 800, 600, NULL, NULL, hInstance, NULL);	
	}

	CoInitialize(NULL);	// nie tylko jeden watek

	Direct3DInit();		// usunac, bez funkcji pomocniczej

	// inicjalizacja systemu audio

	pAudio = new CAudio();

	if( FAILED( pAudio->Init(CurrentDirectory,"Resource\\Music") ) )
	{
		MessageBox(0, "Nie mo¿na zainicjalizowaæ Direct Audio!", "B³¹d!", MB_OK);
		return 0;
	}

	pAudio->PlayMusic(L"002.wav");

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

	delete pMapa;
	delete pRotation;
	delete pRotationPuzzle;
	delete pIntro;
	delete pQuiz;

	// zwolnij myszke

	pMouse->DeInitialize();

	delete pMouse;

	// fonty

	delete pFont;

	delete pAudio;

	pDevice->Release();
	pDirect3D->Release();

	return 0;
}
