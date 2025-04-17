// Rotation.h: interface for the CRotation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROTATION_H__632DF88A_6346_4486_8893_8A2F3F45951E__INCLUDED_)
#define AFX_ROTATION_H__632DF88A_6346_4486_8893_8A2F3F45951E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <d3d8.h>
#include <ghost.h>

// rotation - ukladanka

class CRotation  
{
public:
	CRotation();
	virtual ~CRotation();

	virtual	void	SetActive(bool bState);		// ustaw aktywnosc (czy dane sa w pamieci)
	virtual bool	GetActive(void);			// pobierz aktywnosc

	virtual	void	Initialize(IDirect3DDevice8 *pDevice);	// wczytaj dane
	virtual void	DeInitialize(void);				// usun dane

	// rysuje pojedyncza klatke i zwraca sygnal co dalej
	
	virtual int		DrawScene(long lTimer,float fMouseX, float fMouseY, 
					  bool bLeftButton, bool bRightButton, bool bCenterButton);		// rysuje pojedyncza klatke

private:

	bool	m_bActive;		// czy w pamieci znajduja sie dane

	CButton	*m_pExitButton;	// przycisk wyjscia 

	CSprite	*m_pBackground;	// tlo modulu

	CSprite *m_pKlocki[32];	// klocki do ukladanki

	CFileSystem	*m_pFile;	// od razu bedziemy zamykac

};

#endif // !defined(AFX_ROTATION_H__632DF88A_6346_4486_8893_8A2F3F45951E__INCLUDED_)
