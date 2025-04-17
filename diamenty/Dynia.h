// Dynia.h: interface for the Dynia class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNIA_H__AD8AAA65_761A_4CD2_85A0_4E74E084D555__INCLUDED_)
#define AFX_DYNIA_H__AD8AAA65_761A_4CD2_85A0_4E74E084D555__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <FOX.h>

class Dynia  
{
public:
	Dynia();
	virtual ~Dynia();

	put(unsigned int x, unsigned int y, FOX_Surface *destination, FOX_Surface *back);

	unsigned char	*image_r[6];	
	unsigned char	*image_g[6];
	unsigned char	*image_b[6];
	unsigned char	*image_a[6];

	unsigned int	x_global;			// pozycja w jaskini
	unsigned int	y_global;			// pozycja w jaskini	

	unsigned int	dst_x_global;		// cel
	unsigned int	dst_y_global;		// cel

	char			x_local;			// pozycja na kratkach
	char			y_local;			// pozycja na kratkach

};

#endif // !defined(AFX_DYNIA_H__AD8AAA65_761A_4CD2_85A0_4E74E084D555__INCLUDED_)
