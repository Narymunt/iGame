// konfiguracja ekranu urzadzenia
// SDS = soft def. square = dla rozdzielczosci <1500px przy pixel ratio < 1.5 (kwadratowe, np. 1024x768)
// SDW = soft def. wide = dla rozdzielczosci <1500px przy pixel ratio >1.5 (szerokie np. 1366x768, 1280x600)
// HDS = high def. square = dla rozdzielczosci >=1500px przy pixel ratio >1.5 (kwadratowe np. 2048x1536)
// HDW = high def. square = dla rozdzielczosci >=1500px przy pidel ratio > 1.5 (szerowkie np. 1920x1080)
//
// rozdzielczosci bazowe
// SDS - 1024x768
// SDW - 1366x768
// HDS - 2048x1536
// HDW - 1920x1080

#pragma once

#include <vector>
#include "SDL.h"
#include "OGL.h"


class CScreen
{

public : 

	CScreen();								// init screen with desktop resolution
	~CScreen();

	void			Clear(void);
	void			Flip(void);

	inline int		iSizeX(void) { return _iSizeX; }
	inline int		iSizeY(void) { return _iSizeY; 	}

	inline bool		isSDS(void) { return _isSDS; }
	inline bool		isSDW(void) { return _isSDW; }
	inline bool		isHDS(void) { return _isHDS; }
	inline bool		isHDW(void) { return _isHDW; }

	inline float	fPixelRatio(void) { return _fPixelRatio; }
	inline float 	fReverseRatio(void) { return _fReverseRatio; }

	float			fPositionX(float f);	// zwracamy wsp—¸rz«dne w pixelach przy podaniu parametru w procentach 0-100
	float			fPositionY(float f);	// dla aktualnej rozdzielczosci ekranu

	int				ixSDStoSDW(int x);		// podajemy wspolrzedne dla 1024x768, dostajemy dla 1366x768
	int				ixSDStoHDS(int x);		// 1024x768>2048x768
	int				ixSDStoHDW(int x);		// 1024x768>1920x1080

	int				ixSDWtoSDS(int x);		// podajemy wspolrzedne dla 1366x768, dostajemy dla 1024x768
	int				ixSDWtoHDS(int x);		// 1366x768>2048x1536
	int				ixSDWtoHDW(int x);		// 1366x768>1920x1080

	int				ixHDWtoSDS(int x);		// 1920x1080>1024x768
	int				ixHDWtoSDW(int x);		// 1920x1080>1366x768
	int				ixHDWtoHDS(int x);		// 1920x1080>2048x1536

	int				ixHDStoSDS(int x);		// 2048x1536>1024x768
	int				ixHDStoSDW(int x);		// 2048x1536>1366x768
	int				ixHDStoHDW(int x);		// 2048x1536>1920x1080

	int				iySDStoSDW(int y);		// podajemy wspolrzedne dla 1024x768, dostajemy dla 1366x768
	int				iySDStoHDS(int y);		// 1024x768>2048x768
	int				iySDStoHDW(int y);		// 1024x768>1920x1080

	int				iySDWtoSDS(int y);		// podajemy wspolrzedne dla 1366x768, dostajemy dla 1024x768
	int				iySDWtoHDS(int y);		// 1366x768>2048x1536
	int				iySDWtoHDW(int y);		// 1366x768>1920x1080

	int				iyHDWtoSDS(int y);		// 1920x1080>1024x768
	int				iyHDWtoSDW(int y);		// 1920x1080>1366x768
	int				iyHDWtoHDS(int y);		// 1920x1080>2048x1536

	int				iyHDStoSDS(int y);		// 2048x1536>1024x768
	int				iyHDStoSDW(int y);		// 2048x1536>1366x768
	int				iyHDStoHDW(int y);		// 2048x1536>1920x1080

	int				iSDStoX(int x);
	int				iSDWtoX(int x);
	int				iHDStoX(int x);
	int				iHDWtoX(int x);

