// Sprite2.cpp: implementation of the CSprite2 class.
//
//////////////////////////////////////////////////////////////////////

#include "Sprite2.h"
#include <windows.h>
#include <stdio.h>
#include <d3d8.h>
#include <d3dx8.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// konstruktor

CSprite2::CSprite2(unsigned char alpha, unsigned char r, unsigned char g, unsigned char b)
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

// destruktor

CSprite2::~CSprite2()
{
	if(m_pSprite)	m_pSprite->Release();
}

// stworz ze zwyklego pliku

HRESULT CSprite2::Initialize(IDirect3DDevice8 *g_pDevice, char *path)
{
	HRESULT hr = 0;

	FILE *plik;
	unsigned int *bufor;

	bufor = (unsigned int*) malloc(12773);

	plik = fopen ("alien.tga","rb");
	fread(bufor,12773,1,plik);
	fclose(plik);

	//hr = D3DXCreateTextureFromFile(g_pDevice, path, &m_pTexture);

	hr = D3DXCreateTextureFromFileInMemory(g_pDevice, bufor, 12773, &m_pTexture);

	D3DXCreateSprite(g_pDevice, &m_pSprite);

	m_bInitialized = TRUE;

	free(bufor);

	return S_OK;
}

// wyswietl sprite 

HRESULT CSprite2::Render()
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

