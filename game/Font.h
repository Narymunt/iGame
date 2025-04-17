// Font.h: interface for the CFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONT_H__B9454C09_041C_4E44_A2B7_9801CA053701__INCLUDED_)
#define AFX_FONT_H__B9454C09_041C_4E44_A2B7_9801CA053701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFont  
{
public:
	CFont();
	virtual ~CFont();

	HRESULT					Initialize(IDirect3DDevice8 *g_pDevice,HFONT hFont, D3DCOLOR FontColor);		// init
	
	HRESULT					OutputText(char *pString, int x, int y);	

	D3DCOLOR				m_FontColor;
	int						m_Align;			// alignowanie
	
	LPD3DXFONT				m_pFont;	// jaka czcionka
	
	RECT					m_FontRect;
	BOOL					m_bInitialized;

};

#endif // !defined(AFX_FONT_H__B9454C09_041C_4E44_A2B7_9801CA053701__INCLUDED_)
