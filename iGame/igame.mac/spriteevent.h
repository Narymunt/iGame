// zdarzenie postaci, jezeli odtwarzamy np Kot->Radosc(); to losuje animacje z dzwiekiem i odtwarza
// np radosc
//    - pierwsza animacja + dzwiek
//    - druga animacja + dzwiek

#ifndef _IGAME__SPRITE_EVENT_
#define _IGAME__SPRITE_EVENT_

class SpriteEvent
{

    public : 
    
	SpriteEvent();	// konstruktor
	virtual ~SpriteEvent(); // destruktor
    
    protected:

    // NN_Animation m_pAnimationTable[]; 	// tablica z animacjami    
    // NN_Sound m_pSound[];

};

#endif