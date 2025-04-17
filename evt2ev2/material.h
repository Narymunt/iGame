#ifndef	__MATERIAL_H_
#define __MATERIAL_H_

#include <d3dx8.h>

enum G3DMATERIAL_FLAGS
{
	FLAG_MULTITEXT			= 1,
	FLAG_TEXTUREMODULATE	= 2,
	FLAG_ALPHABLEND			= 4,		
	FLAG_TEXTUREALPHA		= 16,
	FLAG_ENVONLY			= 32,
	FLAG_NOTEXT				= 64,
	FLAG_ENVALPHA			= 128,	
	FLAG_TEXTUREBLEND		= 256,
	FLAG_TEXTUREBLENDADD	= 512,
	FLAG_WRAPU				= 1024,
	FLAG_WRAPV				= 2048,	
	FLAG_MATERIAL_DWORD		= 0x7fffffff
};

enum G3DMATERIAL_ALPHAOP
{
	ALPHAOP_ADD,
	ALPHAOP_LINEAR,
	ALPHAOP_ONE	
};

class G3D_CScene;
class G3D_CMaterial
{
protected:

	DWORD					dwPrevCull;

public:

	G3D_CScene*			pScene;	

	DWORD					dwFlags;	
	DWORD					dwAlphaOp;

	FLOAT					a;
	FLOAT					r;
	FLOAT					g;
	FLOAT					b;

	char*					strTextureName;
	char*					strEnvTextName;

public:

	G3D_CMaterial( G3D_CScene* scene ) : pScene( scene ), dwFlags( 0 ), 
										   a( 0.0f ), r(1.0f), g(1.0f), b(1.0f), 
										   strTextureName(NULL), 
										   strEnvTextName(NULL)
	{
	}

	virtual ~G3D_CMaterial()
	{
		delete strTextureName;
		delete strEnvTextName;
	}

	virtual void ApplyMaterial();
	virtual void RestoreMaterial();
};

class G3D_CRenderedMaterial : public G3D_CMaterial
{
protected:

	PDIRECT3DSURFACE8		psPrevTarget;
	PDIRECT3DSURFACE8		psPrevZBuffer;
	
	DWORD					dwPrevAmbient;		
	DWORD					dwOwnZBuffer;

public:
	
	PDIRECT3DTEXTURE8		ptexText;
	PDIRECT3DSURFACE8		psZBuffer;	
	
public:

	G3D_CRenderedMaterial( G3D_CScene* scene, DWORD width = 640, DWORD height = 480, PDIRECT3DSURFACE8 zbuffer = NULL );
	virtual ~G3D_CRenderedMaterial();	
	
	virtual void ApplyMaterial();	
	virtual void RestoreMaterial();	
		
	void SetRenderTarget();	
	void RestoreRenderTarget();	
};


#endif


