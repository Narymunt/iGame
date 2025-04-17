// Mapa.h: interface for the CMapa class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPA_H__354C9820_738F_48E9_8E83_FCC6C3800B13__INCLUDED_)
#define AFX_MAPA_H__354C9820_738F_48E9_8E83_FCC6C3800B13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// labirynt 3d - mapa

#include <windows.h>
#include <d3d8.h>
#include <fox.h>

class CMapa  
{
public:
	CMapa();
	virtual ~CMapa();

	virtual	void	SetActive(bool bState);		// ustaw aktywnosc (czy dane sa w pamieci)
	virtual bool	GetActive(void);			// pobierz aktywnosc

	virtual	void	Initialize(IDirect3DDevice8 *pDevice);	// wczytaj dane
	virtual void	DeInitialize(void);				// usun dane

	virtual void	DrawScene(long lTimer,float fMouseX, float fMouseY, 
					  bool bLeftButton, bool bRightButton, bool bCenterButton);		// rysuje pojedyncza klatke

private:

	bool	m_bActive;		// czy w pamieci znajduja sie dane

	CButton	*m_pExitButton;	// przycisk wyjscia 

	CSprite	*m_pBackground;	// tlo modulu
	
	CFileSystem	*m_pFile;	// od razu bedziemy zamykac

};

#endif // !defined(AFX_MAPA_H__354C9820_738F_48E9_8E83_FCC6C3800B13__INCLUDED_)
