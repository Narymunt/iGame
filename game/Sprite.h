// Sprite.h: interface for the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRITE_H__112B0E16_0F42_4598_8CC8_8FD2A8E5D834__INCLUDED_)
#define AFX_SPRITE_H__112B0E16_0F42_4598_8CC8_8FD2A8E5D834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <d3d8.h>
#include <d3dx8.h>

class CSprite  
{
public:
	CSprite();
	virtual ~CSprite();

	HRESULT				Initialize(IDirect3DDevice8 *g_pDevice, char *path);
	HRESULT				Render();

	D3DXVECTOR2			m_RotCenter;		// w pixelach
	D3DXVECTOR2			m_Translation;		// przesuniecie we float 
	D3DXVECTOR2			m_Scaling;			// scala we float 
	
	float				m_Rotation;			// we float
	
	D3DCOLOR			m_ModulateColor;	// color 
	
	LPD3DXSPRITE		m_pSprite;
	
	LPDIRECT3DTEXTURE8	m_pTexture;
	
	BOOL				m_bInitialized;

};

#endif // !defined(AFX_SPRITE_H__112B0E16_0F42_4598_8CC8_8FD2A8E5D834__INCLUDED_)
