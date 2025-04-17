// Intro.h: interface for the CIntro class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTRO_H__10E02068_7579_44DD_9430_F6FBC14DABBB__INCLUDED_)
#define AFX_INTRO_H__10E02068_7579_44DD_9430_F6FBC14DABBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <windows.h>
#include <stdlib.h>
#include <d3d8.h>
#include <ghost.h>

class CIntro  
{
public:
	CIntro();
	virtual ~CIntro();
	virtual	void	SetActive(bool bState);		// ustaw aktywnosc (czy dane sa w pamieci)
	virtual bool	GetActive(void);			// pobierz aktywnosc

	virtual	void	Initialize(IDirect3DDevice8 *pDevice, char CurrentDirectory[200], CAudio *pAudio);	// wczytaj dane
	virtual void	DeInitialize(void);				// usun dane

	// rysuje pojedyncza klatke i zwraca sygnal co dalej
	
	virtual int		DrawScene(long lTimer,float fMouseX, float fMouseY, 
					  bool bLeftButton, bool bRightButton, bool bCenterButton, CAudio *pAudio,IDirect3DDevice8 *pDevice);		// rysuje pojedyncza klatke

private:

	bool	m_bActive;		// czy w pamieci znajduja sie dane

	CSprite	*m_pAnimation[110];	// 110 klatek animacji

	CFileSystem	*m_pFile;	// od razu bedziemy zamykac

	long	m_lLastFrame;

	long	m_lLastTimer;	// ostatni timer

};

#endif // !defined(AFX_INTRO_H__10E02068_7579_44DD_9430_F6FBC14DABBB__INCLUDED_)
