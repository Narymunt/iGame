// plaski przycisk, wlasciwie tylko obszar do naciskania
// zwraca 1 jezeli klikniety, 0 jezeli nie klikniety

#ifndef _IGAME__BUTTONFLAT_
#define _IGAME__BUTTONFLAT_

#include "bitmap.h"

class CButtonFlat
{

    public:

	CButtonFlat(int x, int y, char filename[], int xscreen, int yscreen);
	virtual ~CButtonFlat();

//	int		Render(int mousex, int mousey, unsigned char *pBuffer);
	int		Render1280(int mousex, int mousey, bool bleft, bool bright, unsigned char *pBuffer);
	
    protected:

	CBitmap		*m_pImage;

	unsigned long	m_ulSizeX;	// rozmiary
	unsigned long	m_ulSizeY;	

	unsigned long	m_ulX;
	unsigned long	m_ulY;	
	
};

#endif
