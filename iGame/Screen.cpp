#include "Screen.h"

CScreen::CScreen() : _window(NULL), _gl(NULL), _isSDS(false), _isSDW(false), _isHDS(false), _isHDW(false)
{
	int iOffsetX, iOffsetY;

	if (SDL_Init(SDL_INIT_VIDEO)!=0)
	{
		printf("ERROR: unable to init sdl video: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}

	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GetDisplayMode(0,0,&_mode);

//    SDL_DisplayMode displayMode;
//    SDL_GetDesktopDisplayMode(0, &displayMode);

	_iSizeX = _mode.w;
	_iSizeY = _mode.h;

	_fPixelRatio = (float)_iSizeX / (float)_iSizeY;
	_fReverseRatio = (float)_iSizeY / (float)_iSizeX;

	SDL_Log("Screen X: %d Y: %d\n",_iSizeX,_iSizeY);
	SDL_Log("Pixel ratio : %.2f (reverse: %.2f)\n", _fPixelRatio,_fReverseRatio);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
	_window = SDL_CreateWindow(NULL, 0, 0, _iSizeX, _iSizeY, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE);

	if (_window == 0)
	{
		SDL_Log("ERROR: Failed to create window.\n");
		SDL_Quit();
		return;
	}
    else
    {
        SDL_Log("Screen : %d x %d\n", _iSizeX, _iSizeY);        
    }

	_gl = SDL_GL_CreateContext(_window);

	glViewport(0, 0, _iSizeX, _iSizeY);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glOrthof(0.0f, _iSizeX, _iSizeY, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glDisable(GL_DEPTH_TEST);

    // wyliczanie punktow dla macierzy 4x4

    _iXA = 0; _iXC = _iSizeX/2; _iXB = _iXC/2; _iXD = _iXB+_iXC; _iXE = _iSizeX;
    _iYA = 0; _iYC = _iSizeY/2; _iYB = _iYC/2; _iYD = _iYB+_iYC; _iYE = _iSizeY;

    // wyliczanie punktow dla macierzy 16x16

    iOffsetX = _iSizeX / 16;
    iOffsetY = _iSizeY / 16;

	SDL_Log("Screen TILE X: %d Y: %d\n",iOffsetX,iOffsetY);

    if (_iSizeX < 1500)
    {
    	if (_fPixelRatio > _fReverseRatio)
    	{
    		(_fPixelRatio < 1.5f) ? _isSDS = true : _isSDW = true;
    	}
    	else
    	{
    		(_fReverseRatio < 1.5f) ? _isSDS = true : _isSDW = true;
    	}
    }
    else
    {
    	if (_fPixelRatio > _fReverseRatio)
    	{
    		(_fPixelRatio < 1.5f) ? _isHDS = true : _isHDW = true;
    	}
    	else
    	{
    		(_fReverseRatio < 1.5f) ? _isHDS = true : _isHDW = true;
    	}
    }

    if (_isSDS) SDL_Log("Resolution : SDS\n");
    if (_isSDW) SDL_Log("Resolution : SDW\n");
    if (_isHDS) SDL_Log("Resolution : HDS\n");
    if (_isHDW) SDL_Log("Resolution : HDW\n");

    _x0 = iOffsetX * 0 ;
    _x1 = iOffsetX * 1 ;
    _x2 = iOffsetX * 2 ;
    _x3 = iOffsetX * 3 ;
    _x4 = iOffsetX * 4 ;
    _x5 = iOffsetX * 5 ;
    _x6 = iOffsetX * 6 ;
    _x7 = iOffsetX * 7 ;
    _x8 = iOffsetX * 8 ;
    _x9 = iOffsetX * 9 ;
    _x10 = iOffsetX * 10 ;
    _x11 = iOffsetX * 11 ;
    _x12 = iOffsetX * 12 ;
    _x13 = iOffsetX * 13 ;
    _x14 = iOffsetX * 14 ;
    _x15 = iOffsetX * 15 ;
    _x16 = iOffsetX * 16 ;

    _y0 = iOffsetY * 0 ;
    _y1 = iOffsetY * 1 ;
    _y2 = iOffsetY * 2 ;
    _y3 = iOffsetY * 3 ;
    _y4 = iOffsetY * 4 ;
    _y5 = iOffsetY * 5 ;
    _y6 = iOffsetY * 6 ;
    _y7 = iOffsetY * 7 ;
    _y8 = iOffsetY * 8 ;
    _y9 = iOffsetY * 9 ;
    _y10 = iOffsetY * 10 ;
    _y11 = iOffsetY * 11 ;
    _y12 = iOffsetY * 12 ;
    _y13 = iOffsetY * 13 ;
    _y14 = iOffsetY * 14 ;
    _y15 = iOffsetY * 15 ;
    _y16 = iOffsetY * 16 ;

}

CScreen::~CScreen()
{
    SDL_GL_DeleteContext(_gl);
    SDL_DestroyWindow(_window);
}

void CScreen::Clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// You have to do this each frame, because SDL messes up with your GL context when drawing on-screen keyboard, however is saves/restores your matrices
     glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
     glEnable(GL_TEXTURE_2D);
	 glEnable(GL_BLEND);
	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void CScreen::Flip(void)
{
	SDL_GL_SwapWindow(_window);
}

float CScreen::fPositionX(float f)
{
	float x = (float)_iSizeX*(f/100.0f);
	return (int)x;
}

float CScreen::fPositionY(float f)
{
	float y = (float)_iSizeY*(f/100.0f);
}

int CScreen::ixSDStoSDW(int x)
{
	float f = ((float)x/(float)1024.0f) * 1366.0f;
	return (int)f;
}

int CScreen::ixSDStoHDS(int x)
{
	float f = ((float)x/(float)1024.0f) * 2048.0f;
	return (int)f;
}

int CScreen::ixSDStoHDW(int x)
{
	float f = ((float)x/(float)1024.0f) * 1920.0f;
	return (int)f;
}

int CScreen::ixSDWtoSDS(int x)
{
	float f = ((float)x/(float)1366.0f) * 1024.0f;
	return (int)f;
}

int CScreen::ixSDWtoHDS(int x)
{
	float f = ((float)x/(float)1366.0f) * 2048.0f;
	return (int)f;
}

int CScreen::ixSDWtoHDW(int x)
{
	float f = ((float)x/(float)1366.0f) * 1920.0f;
	return (int)f;
}

int CScreen::ixHDWtoSDS(int x)
{
	float f = ((float)x/(float)1920.0f) * 1024.0f;
	return (int)f;
}

int CScreen::ixHDWtoSDW(int x)
{
	float f = ((float)x/(float)1920.0f) * 1366.0f;
	return (int)f;
}

int CScreen::ixHDWtoHDS(int x)
{
	float f = ((float)x/(float)1920.0f) * 2048.0f;
	return (int)f;
}

int CScreen::ixHDStoSDS(int x)
{
	float f = ((float)x/(float)2048.0f) * 1024.0f;
	return (int)f;
}

int CScreen::ixHDStoSDW(int x)
{
	float f = ((float)x/(float)2048.0f) * 1366.0f;
	return (int)f;
}

int CScreen::ixHDStoHDW(int x)
{
	float f = ((float)x/(float)2048.0f) * 1920.0f;
	return (int)f;
}

int CScreen::iySDStoSDW(int y)
{
	return y;
}

int CScreen::iySDStoHDS(int y)
{
	float f = ((float)y/(float)768.0f) * 1536.0f;
	return (int)f;
}

int CScreen::iySDStoHDW(int y)
{
	float f = ((float)y/(float)768.0f) * 1080.0f;
	return (int)f;
}

int CScreen::iySDWtoSDS(int y)
{
	return y;
}

int CScreen::iySDWtoHDS(int y)
{
	float f = ((float)y/(float)768.0f) * 1536.0f;
	return (int)f;
}

int CScreen::iySDWtoHDW(int y)
{
	float f = ((float)y/(float)768.0f) * 1080.0f;
	return (int)f;
}

int CScreen::iyHDWtoSDS(int y)
{
	float f = ((float)y/(float)1080.0f) * 768.0f;
	return (int)f;
}

int CScreen::iyHDWtoSDW(int y)
{
	float f = ((float)y/(float)1080.0f) * 768.0f;
	return (int)f;
}

int CScreen::iyHDWtoHDS(int y)
{
	float f = ((float)y/(float)1080.0f) * 1536.0f;
	return (int)f;
}

int CScreen::iyHDStoSDS(int y)
{
	float f = ((float)y/(float)1536.0f) * 768.0f;
	return (int)f;
}

int CScreen::iyHDStoSDW(int y)
{
	float f = ((float)y/(float)1536.0f) * 768.0f;
	return (int)f;
}

int CScreen::iyHDStoHDW(int y)
{
	float f = ((float)y/(float)1536.0f) * 1080.0f;
	return (int)f;
}

int CScreen::iSDStoX(int x)
{
	float f = ((float)x/(float)1024.0f) * (float)_iSizeX;
	return (int)f;
}

int CScreen::iSDWtoX(int x)
{
	float f = ((float)x/(float)1366.0f) * (float)_iSizeX;
	return (int)f;
}

int CScreen::iHDStoX(int x)
{
	float f = ((float)x/(float)2048.0f) * (float)_iSizeX;
	return (int)f;
}

int CScreen::iHDWtoX(int x)
{
	float f = ((float)x/(float)1920.0f) * (float)_iSizeX;
	return (int)f;
}

int CScreen::iSDStoY(int y)
{
	float f = ((float)y/(float)768.0f) * (float)_iSizeX;
	return (int)f;
}

int CScreen::iSDWtoY(int y)
{
	float f = ((float)y/(float)768.0f) * (float)_iSizeX;
	return (int)f;
}

int CScreen::iHDStoY(int y)
{
	float f = ((float)y/(float)1536.0f) * (float)_iSizeX;
	return (int)f;
}

int CScreen::iHDWtoY(int y)
{
	float f = ((float)y/(float)1080.0f) * (float)_iSizeX;
	return (int)f;
}

int CScreen::iXtoSDS(int x)
{
	float f = ((float)x/(float)_iSizeX) * (float)1024.0f;
	return (int)f;
}

int CScreen::iXtoSDW(int x)
{
	float f = ((float)x/(float)_iSizeX) * (float)1366.0f;
	return (int)f;
}

int CScreen::iXtoHDS(int x)
{
	float f = ((float)x/(float)_iSizeX) * (float)2048.0f;
	return (int)f;
}

int CScreen::iXtoHDW(int x)
{
	float f = ((float)x/(float)_iSizeX) * (float)1920.0f;
	return (int)f;
}

int CScreen::iYtoSDS(int y)
{
	float f = ((float)y/(float)_iSizeY) * (float)768.0f;
	return (int)f;
}

int CScreen::iYtoSDW(int y)
{
	float f = ((float)y/(float)_iSizeY) * (float)768.0f;
	return (int)f;
}

int CScreen::iYtoHDS(int y)
{
	float f = ((float)y/(float)_iSizeY) * (float)1536.0f;
	return (int)f;
}

int CScreen::iYtoHDW(int y)
{
	float f = ((float)y/(float)_iSizeY) * (float)1080.0f;
	return (int)f;
}

void CScreen::RenderX(int i)
{
	int iOffsetX = _iSizeX / 16;

	_x0 = i + (iOffsetX*0);
	_x1 = i + (iOffsetX*1);
	_x2 = i + (iOffsetX*2);
	_x3 = i + (iOffsetX*3);
	_x4 = i + (iOffsetX*4);
	_x5 = i + (iOffsetX*5);
	_x6 = i + (iOffsetX*6);
	_x7 = i + (iOffsetX*7);
	_x8 = i + (iOffsetX*8);
	_x9 = i + (iOffsetX*9);
	_x10 = i + (iOffsetX*10);
	_x11 = i + (iOffsetX*11);
	_x12 = i + (iOffsetX*12);
	_x13 = i + (iOffsetX*13);
	_x14 = i + (iOffsetX*14);
	_x15 = i + (iOffsetX*15);
	_x16 = i + (iOffsetX*16);
}

void CScreen::RenderY(int i)
{
	int iOffsetY = _iSizeY / 16;

	_y0 = i + (iOffsetY*0);
	_y1 = i + (iOffsetY*1);
	_y2 = i + (iOffsetY*2);
	_y3 = i + (iOffsetY*3);
	_y4 = i + (iOffsetY*4);
	_y5 = i + (iOffsetY*5);
	_y6 = i + (iOffsetY*6);
	_y7 = i + (iOffsetY*7);
	_y8 = i + (iOffsetY*8);
	_y9 = i + (iOffsetY*9);
	_y10 = i + (iOffsetY*10);
	_y11 = i + (iOffsetY*11);
	_y12 = i + (iOffsetY*12);
	_y13 = i + (iOffsetY*13);
	_y14 = i + (iOffsetY*14);
	_y15 = i + (iOffsetY*15);
	_y16 = i + (iOffsetY*16);

}

