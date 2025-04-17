// Window.h: interface for the CWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOW_H__C8001CC9_4772_4D5D_BB2A_6330EABE7397__INCLUDED_)
#define AFX_WINDOW_H__C8001CC9_4772_4D5D_BB2A_6330EABE7397__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <d3d8.h>
#include <windows.h>

class CWindow  
{
public:
	CWindow(HINSTANCE fp_hInstance, char *szTitle, char *szClassName, int fp_iX, int fp_iY, int fp_iWidth, int fp_iHeight, bool fp_bFullScreen);
	virtual ~CWindow();

	HWND			hWnd;
	HINSTANCE		hInstance;
	
	bool			bFullScreen;	// czy na pelnym ekranie
	
	int				iWidth;			// szerokosc
	int				iHeight;		// wysokosc
	
	int CheckMessages(); // zwraca -1 dla WM_QUIT

	static LRESULT CALLBACK 
		BasicWindowProc(HWND wpHWnd, UINT msg, WPARAM wParam, LPARAM lParam);

};

#endif // !defined(AFX_WINDOW_H__C8001CC9_4772_4D5D_BB2A_6330EABE7397__INCLUDED_)
