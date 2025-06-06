// LoadScreen.h: interface for the CLoadScreen class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _RADIALZOOM_
#define _RADIALZOOM_

#include <windows.h>
#include <d3d8.h>
#include "Sprite.h"

class CRadialZoom
{
public:
	CRadialZoom();
	virtual ~CRadialZoom();

	virtual void SetActive(bool bState);
	virtual bool bGetActive(void);

	virtual void Initialize(IDirect3DDevice8 *pDevice);
	virtual void DeInitialize(void);

	virtual int	 DrawScene(long lTimer);

private:

	bool		m_bActive;
	
	CSprite		*m_pBackground;
	CSprite		*m_pFadeScreenIn;
	CSprite		*m_pFadeScreenOut;
	
	long		lLastTimer;

	float		dDa, dDb;	// dla petli

};

#endif 
