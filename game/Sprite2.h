// Sprite2.h: interface for the CSprite2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRITE2_H__C2FFEDCB_DC17_40DD_96C3_4CF5DDAB303C__INCLUDED_)
#define AFX_SPRITE2_H__C2FFEDCB_DC17_40DD_96C3_4CF5DDAB303C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <d3d8.h>
#include <d3dx8.h>

class CSprite2  
{
public:
	CSprite2(unsigned char alpha, unsigned char r, unsigned char g, unsigned char b);
	virtual ~CSprite2();

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

#endif // !defined(AFX_SPRITE2_H__C2FFEDCB_DC17_40DD_96C3_4CF5DDAB303C__INCLUDED_)
