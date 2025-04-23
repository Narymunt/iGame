// to jest zdarzenie dzwiekowe, ktore zawiera w sobie wiele plikow .wave
// sa one odtwarzane po kolei, lub losowo
// wszyskie zdarzenia dzwiekowe pogrupowane sa w banku dzwiekowym
// w jednym zdarzeniu dzwiekowym moze byc maksymalnie 16 wave'ow

// nie jestesmy w stanie okreslic ile bedzie dzwiekow z gory, gdyz dodajemy je stopniowo z pliku XML

// typ : 1 - po kolei, 2 losowo


#ifndef _IGAME__EVENTSND_
#define _IGAME__EVENTSND_

#include  "iGame.h"

class CEventSND
{

    public:
	    CEventSND(char cNazwa[],unsigned char ucType);	// dane wczytane z pliku XML
	    virtual ~CEventSND();

	    void Add(char cWaveName[]);	// dodaj wave
	    void Play();	// graj zdarzenie

    private:
	    
	    unsigned char	m_ucType;	// czy wave ma byc losowany
	    char	*m_pNazwa;	// nazwa zdarzenia dzwiekowego
	    Mix_Chunk	m_pWave[16];	// tutaj dzwieki
	    
};

#endif
