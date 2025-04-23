// obsluga plikow .bmp 24-bitowych
// - dodac render_minus / render_scale_minus

#ifndef _IGAME__BITMAP_
#define _IGAME__BITMAP_

// jaka to bitmapa

#define 	BMP	1
#define		TGA	2

class CBitmap
{

    public:

	CBitmap();
	CBitmap(unsigned long size);	// bitmap size
	CBitmap(unsigned long size, char filename[]); // read bitmap
	CBitmap(long lX, long lY, char filename[]);
	CBitmap(char filename[],char cType);	// glownie dla .tga
	
	virtual ~CBitmap();

	// pobieranie danych z tablicy (akcesory)
	
	unsigned char ucGetDataR(int iIndex);
	unsigned char ucGetDataG(int iIndex);
	unsigned char ucGetDataB(int iIndex);
	unsigned char ucGetDataA(int iIndex);

	int		Render(int iX, int iY, int iXSize, int iYSize, double iXScale, double iYScale, unsigned char *pBuffer);
	int		Render(int iX, int iY, unsigned char *pBuffer);
	int		Render1280(int iX, int iY, unsigned char *pBuffer);

	int		RenderPlus(int iX, int iY, unsigned char *pBuffer);

	int		RenderScale(int iX, int iY, int iXSize, int iYSize, double dXScale, double dYScale, unsigned char *pBuffer);
	int		RenderScalePlus(int iX, int iY, int iXSize, int iYSize, double dXScale, double dYScale, unsigned char *pBuffer);

	// ustawianie rozmiarow bitmapy

	void	SetSizeX(unsigned long ulX);
	unsigned long ulGetSizeX(void);
	
	void	SetSizeY(unsigned long ulY);
	unsigned long ulGetSizeY(void);
	
    protected:

	unsigned char	*m_pBitmapDataR;	// dane bitmapy
	unsigned char	*m_pBitmapDataG;	// dane bitmapy
	unsigned char	*m_pBitmapDataB;	// dane bitmapy
	unsigned char 	*m_pBitmapDataA;	// alfa, nie odczytywana z plikow bmp

	unsigned long	m_ulSizeX;	// rozmiary
	unsigned long	m_ulSizeY;	
	
	
};

#endif
