// Diament.h: interface for the Diament class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAMENT_H__FEE806F7_B95F_4C46_947C_97C84C1C6FEB__INCLUDED_)
#define AFX_DIAMENT_H__FEE806F7_B95F_4C46_947C_97C84C1C6FEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <FOX.h>

class Diament  
{
public:
	Diament();
	virtual ~Diament();

	put(int frame,unsigned int x, unsigned int y, FOX_Surface *destination, FOX_Surface *back);

	unsigned char	*image_r[5];		// rysunek 48*48
	unsigned char	*image_g[5];		
	unsigned char	*image_b[5];
	unsigned char	*image_a[5];	

	unsigned int	x_global;			// pozycja w jaskini
	unsigned int	y_global;			// pozycja w jaskini	

	unsigned int	dst_x_global;		// cel
	unsigned int	dst_y_global;		// cel

	char			x_local;			// pozycja na kratkach
	char			y_local;			// pozycja na kratkach


};

#endif // !defined(AFX_DIAMENT_H__FEE806F7_B95F_4C46_947C_97C84C1C6FEB__INCLUDED_)
