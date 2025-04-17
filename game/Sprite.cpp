// Sprite.cpp: implementation of the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#include "Sprite.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// TODO:
// - jaytee twierdzi, ze przy render sprite wystarczy begin dla pierwszego sprite'a

// stworz obiekt 

CSprite::CSprite(unsigned char alpha, unsigned char r, unsigned char g, unsigned char b)
{
	m_pSprite = 0;
	m_pTexture = 0;
	
	m_bInitialized = false;
	
	m_RotCenter.x = 0.0f;
	m_RotCenter.y = 0.0f;
	
	m_Translation.x = 0.0f;
	m_Translation.y = 0.0f;
	
	m_Scaling.x = 1.0f;
	m_Scaling.y = 1.0f;
	
	m_ModulateColor = D3DCOLOR_ARGB(alpha,r,g,b);	// lub RGBA
	
	m_Rotation = 0.0f;
}

// usun obiekt

CSprite::~CSprite()
{
	if(m_pSprite)	m_pSprite->Release();
}

// stworz ze zwyklego pliku

HRESULT CSprite::Initialize(IDirect3DDevice8 *g_pDevice, char *path)
{
	HRESULT hr = 0;

	hr = D3DXCreateTextureFromFile(g_pDevice, path, &m_pTexture);

	D3DXCreateSprite(g_pDevice, &m_pSprite);

	m_bInitialized = TRUE;

	return S_OK;
}

// wyswietl sprite 

HRESULT CSprite::Render()
{
	if(!m_bInitialized)	return E_FAIL;

	HRESULT hr = 0;

	m_pSprite->Begin();

	hr = m_pSprite->Draw(m_pTexture, NULL,
						 &m_Scaling, &m_RotCenter, m_Rotation, &m_Translation, 
						 m_ModulateColor);

	m_pSprite->End();
	
	return S_OK;
}

