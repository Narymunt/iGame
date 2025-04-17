// Direct3D.h: interface for the CDirect3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECT3D_H__2EA60A8F_CAF8_4E3F_96E6_31CFE8E15829__INCLUDED_)
#define AFX_DIRECT3D_H__2EA60A8F_CAF8_4E3F_96E6_31CFE8E15829__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <d3d8.h>
#include <windows.h>
#include "Window.h"		// obsluga okna

class CDirect3D  
{
public:
	
	CDirect3D(CWindow *fp_pWindow);
	virtual ~CDirect3D();

	bool				Release();

	virtual void		Clear(DWORD dwColor);
	virtual void		Present(void);
	virtual void		BeginScene(void);
	virtual void		EndScene(void);

	CWindow				*pWindow;
	
	IDirect3D8			*pDirect3D;
	IDirect3DDevice8	*pDevice;
};

#endif // !defined(AFX_DIRECT3D_H__2EA60A8F_CAF8_4E3F_96E6_31CFE8E15829__INCLUDED_)
