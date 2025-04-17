// Player.cpp: implementation of the Player class.
//
//////////////////////////////////////////////////////////////////////

#include "Player.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Player::Player(float fX, float fY)
{

	for (int iLicznik=0; iLicznik<4; iLicznik++)
	{
		m_pFrames[iLicznik]=new CSprite(255,255,255,255);
	}

	m_fX=fX; 
	m_fY=fY;
	
	m_fAddX=0; 
	m_fAddY=0;
	
	m_fAngle=0;

	m_ucCurrentFrame=0;

}

Player::~Player()
{
	for (int iLicznik=0; iLicznik<4; iLicznik++)
	{
		free(m_pFrames[iLicznik]);
	}
}
