// Window.cpp: implementation of the CWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "Window.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWindow::CWindow(HINSTANCE fp_hInstance, char *szTitle, char *szClassName, int fp_iX, int fp_iY, int fp_iWidth, int fp_iHeight, bool fp_bFullScreen)
{
	WNDCLASSEX winClass;

	hInstance = fp_hInstance;
	bFullScreen = fp_bFullScreen;
	iWidth = fp_iWidth;
	iHeight = fp_iHeight;

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
	winClass.lpszClassName	= szClassName; 
	winClass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);
	
	if (!RegisterClassEx(&winClass)) return;

	// stworz w odpowiedni sposob okno

	if (bFullScreen==false)	// zwykle okno
	{
				
		hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,  
							 szClassName,     
							 szTitle, 
							 WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_VISIBLE, 
					 		 fp_iX, fp_iY,
							 iWidth, iHeight,
							 NULL,
							 NULL,
							 hInstance,  
							 NULL);	
	}
	else	// fulscreen
	{
		
		hWnd = CreateWindowEx(NULL,  
							 szClassName,     
							 szTitle,  
							 WS_POPUP | WS_VISIBLE, 
					 		 fp_iX, fp_iY,
							 iWidth, iHeight,
							 NULL,
							 NULL,
							 hInstance,  
							 NULL);	
	}
}

CWindow::~CWindow()
{

}

// petla obslugi zdarzen

int CWindow::CheckMessages()
{
	MSG msg;

	while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{ 
	    TranslateMessage(&msg);
	    DispatchMessage(&msg); 

		if (msg.message == WM_QUIT)	return -1;
	}
	
	return 0;
}

// funkcja obslugi zdarzen okna

LRESULT CALLBACK CWindow::BasicWindowProc(HWND wpHWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch(msg)
	{	
		case WM_DESTROY: 
		{ 
			PostQuitMessage(0);
			return 0;
		} break;
		default:break; 
	} 

	return DefWindowProc(wpHWnd, msg, wParam, lParam);
}

// end
