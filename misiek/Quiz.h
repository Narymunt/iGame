// Quiz.h: interface for the CQuiz class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUIZ_H__0E75C789_DA6E_4E1C_9312_E0AC94F94DD6__INCLUDED_)
#define AFX_QUIZ_H__0E75C789_DA6E_4E1C_9312_E0AC94F94DD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdlib.h>
#include <d3d8.h>
#include <ghost.h>

class CQuiz  
{
public:
	CQuiz();
	virtual ~CQuiz();

	virtual	void	SetActive(bool bState);		// ustaw aktywnosc (czy dane sa w pamieci)
	virtual bool	GetActive(void);			// pobierz aktywnosc

	virtual	void	Initialize(IDirect3DDevice8 *pDevice, char CurrentDirectory[200], CAudio *pAudio);	// wczytaj dane
	
	virtual void	DeInitialize(void);				// usun dane

	// rysuje pojedyncza klatke i zwraca sygnal co dalej
	
	virtual int		DrawScene(long lTimer,float fMouseX, float fMouseY, 
					  bool bLeftButton, bool bRightButton, bool bCenterButton, CAudio *pAudio);		// rysuje pojedyncza klatke

private:

	bool	m_bActive;		// czy w pamieci znajduja sie dane

	CButton	*m_pExitButton;	// przycisk wyjscia 

	CSprite	*m_pBackground;	// tlo modulu

	CSprite *m_pMysticLogo;	// logo

	CFileSystem	*m_pFile;	// od razu bedziemy zamykac

	long m_lLastTimer;	// ostatni timer

};

#endif // !defined(AFX_QUIZ_H__0E75C789_DA6E_4E1C_9312_E0AC94F94DD6__INCLUDED_)
