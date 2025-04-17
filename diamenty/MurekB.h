// MurekB.h: interface for the MurekB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUREKB_H__7F7762B9_52DB_4343_938C_EFEB06023825__INCLUDED_)
#define AFX_MUREKB_H__7F7762B9_52DB_4343_938C_EFEB06023825__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fox.h>

class MurekB  
{
public:
	MurekB();
	virtual ~MurekB();

	put(unsigned int x, unsigned int y, FOX_Surface *destination);

	unsigned char	*image_r;		// dane
	unsigned char	*image_g;	
	unsigned char	*image_b;
	unsigned char	*image_a;



};

#endif // !defined(AFX_MUREKB_H__7F7762B9_52DB_4343_938C_EFEB06023825__INCLUDED_)
