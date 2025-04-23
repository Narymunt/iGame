// implementation of class
// .bmp file is reversed, so at and we flip it

#include <stdlib.h>
#include <stdio.h>
#include "ButtonFlat.h"

//=== class constructor

CButtonFlat::CButtonFlat(int x, int y, char filename[], int xscreen, int yscreen)
{
    m_pImage = new CBitmap(x,y,filename);
    m_ulSizeX = x; // zapamietaj na potem
    m_ulSizeY = y;
    m_ulX = xscreen;
    m_ulY = yscreen;
}

//=== class destructor

CButtonFlat::~CButtonFlat()
{
    delete m_pImage;
}

int CButtonFlat::Render1280(int mousex, int mousey, bool bleft, bool bright, unsigned char *pBuffer)
{
	m_pImage->Render1280(m_ulX, m_ulY, pBuffer);
	
	if ((mousex>m_ulX)&&(mousex<(m_ulX+m_ulSizeX))&&
	    (mousey>m_ulY)&&(mousey<(m_ulY+m_ulSizeY))&& bleft
	   ) return 1;
	    else return 0;
}

// dla 1024x768

int CButtonFlat::Render(int mousex, int mousey, bool bleft, bool bright, unsigned char *pBuffer)
{
	m_pImage->Render(m_ulX, m_ulY, pBuffer);
	
	if ((mousex>m_ulX)&&(mousex<(m_ulX+m_ulSizeX))&&
	    (mousey>m_ulY)&&(mousey<(m_ulY+m_ulSizeY))&& bleft
	   ) return 1;
	    else return 0;

}
