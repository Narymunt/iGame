// Ball.cpp: implementation of the Ball class.
//
//////////////////////////////////////////////////////////////////////

#include "Ball.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ball::Ball()
{
	for (int iLicznik=0; iLicznik<4; iLicznik++)
	{
		m_pFrames[iLicznik]=new CSprite(255,255,255,255);
	}

	m_fBallX=400-32; 
	m_fBallY=300-32;

	m_fBallAddX=0;
	m_fBallAddY=0;

	m_ucCurrentFrame=0;

}

Ball::~Ball()
{
	for (int iLicznik=0; iLicznik<4; iLicznik++)
	{
		free(m_pFrames[iLicznik]);
	}
}
