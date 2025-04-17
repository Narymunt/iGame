
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


int					iLicznik;

long				h1,h2,h3,h4;	// do petli

//=== zawodnik #1

CSprite				*pPlayer1;	// jego wyglad

float				fPlayer1X;	// x na ekranie
float				fPlayer1Y;	// y na ekranie

float				fPlayer1AddX;	// in/de krementator
float				fPlayer1AddY;	// in/de krementator

float				fPlayer1Angle;	// kat obrotu

float				fPlayer1Kick;		// si³a uderzenia

//=== zawodnik #2

CSprite				*pPlayer2;	// jego wygl¹d

float				fPlayer2X;	// x na ekranie
float				fPlayer2Y;	// y na ekranie

float				fPlayer2AddX;	// inkrementator
float				fPlayer2AddY;

float				fPlayer2Kick;	// si³a uderzenia

//=== pilka

CSprite				*pBall;

float				fBallX, fBallY, fBallZ;
float				fBallAddX, fBallAddY, fBallAddZ;



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

	pMouseFile = new CFileSystem("mouse.fox");
	pMouseFile->Load("myszka.tga");

	pBubble = new CSprite(255,255,255,255);
	//pBubble->Initialize(CurrentDirectory,pDevice,"combat.tga");

	pBubble->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("myszka.tga"),pDevice);

	pBackground = new CSprite(255,255,255,255);
	pMouseFile->Load("back001.bmp");
	pBackground->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("back001.bmp"),pDevice);

	// wczytaj obiekt graczy

	pPlayer1 = new CSprite(255,255,255,255);
	pMouseFile->Load("player1.tga");
	pPlayer1->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("player1.tga"),pDevice);

	fPlayer1X=368; fPlayer1Y=268;
	fPlayer1AddX=0; fPlayer1AddY=0;
	fPlayer1Angle=0;

	pPlayer2 = new CSprite(255,255,255,255);
	pMouseFile->Load("player2.tga");
	pPlayer2->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("player2.tga"),pDevice);

	// wczytaj obiekt pi³ki

	pBall = new CSprite(255,255,255,255);
	pMouseFile->Load("ball.tga");
	pBall->InitializeTGAinMemory((unsigned int*)pMouseFile->pDataBuffer,
		pMouseFile->Search("ball.tga"),pDevice);

	return true;
}

//=== aktualizuj scenke, to ma byc wymienione i podzielone na czesci

