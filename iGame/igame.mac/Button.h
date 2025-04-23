// przyciski, statyczne, jedynie stany w zaleznosci od polozenia myszy
// tworzone zawsze z plikow .tga

#ifndef _IGAME__BUTTON_
#define _IGAME__BUTTON_

#include "Bitmap.h"	// korzystamy z bitmapy

class CButton
{

    public:

	CButton(char cStatic[], char cOnClick[], char cOnMouse[]);     
	virtual ~CButton();

        // konstruktor od razu ze wspolrzednymi, gorace takie same jak obrazu
        
        CButton(char cStatic[], char cOnClick[], char cOnMouse[], 
                int iXPosition, int iYPosition);
        
        // konstruktor ze wspolrzednymi, ale reagujace rozne od rysowanych
        
        CButton(char cStatic[], char cOnClick[], char cOnMouse[],
                int iXPosition, int iYPosition, 
                int iHotXPositionStart, int iHotYPositionStart,
                int iHotXPositionEnd, int iHotYPositionEnd);
 
		CButton(char cScriptFile[]);	// inicjalizacja ze skryptu
			          
        // rysuj 
        
        virtual int Render(int iMouseX, int iMouseY, bool bLeftButton, bool bCenterButton,
                bool bRightButton, unsigned char *pBackBuffer);
        
        // ustawienie wspolrzednych do rysowania
        
        virtual void SetPosition(int iXPosition, int iYPosition);
        
        // ustawienie wspolrzednych reagowania
        
        virtual void SetHotPosition(int iHotXPositionStart, int iHotYPositionStart,
                int iHotXPositionEnd, int iHotYPositionEnd);
        
        // to podnoszenia znakow
		
		void UpOnly(char str[]);
		
        
    protected:
	
    // obrazy
        
    CBitmap     *m_pStatic; // zwykly przycisk, gdy mysz poza obszarem
    CBitmap     *m_pOnClick;    // gdy klikniety
    CBitmap     *m_pOnMouse;    // gdy myszka nad nim
    
    // wspolrzedne rysowania
    
    int m_iXPosition;
    int m_iYPosition;
    
    // gorace wspolrzedne
    
    int m_iHotXPositionStart;
    int m_iHotXPositionEnd;
    int m_iHotYPositionStart;
    int m_iHotYPositionEnd;
    
    // pozostale
    
    bool    m_bFE;  // first enter, czy pierwsze wejscie na przycisk (dzwiek)
    bool    m_bPress;   // czy nacisniety
	
	char	m_cName[256];	// nazwa przycisku
};

#endif
