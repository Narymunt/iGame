// Player.h: interface for the Player class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYER_H__8DE23C12_0AC7_483F_BEDA_36A8A6DC2085__INCLUDED_)
#define AFX_PLAYER_H__8DE23C12_0AC7_483F_BEDA_36A8A6DC2085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <fox.h>

class Player  
{
public:
	Player(float fX, float fY);
	virtual ~Player();

	CSprite	*m_pFrames[4];

	float	m_fX;	// x na ekranie
	float	m_fY;	// y na ekranie

	float	m_fAddX;	// in/de krementator
	float	m_fAddY;	// in/de krementator

	float	m_fLastAddX;	// jaki byl ostatni ? potrzebne do stwierdzenia w ktora
	float	m_fLastAddY;	// strone ma kopac pilke

	float	m_fAngle;		// kat obrotu
	float	m_fKick;		// si³a uderzenia

	unsigned char m_ucCurrentFrame;	// aktualna klatka
};

#endif // !defined(AFX_PLAYER_H__8DE23C12_0AC7_483F_BEDA_36A8A6DC2085__INCLUDED_)
