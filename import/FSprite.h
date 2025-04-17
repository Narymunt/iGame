// FSprite.h: interface for the FSprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FSPRITE_H__A6F06941_6172_4CE6_A5F8_064AAD3F6641__INCLUDED_)
#define AFX_FSPRITE_H__A6F06941_6172_4CE6_A5F8_064AAD3F6641__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fox.h>
#include "FEvent.h"

// zdarzenia sa trzymane w osobnym pliku, kazde jedno zdarzenie

class FSprite  
{
public:
	FSprite(char csFilename[]);
	virtual ~FSprite();

	void Put(FOX_Surface *fsDestination, 
			 unsigned long ulXScreen, unsigned long ulYScreen, unsigned long ulFrame);



	unsigned long	ulIloscKlatek;		// ile klatek w tym obiekcie

	//=== poczatek petli ===

	unsigned int	*uiWysokoscKlatki;	// czyli ile pixeli w pione
	unsigned int	*uiSzerokoscKlatki;	// czyli ile pixeli w poziomie

	FOX_Surface		**fsObrazKlatki;	// czyli dane w formacie bgra

	//=== koniec petli ===

	unsigned int	ulIloscZdarzen;		// ile zdarzen

	FEvent			**fevZdarzenia;		// zdarzenia postaci
	

};

#endif // !defined(AFX_FSPRITE_H__A6F06941_6172_4CE6_A5F8_064AAD3F6641__INCLUDED_)
