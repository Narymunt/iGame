// FEvent.h: interface for the FEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEVENT_H__3664568E_49B4_4777_8E4F_AECFD1F07999__INCLUDED_)
#define AFX_FEVENT_H__3664568E_49B4_4777_8E4F_AECFD1F07999__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class FEvent  
{
public:
	FEvent();
	virtual ~FEvent();

	unsigned char	*sNazwaZdarzeniaGFX;	// nazwa zdarzenia graficznego 256

	unsigned long	ulLiczbaKlatek;			// liczba klatek w zdarzeniu

	int				*iXKlatki;				// wspolrzedne na ekrania, lewy gorny rog
	int				*iYKlatki;				// tak jak wyzej
	unsigned int	*uiNrKlatki;			// numer klatki 

	unsigned char	ucCzyOdtwarzac;			// czy jest do tego zdarzenie dzwiekowe


	char			sNazwaBanku[256];		// plik ze opisem zdarzen
											// na koncu 0
	
	char			sNazwaZdarzeniaSFX[256];	// nazwa zdarzenia dzwiekowego w pliku

	unsigned char	ucJakOdtwarzac;			// losowo/po kolei/parametr
											// 0 nie odtwarzac
											// 1 losowo
											// 2 po kolei
											// 3 parametr
											// 3 petla, powtarza 
						
	unsigned int	uiIleWave;				// ile wave w tym zdarzeniu
	char			**sNazwyWave;			// nazwy plikow do wczytania

};

#endif // !defined(AFX_FEVENT_H__3664568E_49B4_4777_8E4F_AECFD1F07999__INCLUDED_)
