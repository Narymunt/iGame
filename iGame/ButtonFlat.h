// plaski przycisk, wlasciwie tylko obszar do naciskania
// zwraca 1 jezeli klikniety, 0 jezeli nie klikniety

#ifndef _IGAME__BUTTONFLAT_
#define _IGAME__BUTTONFLAT_

#include "Bitmap.h"

class CButtonFlat
{

    public:

	CButtonFlat(int x, int y, char filename[], int xscreen, int yscreen);
        CButtonFlat(char cScriptFile[]);    // inicjalizacja ze skryptu
        virtual ~CButtonFlat();

	int		Render(int mousex, int mousey, bool bleft, bool bright, unsigned char *pBuffer);
	int		Render1280(int mousex, int mousey, bool bleft, bool bright, unsigned char *pBuffer);
	
	void	UpOnly(char str[]);
	
    protected:

	CBitmap		*m_pImage;	// obrazek, tak wyglada przycisk

	char			m_cName[256];	// nazwa

	unsigned long	m_ulSizeX;	// rozmiary
	unsigned long	m_ulSizeY;	

	unsigned long	m_ulX1;
	unsigned long	m_ulY1;
	unsigned long 	m_ulX2;
	unsigned long	m_ulY2;	
	
};

#endif
