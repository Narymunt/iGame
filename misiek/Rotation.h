// Rotation.h: interface for the CRotation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROTATION_H__632DF88A_6346_4486_8893_8A2F3F45951E__INCLUDED_)
#define AFX_ROTATION_H__632DF88A_6346_4486_8893_8A2F3F45951E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdlib.h>
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

	virtual	void	Initialize(IDirect3DDevice8 *pDevice, char CurrentDirectory[200], CAudio *pAudio);	// wczytaj dane
	virtual void	Initialize_Puzzle(IDirect3DDevice8 *pDevice, char CurrentDirectory[200], CAudio *pAudio);	// wczytaj dane
	
	virtual void	DeInitialize(void);				// usun dane

	// rysuje pojedyncza klatke i zwraca sygnal co dalej
	
	virtual int		DrawScene(long lTimer,float fMouseX, float fMouseY, 
					  bool bLeftButton, bool bRightButton, bool bCenterButton, CAudio *pAudio);		// rysuje pojedyncza klatke

private:

	bool	m_bActive;		// czy w pamieci znajduja sie dane

	CButton	*m_pExitButton;	// przycisk wyjscia 

	CSprite	*m_pBackground;	// tlo modulu

	CSprite *m_pKlocki[32];	// klocki do ukladanki

	CSprite *m_pRamka;		// gdzie jestesmy ? 

	CSprite *m_pMysticLogo;	// logo

	CFileSystem	*m_pFile;	// od razu bedziemy zamykac

	CSound	*m_pKlocekRuch;	// szuru bur

	unsigned char m_ucKlocki[28];	// plansza 7x4
	
	// 5 nie ruszaja sie
	// 8 w gore
	// 4 w lewo
	// 2 w dol
	// 6 w prawo 
	
	unsigned char m_ucKlockiRuch[28];

	char	m_cKlockiRuchOffset;	// ruch mozliwy tylko gdy rowny 0 

	long m_lLastTimer;	// ostatni timer

	unsigned char m_ucClickedKlocek;

};

#endif // !defined(AFX_ROTATION_H__632DF88A_6346_4486_8893_8A2F3F45951E__INCLUDED_)
