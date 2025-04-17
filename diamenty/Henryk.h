// Henryk.h: interface for the Henryk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HENRYK_H__9A33E06A_3FAD_4297_A788_57F759441A9A__INCLUDED_)
#define AFX_HENRYK_H__9A33E06A_3FAD_4297_A788_57F759441A9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <FOX.h>
// szczurek, glowna postac

class Henryk  
{
public:
	Henryk();
	virtual ~Henryk();

	put_Henryk(unsigned int x, unsigned int y, FOX_Surface *destination, FOX_Surface *back);

	unsigned int	x_global;		// pozycja w jaskini
	unsigned int	y_global;		// pozycja w jaskini	

	unsigned int	dst_x_global;	// cel
	unsigned int	dst_y_global;	// cel

	int 			ile_stoi;		// jak dlugo ten matol stoi

	char			x_local;		// pozycja na kratkach
	char			y_local;		// pozycja na kratkach

	unsigned char	*lewo_r[6];		// idzie w lewo
	unsigned char	*lewo_g[6];	
	unsigned char	*lewo_b[6];
	unsigned char	*lewo_a[6];

	unsigned char	*prawo_r[6];		// idzie w prawo
	unsigned char	*prawo_g[6];
	unsigned char	*prawo_b[6];
	unsigned char	*prawo_a[6];

	unsigned char	*stoi_r;			// stoi
	unsigned char	*stoi_g;
	unsigned char	*stoi_b;
	unsigned char	*stoi_a;

	unsigned char	*gora_r[4];		// idzie do gory
	unsigned char	*gora_g[4];
	unsigned char	*gora_b[4];
	unsigned char	*gora_a[4];

	unsigned char	*dol_r[4];		// idzie w dol
	unsigned char	*dol_g[4];
	unsigned char	*dol_b[4];
	unsigned char	*dol_a[4];

//	unsigned char	*dlubie[9];		// dlubie sobie w nosie
//	unsigned char	*macha[13];		// macha reka

	unsigned char	*buffer_r;		// tutaj rysujemy
	unsigned char	*buffer_g;
	unsigned char	*buffer_b;
	unsigned char	*buffer_a;

};

#endif // !defined(AFX_HENRYK_H__9A33E06A_3FAD_4297_A788_57F759441A9A__INCLUDED_)
