// Sprite.cpp: implementation of the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#include "Sprite.h"
#include "Debug.h"
#include <iostream.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//=== inicjalizacja obiektu

CSprite::CSprite(unsigned char alpha, unsigned char r, unsigned char g, unsigned char b)
{
	m_pSprite = 0;
	m_pTexture = 0;
	
	m_bInitialized = false;
	m_bVisible = true;

	m_RotCenter.x = 0.0f;
	m_RotCenter.y = 0.0f;
	
	m_Translation.x = 0.0f;
	m_Translation.y = 0.0f;
	
	m_Scaling.x = 1.0f;
	m_Scaling.y = 1.0f;
	
	m_ModulateColor = D3DCOLOR_ARGB(alpha,r,g,b);	// lub RGBA
	
	m_Rotation = 0.0f;

	m_pSprite = NULL;	// nie aktywny
	m_pTexture = NULL;

}

//=== usuniecie obiektu

CSprite::~CSprite()
{
	if (m_pSprite!=NULL)	// usuwamy jezeli zaalokowany
	{
		m_pSprite->Release();
		m_pSprite = NULL;
	}

	if (m_pTexture!=NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=== inicjalizuj obiekt - stworz ze zwyklego pliku

HRESULT CSprite::Initialize(char *path,IDirect3DDevice8 *g_pDevice)
{
	char bufor[512];
	char CurrentDirectory[512];
	
	GetCurrentDirectory(sizeof(CurrentDirectory), CurrentDirectory);
	
	wsprintf(bufor, "%s\\%s", CurrentDirectory,path);

#if (DEBUG==1)
	cout<<"- initialize sprite :"<<bufor<<endl;
#endif

	HRESULT hr = 0;

	hr = D3DXCreateTextureFromFile(g_pDevice, bufor, &m_pTexture);

	D3DXCreateSprite(g_pDevice, &m_pSprite);

	m_bInitialized = TRUE;

	return S_OK;
}

//=== inicjalizuj obiekt, stworz ze zwyklego pliku, ale parametry textury podaj recznie

HRESULT	CSprite::InitializeEx(char *path, IDirect3DDevice8 *g_pDevice, unsigned int uiWidth, unsigned int uiHeight,
							  unsigned int MipLevels, DWORD dUsage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter, DWORD MipFilter, 
							  D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette)
{
	char bufor[512];
	char CurrentDirectory[512];
	
	GetCurrentDirectory(sizeof(CurrentDirectory), CurrentDirectory);
	
	wsprintf(bufor, "%s\\%s", CurrentDirectory,path);

#if (DEBUG==1)
	cout<<"- initialize spriteEX :"<<bufor<<endl;
#endif

	HRESULT hr = 0;

	hr = D3DXCreateTextureFromFileEx(g_pDevice, bufor, uiWidth, uiHeight, MipLevels, dUsage,
											Format, Pool, Filter, MipFilter, ColorKey, pSrcInfo, pPalette, &m_pTexture);

	D3DXCreateSprite(g_pDevice, &m_pSprite);

	m_bInitialized = TRUE;
	
	return S_OK;
}

//=== inicjalizuj obiekt, kt�ry jest ju� w pami�ci jako TGA

HRESULT CSprite::InitializeTGAinMemory(unsigned int *pSource, unsigned long m_ulSize, IDirect3DDevice8 *g_pDevice)
{
	
	HRESULT hr = 0;
	
	hr = D3DXCreateTextureFromFileInMemory(g_pDevice, pSource, m_ulSize, &m_pTexture);

	D3DXCreateSprite(g_pDevice, &m_pSprite);

	m_bInitialized = TRUE;

	return S_OK;
}

//=== inicjalizuj obiekt, wszystkie parametry podajemy recznie

HRESULT CSprite::InitializeTGAinMemoryEx(unsigned int *pSource, unsigned long m_ulSize, IDirect3DDevice8 *g_pDevice,
										 unsigned int uiWidth, unsigned int uiHeight, unsigned int MipLevels, 
										 DWORD dUsage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter, DWORD MipFilter, 
										 D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette)
{
	HRESULT hr=0;

	hr = D3DXCreateTextureFromFileInMemoryEx(g_pDevice, pSource, m_ulSize, uiWidth, uiHeight, MipLevels, dUsage,
											Format, Pool, Filter, MipFilter, ColorKey, pSrcInfo, pPalette, &m_pTexture);

	D3DXCreateSprite(g_pDevice, &m_pSprite);

	m_bInitialized = TRUE;

	return S_OK;
}

//=== renderuj sprite

HRESULT CSprite::Render()
{
	if (!m_bInitialized)	return E_FAIL;

	if (m_bVisible == false) return S_OK;	// po prostu nie rysuje niewidocznego

	HRESULT hr = 0;

	m_pSprite->Begin();

	hr = m_pSprite->Draw(m_pTexture, NULL,
						 &m_Scaling, &m_RotCenter, m_Rotation, &m_Translation, 
						 m_ModulateColor);

	m_pSprite->End();
	
	return S_OK;
}

//=== ustaw rotacje

void CSprite::SetRotation(float newRotation)
{
	m_Rotation = newRotation;
}
	
//=== pobierz rotacje

float CSprite::GetRotation(void)
{
	return m_Rotation;
}

//=== dodaj lub odejmij rotacje

void CSprite::AddRotation(float addValue)
{
	m_Rotation+=addValue;
}

//=== ustaw przesuniecie obiektu

void CSprite::SetTranslation(float x, float y)
{
	m_Translation.x = x;
	m_Translation.y = y;
}

//=== pobierz przesuniecie x

float CSprite::GetTranslationX(void)
{
	return m_Translation.x;
}

//=== pobierz przesuniecie y

float CSprite::GetTranslationY(void)
{
	return m_Translation.y;
}

//=== dodaj lub odejmij przesuniecie

void CSprite::AddTranslation(float x, float y)
{
	m_Translation.x += x;
	m_Translation.y += y;
}

//=== ustaw punkt rotacji w obiekcie

void CSprite::SetRotationCenter(float x, float y)
{
	m_RotCenter.x = x;
	m_RotCenter.y = y;
}

//=== zwroc wartosc kata w stopniach

float CSprite::GetDegree(float fVector)
{
	return D3DXToDegree(fVector);// * (180.0f / D3DX_PI));
}

//=== zwroc wartosc kata w radianach

float CSprite::GetRadian(float fVector)
{
	return D3DXToRadian((fVector) * (D3DX_PI / 180.0f));
}

//=== ustaw skal� obiektu

void CSprite::SetScale(float fValueX, float fValueY)
{
	m_Scaling.x=fValueX;
	m_Scaling.y=fValueY;
}

//=== ustaw skal� obiektu - stretching

void CSprite::SetScaleX(float fValueX)
{
	m_Scaling.x=fValueX;
}

//=== ustaw skal� obiektu - stretching

void CSprite::SetScaleY(float fValueY)
{
	m_Scaling.y=fValueY;
}

//=== pobierz skal� X

float CSprite::GetScaleX(void)
{
	return m_Scaling.x;
}

//=== pobierz skal� Y
	
float CSprite::GetScaleY(void)
{
	return m_Scaling.y;
}

//=== dodaj skal�

void CSprite::AddScale(float fValueX, float fValueY)
{
	m_Scaling.x += fValueX;
	m_Scaling.y += fValueY;
}

//=== dodaj skal� X

void CSprite::AddScaleX(float fValueX)
{
	m_Scaling.x += fValueX;
}

//=== dodaj skal� Y

void CSprite::AddScaleY(float fValueY)
{
	m_Scaling.y += fValueY;
}

//=== ustawia widocznosc ===

void CSprite::SetVisible(bool bState)
{
	m_bVisible = bState;
}

//=== zwraca znacznik widocznosci ===

bool CSprite::GetVisible(void)
{
	return m_bVisible; 
}

//=== stan inicjalizacji (czy byl zainicjalizowany, czy tylko klasa)

void CSprite::SetState(bool bState)
{
	// ta klasa nigdy nie powinna byc wywolywana
	// inicjalizacja powinna byc poprzez InitializeTGAInMemory
	
	m_bInitialized = bState;
}

//=== sprawdz czy zainicjalizowany

bool CSprite::GetState(void)
{
	return m_bInitialized;
}

//=== ustaw modulacje

void CSprite::SetModulate(unsigned char alpha, unsigned char r, unsigned char g, unsigned char b)
{
	m_ModulateColor = D3DCOLOR_ARGB(alpha,r,g,b);	// lub RGBA
}

// end