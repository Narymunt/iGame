// w banku sfx znajduja sie dzwieki, ktore sa 
// - odtwarzane losowo 
// - odtwarzane po kolei

// typ : 1 - po kolei, 2 losowo

// czyli np. zdarzenie "gada" ma 3 dzwieki i odtwarzane sa po kolei
// wav start.wav
// wav gadanie.wav
// wav end.wav

// zdarzenie "dobrze", czyli losowe mowienie roznego tekstu o tym,
// ze zadanie zostalo wykonane poprawnie
// wav dobrze1.wav
// wav dobrze2.wav
// wav.... 


//#include "sound.h"

#ifndef _IGAME__BANKSFX_
#define _IGAME__BANKSFX_

#include  "iGame.h"

class CBankSFX
{

    public:
	    CBankSFX(char XMLFilename[]);	// dane wczytane z pliku XML
	    virtual ~CBankSFX();

	    void Play(char cEvent[]);	// graj zdarzenie na podstawie nazwy
	    void Play(int iEvent);	// graj zdarzenie o numerze
	    

    private:
	    
	    unsigned char	m_ucVersion;	// ktora wersja pliku
	    unsigned char	m_ucType;	// czy wave ma byc losowany
	    
	    unsigned int	m_uiLiczbaWave;	// ile dzwiekow w tym banku
	    
	    char	**m_pNazwaPliku;	// nazwy plikow wave
	    char	*m_pOpis;	// opis zdarzenia dzwiekowego

	    Mix_Chunk	**m_pWave;	// tutaj dzwieki
	    
	    CXmlFile	*m_pXML;	// z tego pliku odczytujemy wszystkie parametry
	    
	    char	m_cTempNode[1024];	// zakladam ze linia nie bedzie dluzsza niz 1024 znaki
};

#endif
