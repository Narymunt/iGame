
// klasyczny tunel

#ifndef _IGAME__PINCH_
#define _IGAME__PINCH_

#include "iGame.h"


class CPinch
{

    public:
	CPinch(unsigned int uiXSize, unsigned int uiYSize, char cXTable[], char cYTable[], char cTexture[]);
	~CPinch();
	
	virtual void IncX(char ucVal);	// zwieksza wskazniki a nie rozmiary
	virtual void IncY(char ucVal);
	
	virtual void Render(unsigned char *pBuffer);
	
    protected:
    
	unsigned int	m_uiXSize;	// rozmiary
	unsigned int	m_uiYSize;
	
	unsigned char	*m_pXTable;	// dane do pincha
	unsigned char 	*m_pYTable;

	CBitmap		*m_pTexture;	// textura zawsze 256x256

};

#endif
