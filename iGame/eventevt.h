
// odczytanie struktury pliku evt


#ifndef _IGAME__EVENTEVT_
#define _IGAME__EVENTEVT_

#include "iGame.h"

//#include "sprite.h"	// wyswietlanie grafiki
//#include "event.h"	// alokacja zdarzenia

class CEventEVT
{

    public:
	    CEventEVT(char cFile[], char cEventName[]);	// nowe zdarzenie odczytane z pliku
	    virtual ~CEventEVT();
	    
	    // renderowanie wg numeru lub nazwy zdarzenia, pozycje obiektu odczytane z pliku
	    
	    virtual void Put(unsigned int uiNrKlatki, unsigned int uiNrEventu, unsigned char *pBuffer);
	    virtual void Put(unsigned int uiNrKlatki, char cNazwa[], unsigned char *pBuffer);
	    
	    // renderowanie wg numeru lub nazwy zdarzenia, pozycje podajemy sami 
	    
	    virtual void Put(int iXScreen, int iYScreen, 
			    unsigned int uiNrKlatki, unsigned int uiNrEventu, unsigned char *pBuffer);
			    
	    virtual void Put(int iXScreen, int iYScreen,
			    unsigned int uiNrKlatki, char cNazwa[], unsigned char *pBuffer);
			    
	
    private:
    
	    unsigned char	m_ucVersion;		// wersja pliku
	    unsigned int	m_uiIloscKlatek;		// ile klatek w tym pliku
	    
	    CBitmap		**m_pEventFrames;		// wskaznik na tablice (!!) klatek 
	    
	    unsigned int	m_uiIloscZdarzen;	// ile jest zdarzen w tym sprite
	    CEvent		**m_pEvent;		// zdarzenia
    
};

#endif