	int				iSDStoY(int y);
	int				iSDWtoY(int y);
	int				iHDStoY(int y);
	int				iHDWtoY(int y);

	int				iXtoSDS(int x);
	int				iXtoSDW(int x);
	int				iXtoHDS(int x);
	int 			iXtoHDW(int x);

	int				iYtoSDS(int y);
	int				iYtoSDW(int y);
	int				iYtoHDS(int y);
	int 			iYtoHDW(int y);

	// zwi«kszanie pozycji x0-16 i y0-16, mozna np. potrzasac ekranem, jezeli wszystkie kontrolki bazuja na tych funkcjach

	void 			RenderX(int i);
	void 			RenderY(int i);

	// siatka 4x4

	inline int		iXA(void) { return _iXA; }
	inline int		iXB(void) { return _iXB; }
	inline int		iXC(void) { return _iXC; }
	inline int		iXD(void) { return _iXD; }
	inline int		iXE(void) { return _iXE; }

	inline int		iYA(void) { return _iYA; }
	inline int		iYB(void) { return _iYB; }
	inline int		iYC(void) { return _iYC; }
	inline int		iYD(void) { return _iYD; }
	inline int		iYE(void) { return _iYE; }

	// siatka 16x16

	inline int		x0(void) { return _x0; }
	inline int		x1(void) { return _x1; }
	inline int		x2(void) { return _x2; }
	inline int		x3(void) { return _x3; }
	inline int		x4(void) { return _x4; }
	inline int		x5(void) { return _x5; }
	inline int		x6(void) { return _x6; }
	inline int		x7(void) { return _x7; }
	inline int		x8(void) { return _x8; }
	inline int		x9(void) { return _x9; }
	inline int		x10(void) { return _x10; }
	inline int		x11(void) { return _x11; }
	inline int		x12(void) { return _x12; }
	inline int		x13(void) { return _x13; }
	inline int		x14(void) { return _x14; }
	inline int		x15(void) { return _x15; }
	inline int		x16(void) { return _x16; }

	inline int		y0(void) { return _y0; }
	inline int		y1(void) { return _y1; }
	inline int		y2(void) { return _y2; }
	inline int		y3(void) { return _y3; }
	inline int		y4(void) { return _y4; }
	inline int		y5(void) { return _y5; }
	inline int		y6(void) { return _y6; }
	inline int		y7(void) { return _y7; }
	inline int		y8(void) { return _y8; }
	inline int		y9(void) { return _y9; }
	inline int		y10(void) { return _y10; }
	inline int		y11(void) { return _y11; }
	inline int		y12(void) { return _y12; }
	inline int		y13(void) { return _y13; }
	inline int		y14(void) { return _y14; }
	inline int		y15(void) { return _y15; }
	inline int		y16(void) { return _y16; }

public:
    
    SDL_DisplayMode		_mode;
    SDL_Window			*_window;
    SDL_GLContext		_gl;
    
private:

	int					_iSizeX, _iSizeY;					// aktualne wspolrzedne ekranu

	bool				_isSDS, _isSDW, _isHDS, _isHDW;		// jaki typ rozdzielczosci

	bool				_isHD;								// czy to jest HDS lub HDW

	int					_iXA, _iXB, _iXC, _iXD, _iXE;		// parametry poziome dla macierzy
	int					_iYA, _iYB, _iYC, _iYD, _iYE;		// parametry pionowe dla macierzy


	// siatka 16x16
	// x16 = max
	// x8 = polowa
	// x0,y0 = 0,0

	int					_x0,_x1,_x2,_x3,_x4,_x5,_x6,_x7,_x8,_x9,_x10,_x11,_x12,_x13,_x14,_x15,_x16;
	int					_y0,_y1,_y2,_y3,_y4,_y5,_y6,_y7,_y8,_y9,_y10,_y11,_y12,_y13,_y14,_y15,_y16;

	float				_fPixelRatio, _fReverseRatio;

};


