// Sprite.h: interface for the CSprite class.
//
// zwykly duszek - jako jeden obiekt, jedna klatka
//////////////////////////////////////////////////////////////////////

#ifndef _GHOSTSPRITE_
#define _GHOSTSPRITE_

#include <windows.h>
#include <d3d8.h>
#include <d3dx8.h>

// dll interface
#pragma warning(disable: 4251)

class __declspec(dllexport) CSprite  
{

public:
	
	CSprite(unsigned char alpha, unsigned char r, unsigned char g, unsigned char b);
	virtual ~CSprite();

	virtual HRESULT		Initialize(char pCurrentDirectory[200],IDirect3DDevice8 *g_pDevice, char *path);
	virtual HRESULT		InitializeTGAinMemory(unsigned int *pSource, unsigned long m_ulSize, IDirect3DDevice8 *g_pDevice);
	virtual	HRESULT		InitializeTGAinMemoryEx(unsigned int *pSource, unsigned long m_ulSize, IDirect3DDevice8 *g_pDevice,
										 unsigned int uiWidth, unsigned int uiHeight, unsigned int MipLevels, 
										 DWORD dUsage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter, DWORD MipFilter, 
										 D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette);
	
	virtual HRESULT		Render();
	
	//-=- modulacja -=-

	virtual void		SetModulate(unsigned char alpha, unsigned char r, unsigned char g, unsigned char b);

	//-=- obr�t -=-

	virtual void		SetRotation(float newRotation);	// ustaw rotacje
	virtual void		SetRotationCenter(float x, float y); // ustaw punkt rotacji
	virtual float		GetRotation(void);				// pobierz rotacje
	virtual void		AddRotation(float addValue);	// dodaj lub odejmij 

	//-=- przesuni�cie -=-

	virtual void		SetTranslation(float x, float y);	// ustaw przesuniecie
	virtual float		GetTranslationX(void);
	virtual float		GetTranslationY(void);
	virtual void		AddTranslation(float x, float y);

	//-=- konwersje k�t�w -=-

	virtual float		GetDegree(float fVector);		// podaj w katach
	virtual float		GetRadian(float fVector);		// podaj w radianach

	//-=- skalowanie -=-

	virtual void		SetScale(float fValueX, float fValueY);	// ustaw skal� obiektu
	
	virtual void		SetScaleX(float fValueX);	// ustaw skal�
	virtual void		SetScaleY(float fValueY);

	virtual float		GetScaleX(void);	// pobierz wsp�rz�dne
	virtual float		GetScaleY(void);		

	virtual void		AddScale(float fValueX, float fValueY);	// dodaj skal�

	virtual void		AddScaleX(float fValueX);
	virtual void		AddScaleY(float fValueY);

	//=== widzialnosci

	virtual void		SetVisible(bool bState);
	virtual bool		GetVisible(void);

	//=== stan inicjalizacji (czy byl zainicjalizowany, czy tylko klasa)

	virtual void		SetState(bool bState);
	virtual bool		GetState(void);

	//=== do blokowania i rysowania bezposrednio na texturze

	virtual void		Lock(void);
	virtual void		Unlock(void);

	//=== rysowanie na zablokowanej texturze

	virtual void		Paint(int iX, int iY, int iA, int iR, int iG, int iB);

	LPD3DXSPRITE		m_pSprite;
	
	LPDIRECT3DTEXTURE8	m_pTexture;

	D3DLOCKED_RECT		LockedRect;	// do blokowania textury

	

private:

	DWORD				*m_pTextureBuffer;

	bool				m_bVisible;			// czy widoczny, czy ma byc renderowany
	
	D3DXVECTOR2			m_RotCenter;		// w pixelach
	D3DXVECTOR2			m_Translation;		// przesuniecie we float 
	D3DXVECTOR2			m_Scaling;			// scala we float 

	float				m_Rotation;			// we float
	
	D3DCOLOR			m_ModulateColor;	// color 

	bool				m_bInitialized;

};

#endif 
 