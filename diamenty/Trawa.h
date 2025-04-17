// Trawa.h: interface for the Trawa class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAWA_H__5259DAFA_175E_4B6A_896B_AAF52E2296C6__INCLUDED_)
#define AFX_TRAWA_H__5259DAFA_175E_4B6A_896B_AAF52E2296C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <FOX.h>

class Trawa  
{
public:
	Trawa();
	virtual ~Trawa();
	put_Trawa(unsigned int x, unsigned int y, FOX_Surface *destination);

	unsigned char	*image_r;		// rysunek trawy
	unsigned char	*image_g;
	unsigned char	*image_b;
	unsigned char	*image_a;


};

#endif // !defined(AFX_TRAWA_H__5259DAFA_175E_4B6A_896B_AAF52E2296C6__INCLUDED_)
