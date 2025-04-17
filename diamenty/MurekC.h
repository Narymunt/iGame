// MurekC.h: interface for the MurekC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUREKC_H__0FBA854D_670A_4277_BA02_4C80C30FA548__INCLUDED_)
#define AFX_MUREKC_H__0FBA854D_670A_4277_BA02_4C80C30FA548__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fox.h>

class MurekC  
{
public:
	MurekC();
	virtual ~MurekC();
	put(unsigned int x, unsigned int y, FOX_Surface *destination);

	unsigned char	*image_r;		// dane
	unsigned char	*image_g;	
	unsigned char	*image_b;
	unsigned char	*image_a;
};

#endif // !defined(AFX_MUREKC_H__0FBA854D_670A_4277_BA02_4C80C30FA548__INCLUDED_)