void UpdateScene()
{
	char	str[20];	// tymczasowy


	pBackground->Render();

	// player 1 biegnie

	// nie za szybko ? 

	if (fPlayer1AddX>2.0f)
	{
		fPlayer1AddX=2.0f;
	}

	if (fPlayer1AddX<-2.0f)
	{
		fPlayer1AddX=-2.0f;
	}

	if (fPlayer1AddY>2.0f)
	{
		fPlayer1AddY=2.0f;
	}

	if (fPlayer1AddY<-2.0f)
	{
		fPlayer1AddY=-2.0f;
	}


	fPlayer1X+=fPlayer1AddX;
	fPlayer1Y+=fPlayer1AddY;

	// jezeli nie trzymany klawisz to zwalnia 
	
	// if (fPlayer1AddX>0)
	// {
	//		fPlayer1AddX-=0.5f;
	// }
	
	// jezeli trzymany to przyspiesza w kierunku 


	// odbicia od scian

	if (fPlayer1X>736 && fPlayer1AddX>0)	// prawa
	{
		fPlayer1AddX = -fPlayer1AddX+(fPlayer1AddX*0.3f);
	}
	
	if (fPlayer1X<0&&fPlayer1AddX<0 )		// lewa
	{
		fPlayer1AddX = -fPlayer1AddX+(fPlayer1AddX*0.3f);
	}


	if (fPlayer1Y<0 && fPlayer1AddY<0)		// gora
	{
		fPlayer1AddY = -fPlayer1AddY+(fPlayer1AddY*0.3f);
	}

	if (fPlayer1Y>536 && fPlayer1AddY>0)
	{
		fPlayer1AddY = - fPlayer1AddY+(fPlayer1AddY*0.3f);
	}

	// odbicia wzajemne poziome

//	for (h1=0;h1<ILE_KULEK;h1++)
//	{
//		if (
//			(fKabzdelX[iLicznik]>fKabzdelX[h1])&&
//			(fKabzdelX[iLicznik]<fKabzdelX[h1]+64)&&
//			fKabzdelAddX[iLicznik]<0)	// prawa
//		{
//			fKabzdelAddX[iLicznik] = -fKabzdelAddX[iLicznik]-fKabzdelAddX[h1];
//			fKabzdelAddX[h1] = -fKabzdelAddX[h1]-fKabzdelAddX[iLicznik];
//
//			pBounce->Play(pAudio,0,0,0);

			//fKabzdelAddX[iLicznik] = -fKabzdelAddX[iLicznik]*0.7f;
//		}
//
//		if (
//			(fKabzdelX[iLicznik]<fKabzdelX[h1])&&
//			(fKabzdelX[iLicznik]>fKabzdelX[h1]-64)&&
//			fKabzdelAddX[iLicznik]>0)	// lewa
//		{
//			fKabzdelAddX[iLicznik] = -fKabzdelAddX[iLicznik]-fKabzdelAddX[h1];
//			fKabzdelAddX[h1] = -fKabzdelAddX[h1]-fKabzdelAddX[iLicznik];

//			pBounce->Play(pAudio,0,0,0);

//		}
			

//		if (fKabzdelX[iLicznik]>fKabzdelX[h1]&&fKabzdelX[iLicznik]-64<fKabzdelX[h1])	// lewa
//		{
			//fKabzdelAddX[iLicznik] = -fKabzdelAddX[iLicznik];
//		}

//	}

	// tarcie poziome i pionowe (biegnie pod gorke, albo z gorki)

	if (fPlayer1AddX>0) fPlayer1AddX-=0.1f;
	if (fPlayer1AddX<0) fPlayer1AddX+=0.1f;
	
	if (fPlayer1AddY>0)	fPlayer1AddY-=0.1f;
	if (fPlayer1AddY<0) fPlayer1AddY+=0.1f;


	//if (fKabzdelAddX[iLicznik]>0) fKabzdelAddX[iLicznik]-=0.01f;
	//if (fKabzdelAddX[iLicznik]<0) fKabzdelAddX[iLicznik]+=0.01f;


	// przesuniecie na ekranie

	pPlayer1->SetTranslation(fPlayer1X, fPlayer1Y);
	
	// obrot

	pPlayer1->SetRotationCenter(32,32);
	pPlayer1->SetRotation(fPlayer1Angle);	

	// sprawdz czy biegnie 

	if (GetAsyncKeyState(VK_RSHIFT)!=0)
	{
	}


	// rysuj

	pPlayer1->Render();
	
	pBubble->SetRotationCenter(0,64);
	
	if (rightButton) pBubble->AddRotation(0.01f);

	leftButton ? pBubble->SetTranslation(mouseX+16,mouseY+16) : pBubble->SetTranslation(mouseX,mouseY);

//	pBubble->SetTranslation(mouseX,mouseY) ? !leftButton : leftButton;

	//pBubble->SetTranslation(mouseX,mouseY);
	pBubble->Render();


	pFont->OutputText("FPS: ",10,10);
	_itoa(g_FrameRate,str,10);		// fps
	pFont->OutputText(str,50,10);

	pFont->OutputText("Player1 Angle: ",10,30);
	_itoa(fPlayer1Angle*10,str,10);
	pFont->OutputText(str,120,30);

	pFont->OutputText("Player1 X: ",10,50);
	_itoa(fPlayer1X,str,10);
	pFont->OutputText(str,120,50);

	_itoa(GetAsyncKeyState(VK_RSHIFT),str,10);
	pFont->OutputText(str,10,160);

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

				case VK_UP:

					// lewo 

					if (fPlayer1Angle>=0 && fPlayer1Angle<1.5f)
					{
						fPlayer1AddX-=fPlayer1Angle;
						fPlayer1AddY-=(1.5f-fPlayer1Angle);
					}

					if (fPlayer1Angle>=1.5f && fPlayer1Angle<3.0f)
					{
						fPlayer1AddX-=(3.0f-fPlayer1Angle);
						fPlayer1AddY+=fPlayer1Angle-1.5f;
					}

					if (fPlayer1Angle>=3.0f && fPlayer1Angle<4.7f)
					{
						fPlayer1AddX+=fPlayer1Angle-3.0f;
						fPlayer1AddY+=4.5f-fPlayer1Angle;
					}

					if (fPlayer1Angle>=4.7)
					{
						fPlayer1AddX+=6.3f-fPlayer1Angle;
						fPlayer1AddY-=6.3f-fPlayer1Angle;
					}

					// prawo

					if (fPlayer1Angle<0 && fPlayer1Angle>-1.6f)
					{
						fPlayer1AddX-=fPlayer1Angle;
						fPlayer1AddY-=(1.5f-fPlayer1Angle);
					}

					if (fPlayer1Angle<=-1.6f && fPlayer1Angle>-3.1f)
					{
						fPlayer1AddX+=(3.1f+fPlayer1Angle);
						fPlayer1AddY-=fPlayer1Angle+1.6f;
					}

					if (fPlayer1Angle<=-3.1f && fPlayer1Angle>-4.7f)
					{
						fPlayer1AddX+=fPlayer1Angle+3.0f;
						fPlayer1AddY+=4.5f-fPlayer1Angle;
					}

					if (fPlayer1Angle<=-4.7)
					{
						fPlayer1AddX-=6.3f-fPlayer1Angle;
						fPlayer1AddY-=6.3f-fPlayer1Angle;
					}
					
					break;

				case VK_LEFT:
					
					fPlayer1Angle+=0.1f;
					
					if (fPlayer1Angle>6.2)
					{
						fPlayer1Angle=0;
					}

					break;

				case VK_RIGHT:
					
					fPlayer1Angle-=0.1f;

					if (fPlayer1Angle<-6.2)
					{
						fPlayer1Angle=0;
					}

					break;
		

				case VK_DOWN:

					fPlayer1AddX-=fPlayer1Angle;
					fPlayer1AddY-=fPlayer1Angle;
					
					break;				

				case VK_SPACE:
					fPlayer1Angle=0;
					fPlayer1AddX=0;
					fPlayer1AddY=0;
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

//    m_bitmap = (HBITMAP)LoadImage( GetModuleHandle( NULL ),
//                                       "c:\\projects\\Fox\\screen.bmp", IMAGE_BITMAP,
//                                         800, 600, LR_LOADFROMFILE );



	Direct3DInit();		// usunac, bez funkcji pomocniczej

	// inicjalizacja systemu audio

	pAudio = new CAudio();

	if( FAILED( pAudio->Init(CurrentDirectory) ) )
	{
		MessageBox(0, "Nie mo¿na zainicjalizowaæ Direct Audio!", "B³¹d!", MB_OK);
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

	free(pPlayer1);


	free (pBubble);
	free (pBackground);
	free (pFont);
	free (pBounce);

	free (pAudio);

	pDevice->Release();
	pDirect3D->Release();

	return 0;
}
