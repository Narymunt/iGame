// Ball.h: interface for the Ball class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BALL_H__06025F72_BE32_46D1_BCC8_8E78533706D2__INCLUDED_)
#define AFX_BALL_H__06025F72_BE32_46D1_BCC8_8E78533706D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <fox.h>

class Ball  
{
public:
	Ball();
	virtual ~Ball();




	CSprite		*m_pFrames[4];		// klatki animacji

	float		m_fBallX, m_fBallY, m_fBallZ;
	float		m_fBallAddX, m_fBallAddY, m_fBallAddZ;

	unsigned char	m_ucCurrentFrame;		
	

};

#endif // !defined(AFX_BALL_H__06025F72_BE32_46D1_BCC8_8E78533706D2__INCLUDED_)
