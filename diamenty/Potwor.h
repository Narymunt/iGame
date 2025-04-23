// Potwor.h: interface for the Potwor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POTWOR_H__390E5326_01A6_46AF_B201_AB6E87CA5FE0__INCLUDED_)
#define AFX_POTWOR_H__390E5326_01A6_46AF_B201_AB6E87CA5FE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fox.h>
#include <windows.h>

class Potwor  
{
public:
	Potwor();
	virtual ~Potwor();

	put(unsigned int frame, unsigned int x, unsigned int y, FOX_Surface *destination, FOX_Surface *back);

	unsigned int	x_global;		// pozycja w jaskini
	unsigned int	y_global;		// pozycja w jaskini	

	unsigned int	dst_x_global;	// cel
	unsigned int	dst_y_global;	// cel

	char			x_local;		// pozycja na kratkach
	char			y_local;		// pozycja na kratkach

	unsigned char	*lewo_r[5];		// idzie w lewo
	unsigned char	*lewo_g[5];	
	unsigned char	*lewo_b[5];
	unsigned char	*lewo_a[5];

	unsigned char	*prawo_r[5];		// idzie w prawo
	unsigned char	*prawo_g[5];
	unsigned char	*prawo_b[5];
	unsigned char	*prawo_a[5];

	unsigned char	*gora_r[4];		// idzie do gory
	unsigned char	*gora_g[4];
	unsigned char	*gora_b[4];
	unsigned char	*gora_a[4];

	unsigned char	*dol_r[4];		// idzie w dol
	unsigned char	*dol_g[4];
	unsigned char	*dol_b[4];
	unsigned char	*dol_a[4];

	unsigned char	*buffer_r;		// tutaj rysujemy
	unsigned char	*buffer_g;
	unsigned char	*buffer_b;
	unsigned char	*buffer_a;

	unsigned char 	ostatni_ruch;		// czy ostatnio w lewo czy w prawo?

};

#endif // !defined(AFX_POTWOR_H__390E5326_01A6_46AF_B201_AB6E87CA5FE0__INCLUDED_)
