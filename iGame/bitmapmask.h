// bitmap mask, 8bpp mask 

#ifndef _IGAME__BITMAPMASK_
#define _IGAME__BITMAPMASK_

class CBitmapMask
{
    public:
	CBitmapMask();
	CBitmapMask(unsigned long size);	// od razu alokuj pamiec
	CBitmapMask(unsigned long size, char filename[]);	// wczytaj z pliku

	virtual ~CBitmapMask();

	protected:

	unsigned char	*m_pBitmapMaskData;
};

#endif
