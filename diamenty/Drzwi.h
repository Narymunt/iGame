// Drzwi.h: interface for the Drzwi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRZWI_H__7094B90B_F4BC_4FF0_A987_9ED0CF37A6D8__INCLUDED_)
#define AFX_DRZWI_H__7094B90B_F4BC_4FF0_A987_9ED0CF37A6D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fox.h>
#include <windows.h>

class Drzwi  
{
public:
	Drzwi();
	virtual ~Drzwi();

	put(int frame,unsigned int x, unsigned int y, FOX_Surface *destination);

	unsigned char	*image_r[3];		// rysunek 48*48
	unsigned char	*image_g[3];		
	unsigned char	*image_b[3];
	unsigned char	*image_a[3];	

	unsigned long	x_global;
	unsigned long	y_global;

};

#endif // !defined(AFX_DRZWI_H__7094B90B_F4BC_4FF0_A987_9ED0CF37A6D8__INCLUDED_)
