// w banku sfx znajduja sie dzwieki, ktore sa 
// - odtwarzane losowo 
// - odtwarzane po kolei
// - odtwarzane wg parametru

//#include "sound.h"

#ifndef _IGAME__BANKSFX_
#define _IGAME__BANKSFX_

#include  "iGame.h"

class CBankSFX
{

    public:
	    CBankSFX();
	    virtual ~CBankSFX();
	    
	    unsigned char	m_ucVersion;	// ktora wersja pliku
	    
	    unsigned char	m_ucLosowanie;	// czy wave ma byc losowany
	    unsigned char	m_ucPoKolei;	// czy odtwarzac wave'y z listy po kolei
	    
	    unsigned int	m_uiLiczbaWabe;	// ile dzwiekow w tym banku
	    
	    char	*m_pNazwaPliku;	// 256 bajtow
	    char	*m_pOpis;	// opis dzwieku
	    
	    // CSound	*m_pWave;	// dzwiek ktory odtwarzamy
	    
};

#endif
